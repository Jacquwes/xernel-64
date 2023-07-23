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

#include <limine.h>

#include <stl/int.hpp>

static volatile struct limine_framebuffer_request framebuffer_request =
{
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0,
};

void halt()
{
	asm("cli");
	for (;;)
		asm("hlt");
}

extern "C" void _start()
{
	if (framebuffer_request.response == 0
		|| framebuffer_request.response->framebuffer_count < 1)
		halt();

	limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];

	for (size_t i = 0; i < 100; i++)
	{
		uint32_t* fb = reinterpret_cast<uint32_t*>(framebuffer->address);
		fb[i * (framebuffer->pitch / 4) + i] = 0x0000ff;
	}

	halt();
}