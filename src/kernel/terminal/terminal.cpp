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

#include <screen.hpp>
#include <terminal.hpp>

namespace kernel
{
    terminal* terminal::instance = nullptr;

	terminal::terminal()
	{
		instance = this;

		rows = screen_manager::instance->height / 16;
		columns = screen_manager::instance->width / 9;
	}

	void terminal::put_string(const char* str, u32 foreground_color, u32 background_color)
	{
		for (const char* c = str; *c; c++)
			put_char(*c, foreground_color, background_color);
	}
}