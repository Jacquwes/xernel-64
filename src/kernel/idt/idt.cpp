/*
	xernel - x86_64 kernel written in C++20
	Copyright (C) 2023  Jacquwes

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <gdt.hpp>
#include <idt.hpp>

namespace kernel
{
	namespace idt
	{
		u8 gate_descriptor_t::get_present() const
		{
			return (data_low & 0x0000'8000'0000'0000) >> 0x2f;
		}

		void gate_descriptor_t::set_present(u8 present)
		{
			data_low &= (0xffff'7fff'ffff'ffff | ((present & 1) << 0x2f));
		}



		u8 gate_descriptor_t::get_descriptor_privilege_level() const
		{
			return (data_low & 0x0000'6000'0000'0000) >> 0x2d;
		}

		void gate_descriptor_t::set_descriptor_privilege_level(u8 dpl)
		{
			data_low &= (0xffff'9fff'ffff'ffff | ((dpl & 0b0011) << 0x2d));
		}



		gate_descriptor_t::gate_type_t gate_descriptor_t::get_gate_type() const
		{
			return (data_low & 0x0000'0f00'0000'0000) >> 0x28;
		}

		void gate_descriptor_t::set_gate_type(gate_type_t gate_type)
		{
			data_low &= (0xffff'f0ff'ffff'ffff | ((gate_type & 0b1111) << 0x28));
		}



		u8 gate_descriptor_t::get_interrupt_stack_table() const
		{
			return (data_low & 0x0000'0007'0000'0000) >> 0x20;
		}

		void gate_descriptor_t::set_interrupt_stack_table(u8 ist)
		{
			data_low &= (0xffff'fff8'ffff'ffff | ((ist & 0b0111) << 0x20));
		}



		gdt::segment_selector_t gate_descriptor_t::get_segment_selector() const
		{
			return static_cast<gdt::segment_selector_t>((data_low & 0x0000'0000'0000'ffff'ffff) >> 0x10);
		}

		void gate_descriptor_t::set_segment_selector(gdt::segment_selector_t segment_selector)
		{
			data_low &= (0xffff'ffff'0000'ffff | ((segment_selector.data & 0xffff) << 0x10));
		}



		u64 gate_descriptor_t::get_offset() const
		{
			u64 offset = (data_low & 0x0000'0000'0000'ffff);
			offset |= ((data_low & 0xffff'0000'0000'0000) >> 0x20);
			offset |= ((data_high & 0x0000'0000'ffff'ffff) << 0x20);

			return offset;
		}

		void gate_descriptor_t::set_offset(u64 offset)
		{
			data_high &= (0xffff'ffff'0000'0000 | ((offset & 0xffff'ffff'0000'0000) >> 0x20));
			data_low &= (0x0000'ffff'ffff'ffff | ((offset & 0x0000'0000'ffff'0000) << 0x20));
			data_low &= (0xffff'ffff'ffff'0000 | (offset & 0x0000'0000'0000'ffff));
		}
	}
}