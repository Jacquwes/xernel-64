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

	}
}