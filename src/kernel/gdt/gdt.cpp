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

#include "gdt.hpp"

namespace kernel
{
	namespace gdt
	{
		u16 segment_selector_t::get_index() const
		{
			return (data & 0b1111'1111'1111'1000) >> 3;
		}

		void segment_selector_t::set_index(u16 index)
		{
			data &= (0b0000'0000'0000'0111 | ((index & 0b1'1111'1111'1111) << 3));
		}

		segment_selector_t::table_t segment_selector_t::get_table() const
		{
			return static_cast<segment_selector_t::table_t>((data & 0b0000'0000'0000'0100) >> 2);
		}

		void segment_selector_t::set_table(segment_selector_t::table_t table)
		{
			data &= (0b1111'1111'1111'1011 | ((table & 1) << 2));
		}

		u8 segment_selector_t::get_requested_privilege_level() const
		{
			return data & 0b0000'0000'0000'0011;
		}

		void segment_selector_t::set_requested_privilege_level(u8 rpl)
		{
			data &= (0b1111'1111'1111'1100 | (rpl & 0b0011));
		}

		segment_descriptor_t::access_byte_t::access_byte_t(u8 value_)
		{
			value = value_;
		}

		bool segment_descriptor_t::access_byte_t::get_accessed() const
		{
			return value & 0b000'00001;
		}

		void segment_descriptor_t::access_byte_t::set_accessed(bool accessed)
		{
			value &= (0b1111'1110 | accessed);
		}

		bool segment_descriptor_t::access_byte_t::get_readable() const
		{
			return (value & 0b0000'0010) >> 1;
		}

		void segment_descriptor_t::access_byte_t::set_readable(bool readable)
		{
			value &= (0b1111'1101 | ((readable & 0b0000'0001) << 1));
		}

		bool segment_descriptor_t::access_byte_t::get_writable() const
		{
			return (value & 0b0000'0010) >> 1;
		}

		void segment_descriptor_t::access_byte_t::set_writable(bool writable)
		{
			value &= (0b1111'1101 | ((writable & 0b0000'0001) << 1));
		}

		segment_descriptor_t::access_byte_t::direction_t segment_descriptor_t::access_byte_t::get_direction() const
		{
			return (direction_t)
				((value & 0b0000'0100) >> 2);
		}

		void segment_descriptor_t::access_byte_t::set_direction(direction_t direction)
		{
			value &= (0b1111'1011 | ((direction & 0b0000'0001) << 2));
		}

		segment_descriptor_t::access_byte_t::conforming_t segment_descriptor_t::access_byte_t::get_conforming() const
		{
			return (conforming_t)
				((value & 0b0000'0100) >> 2);
		}

		void segment_descriptor_t::access_byte_t::set_conforming(conforming_t conforming)
		{
			value &= (0b1111'1011 | ((conforming & 0b0000'0001) << 2));
		}

		segment_descriptor_t::access_byte_t::executable_t segment_descriptor_t::access_byte_t::get_executable() const
		{
			return (executable_t)
				((value & 0b0000'1000) >> 3);
		}

		void segment_descriptor_t::access_byte_t::set_executable(executable_t executable)
		{
			value &= (0b1111'0111 | ((executable & 0b0000'0001) << 3));
		}

		segment_descriptor_t::access_byte_t::descriptor_type_t segment_descriptor_t::access_byte_t::get_descriptor_type() const
		{
			return (descriptor_type_t)
				((value & 0b0001'0000) >> 4);
		}

		void segment_descriptor_t::access_byte_t::set_descriptor_type(descriptor_type_t type)
		{
			value &= (0b1110'1111 | ((type & 0b0000'0001) << 4));
		}

		u8 segment_descriptor_t::access_byte_t::get_privilege_level() const
		{
			return (value & 0b0110'0000) >> 5;
		}

		void segment_descriptor_t::access_byte_t::set_privilege_level(u8 privilege_level)
		{
			value &= (0b1001'1111 | ((privilege_level & 0b0000'0011) << 5));
		}

		bool segment_descriptor_t::access_byte_t::get_present() const
		{
			return (value & 0b1000'0000) >> 7;
		}

		void segment_descriptor_t::access_byte_t::set_present(bool present)
		{
			value &= (0b0111'1111 | ((present & 0b0000'0001) << 7));
		}

		segment_descriptor_t::system_access_byte_t::system_access_byte_t(u8 value_)
		{
			value = value_;
		}

		segment_descriptor_t::system_access_byte_t::segment_type_t segment_descriptor_t::system_access_byte_t::get_segment_type() const
		{
			return (segment_type_t)
				(value & 0b0000'1111);
		}

		void segment_descriptor_t::system_access_byte_t::set_segment_type(segment_type_t type)
		{
			value &= (0b1111'0000 | (type & 0b0000'1111));
		}

		segment_descriptor_t::flags_t::flags_t(u8 value_)
		{
			value = value_;
		}

		u8 segment_descriptor_t::flags_t::get_long_mode() const
		{
			return (value & 0b0010) >> 1;
		}

		void segment_descriptor_t::flags_t::set_long_mode(u8 long_mode)
		{
			value &= (0b1101 | ((long_mode & 0b0001) << 1));
		}

		u8 segment_descriptor_t::flags_t::get_size() const
		{
			return (value & 0b0100) >> 2;
		}

		void segment_descriptor_t::flags_t::set_size(u8 size)
		{
			value &= (0b1011 | ((size & 0b0001) << 2));
		}

		u8 segment_descriptor_t::flags_t::get_granularity() const
		{
			return (value & 0b1000) >> 3;
		}

		void segment_descriptor_t::flags_t::set_granularity(u8 granularity)
		{
			value &= (0b0111 | ((granularity & 0b0001) << 3));
		}

		u32 segment_descriptor_t::get_limit() const
		{
			u32 limit_low = data_low & 0x0000'0000'0000'ffff;
			u32 limit_high = data_low & 0x000f'0000'0000'0000;

			return limit_low | (limit_high >> 0x20);
		}

		void segment_descriptor_t::set_limit(u32 limit)
		{
			data_low &= 0xffff'ffff'ffff'0000;
			data_low |= limit & 0x0000'0000'0000'ffff;

			data_low &= 0xfff0'ffff'ffff'ffff;
			data_low |= (limit & 0x000f'0000'0000'0000) << 0x20;
		}

		u64 segment_descriptor_t::get_base_low() const
		{
			u64 base_low = data_low & 0x0000'00ff'ffff'0000;
			u64 base_high = data_low & 0xff00'0000'0000'0000;

			return (base_low >> 0x10) | (base_high >> 0x20);
		}

		void segment_descriptor_t::set_base_low(u64 base)
		{
			data_low &= 0xffff'ff00'0000'ffff;
			data_low |= (base & 0x0000'0000'00ff'ffff) << 0x10;

			data_low &= 0x00ff'ffff'ffff'ffff;
			data_low |= (base & 0x0000'0000'ff00'0000) << 0x20;
		}

		segment_descriptor_t::access_byte_t segment_descriptor_t::get_access_byte() const
		{
			return (data_low & 0x0000'ff00'0000'0000) >> 0x28;
		}

		void segment_descriptor_t::set_access_byte(access_byte_t access_byte)
		{
			data_low &= 0xffff'00ff'ffff'ffff;
			data_low |= (static_cast<u64>(access_byte.value & 0x0000'00ff)) << 0x28;
		}

		segment_descriptor_t::flags_t segment_descriptor_t::get_flags() const
		{
			return (data_low & 0x00f0'0000'0000'0000) >> 0x34;
		}

		void segment_descriptor_t::set_flags(flags_t flags)
		{
			data_low &= 0xff0f'ffff'ffff'ffff;
			data_low |= (static_cast<u64>(flags.value & 0x0000'000f)) << 0x34;
		}
	}
}