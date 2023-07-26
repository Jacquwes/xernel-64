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

namespace kernel
{
	class terminal
	{
	public:
		struct cursor
		{
			u64 row;
			u64 column;
		};

		static terminal* instance;

		terminal();

		void draw_char(u8 c, u32 color = 0x777777);

		u64 rows;
		u64 columns;

		cursor cursor;
	};
}