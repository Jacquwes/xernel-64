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
#include <terminal.hpp>

namespace kernel
{
	/// <summary>
	/// Manages the screen.
	/// It is a singleton.
	/// </summary>
	class screen_manager
	{
	public:
		/// <summary>
		/// Singleton instance of the screen manager.
		/// </summary>
		static screen_manager* instance;

		/// <summary>
		/// Initializes the screen manager.
		/// </summary>
		screen_manager();

		/// <summary>
		/// Width of the screen in pixels.
		/// </summary>
		u64 width;

		/// <summary>
		/// Height of the screen in pixels.
		/// </summary>
		u64 height;

		/// <summary>
		/// Draws a pixel on the screen.
		/// </summary>
		/// <param name="x">X position of the pixel.</param>
		/// <param name="y">Y position of the pixel.</param>
		/// <param name="color">RGB color of the pixel.</param>
		void draw_pixel(u64 x, u64 y, u32 color);

	private:
		limine_framebuffer* m_framebuffer;
	};
}