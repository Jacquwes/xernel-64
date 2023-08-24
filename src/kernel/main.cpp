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

#define GLOBAL_NUMERICS

#include <numerics.hpp>

#include <gdt.hpp>
#include <halt.hpp>
#include <pic.hpp>
#include <screen.hpp>
#include <terminal.hpp>

extern "C" void _start()
{
	auto screen = kernel::screen_manager();
	auto terminal = kernel::terminal();
	auto gdt = kernel::gdt::gdt_manager();
	auto pic = kernel::pic::pic_manager();

	gdt.load_default();
	gdt.lgdt();

	terminal.put_string("Hello, world!\nf", 0xff7777, 0x007777);

	kernel::halt();
}
