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

namespace kernel
{
	namespace gdt
	{
		gdt_manager::gdt_manager()
		{}

		segment_descriptor_t gdt_manager::get_entry(u8 index) const
		{
			return m_gdt.entries[index];
		}

		void gdt_manager::set_entry(u8 index, segment_descriptor_t entry)
		{
			m_gdt.entries[index] = entry;
		}

		void gdt_manager::load_default()
		{
			auto access_byte = segment_descriptor_t::access_byte_t();
			auto flags = segment_descriptor_t::flags_t();

			// Null segment
			m_gdt.entries[0] = segment_descriptor_t();

			// Kernel code segment
			auto kernel_code_segment = segment_descriptor_t();
			// 0x9A (0b1001'1010)
			access_byte.set_accessed(false);
			access_byte.set_readable(true);
			access_byte.set_conforming(false);
			access_byte.set_executable(true);
			access_byte.set_descriptor_type(segment_descriptor_t::access_byte_t::descriptor_type_t::CODE_OR_DATA);
			access_byte.set_privilege_level(0);
			access_byte.set_present(true);
			kernel_code_segment.set_access_byte(access_byte);
			// 0xA (0b1010)
			flags.set_long_mode(true);
			flags.set_size(0);
			flags.set_granularity(1);
			kernel_code_segment.set_flags(flags);
			kernel_code_segment.set_limit(0xfffff);
			m_gdt.entries[1] = kernel_code_segment;

			// Kernel data segment
			auto kernel_data_segment = segment_descriptor_t();
			// 0x92 (0b1001'0010)
			access_byte.set_accessed(false);
			access_byte.set_writable(true);
			access_byte.set_direction(segment_descriptor_t::access_byte_t::direction_t::GROW_UP);
			access_byte.set_executable(false);
			access_byte.set_descriptor_type(segment_descriptor_t::access_byte_t::descriptor_type_t::CODE_OR_DATA);
			access_byte.set_privilege_level(0);
			access_byte.set_present(true);
			kernel_data_segment.set_access_byte(access_byte);
			// 0xC (0b1100)
			flags.set_long_mode(false);
			flags.set_size(1);
			flags.set_granularity(1);
			kernel_data_segment.set_flags(flags);
			kernel_data_segment.set_limit(0xfffff);
			m_gdt.entries[2] = kernel_data_segment;
		}

		void gdt_manager::flush()
		{
			for (segment_descriptor_t& entry : m_gdt.entries)
			{
				entry = segment_descriptor_t();
			}
		}

		void gdt_manager::lgdt()
		{
			m_gdtr.offset = (u64)&m_gdt;
			m_gdtr.size = sizeof(m_gdt) - 1;

			asm volatile("lgdt %0" : : "m"(m_gdtr));
		}
	}
}