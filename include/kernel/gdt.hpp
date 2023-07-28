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

#pragma once

#include <numerics.hpp>

namespace kernel::gdt
{
	struct segment_descriptor
	{
		struct access_byte
		{
			u8 accessed : 1;
			u8 readable_writeable : 1;
			u8 direction : 1;
			u8 executable : 1;
			u8 descriptor_type : 1;
			u8 descriptor_privilege_level : 2;
			u8 present : 1;

			access_byte() = default;
			access_byte(u8 value);
		} __attribute(packed);

		struct flags
		{
			u8 granularity : 1;
			u8 size : 1;
			u8 long_mode : 1;
			u8 reserved : 1;

			flags() = default;
			flags(u8 value);
		} __attribute__((packed));

		struct
		{
			u64 limit_low : 16;
			u64 base_low : 24;
			access_byte access_byte : 8;
			u64 limit_high : 4;
			flags flags : 4;
			u64 base_high : 8;
		} low;

		struct
		{
			u64 base : 32;
			u64 reserved : 32;
		} high;
	} __attribute__((packed));

	struct gdt
	{
		gdt_entry entries[8];
	} __attribute__((packed));

	class gdt_manager
	{
	public:
		static gdt_manager* instance;

		gdt_manager();

		gdt_manager& set_entry(u8 index, gdt_entry entry);

		gdt_manager& load_default();

		gdt_manager& flush();

	private:
		gdt m_gdt;
	};
}