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
	
static volatile limine_framebuffer_request m_framebuffer_request = {
	LIMINE_FRAMEBUFFER_REQUEST,
	0,
	0,
};

namespace kernel
{
	screen_manager* screen_manager::instance = nullptr;

	screen_manager::screen_manager()
	{
		instance = this;

		if (!m_framebuffer_request.response
			|| m_framebuffer_request.response->framebuffer_count < 1)
			return;

		m_framebuffer = m_framebuffer_request.response->framebuffers[0];

		width = m_framebuffer->width;
		height = m_framebuffer->height;
	}

	void screen_manager::draw_pixel(u64 x, u64 y, u32 color)
	{
		if (x >= width || y >= height)
			return;

		auto bytes_per_pixel = m_framebuffer->bpp / 8;
		auto pixel_offset = m_framebuffer->pitch * y + x * bytes_per_pixel;

		u8* fb_ptr = (u8*)m_framebuffer->address;
		fb_ptr[pixel_offset] = color;
		fb_ptr[pixel_offset + 1] = color >> 8;
		fb_ptr[pixel_offset + 2] = color >> 16;
	}
}