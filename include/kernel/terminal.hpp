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
	/// <summary>
	/// This class is used to communicate with the user through the use of a terminal.
	/// It is a singleton class.
	/// </summary>
	class terminal
	{
	public:
		/// <summary>
		/// This struct is used to represent a cursor on the <see cref="screen_manager"/> singleton instance.
		/// </summary>
		struct cursor
		{
			u64 row;
			u64 column;
		};

		/// <summary>
		/// Singleton instance of the terminal.
		/// </summary>
		static terminal* instance;

		/// <summary>
		/// Initializes a new instance of the <see cref="terminal"/> class.
		/// </summary>
		terminal();

		/// <summary>
		/// Puts a character on the terminal.
		/// </summary>
		/// <param name="c">Character to put.</param>
		/// <param name="foreground_color">Color of the character.</param>
		/// <param name="background_color">Color of the background.</param>
		void put_char(u8 c, u32 foreground_color = 0x777777, u32 background_color = 0x000000);
		
		/// <summary>
		/// Puts a string on the terminal.
		/// </summary>
		/// <param name="str">String to put.
		/// <param name="foreground_color">Color of the string.</param>
		/// <param name="background_color">Color of the background.</param>
		void put_string(const char* str, u32 foreground_color = 0x777777, u32 background_color = 0x000000);

		/// <summary>
		/// How many rows the terminal has.
		/// </summary>
		u64 rows;

		/// <summary>
		/// How many columns the terminal has.
		/// </summary>
		u64 columns;

		/// <summary>
		/// Current cursor.
		/// </summary>
		cursor cursor;
	};
}