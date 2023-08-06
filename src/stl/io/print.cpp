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

#include <io.hpp>
#include <numerics.hpp>
#include <terminal.hpp>

namespace stl
{
	void print(const char* format, ...)
	{
		__builtin_va_list args;
		__builtin_va_start(args, format);
		vprint(format, args);
		__builtin_va_end(args);
	}

	void vprint(const char* format, __builtin_va_list args)
	{
		auto& terminal = *kernel::terminal::instance;

		for (const char* c = format; *c != 0; c++)
		{
			terminal.put_char(*c);
		}
	}
}