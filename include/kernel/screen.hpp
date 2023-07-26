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

#include <limine.h>
#include <numerics.hpp>

namespace kernel
{
	class screen_manager
	{
	public:
		static screen_manager* instance;

		screen_manager();

		u64 width;
		u64 height;

		void draw_pixel(u64 x, u64 y, u32 color);

	private:
		limine_framebuffer* m_framebuffer;
	};
}