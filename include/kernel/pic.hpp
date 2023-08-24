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
	namespace pic
	{
		constexpr auto MASTER_PIC_ADDRESS = 0x20;
		constexpr auto MASTER_PIC_COMMAND = MASTER_PIC_ADDRESS;
		constexpr auto MASTER_PIC_DATA = MASTER_PIC_ADDRESS + 1;
		constexpr auto SLAVE_PIC_ADDRESS = 0x28;
		constexpr auto SLAVE_PIC_COMMAND = SLAVE_PIC_ADDRESS;
		constexpr auto SLAVE_PIC_DATA = SLAVE_PIC_ADDRESS + 1;

		constexpr auto ICW1_ICW4 = 0x01;
		constexpr auto ICW1_SINGLE = 0x02;
		constexpr auto ICW1_INTERVAL4 = 0x04;
		constexpr auto ICW1_LEVEL = 0x08;
		constexpr auto ICW1_INIT = 0x10;

		constexpr auto ICW4_8086 = 0x01;
		constexpr auto ICW4_AUTO = 0x02;
		constexpr auto ICW4_BUF_SLAVE = 0x08;
		constexpr auto ICW4_BUF_MASTER = 0x0c;
		constexpr auto ICW4_SFNM = 0x10;

		constexpr auto PIC_READ_IRR = 0x0a;
		constexpr auto PIC_READ_ISR = 0x0b;

		constexpr auto PIC_EOI = 0x20;

		constexpr auto COM1 = 0x3F8;
		constexpr auto COM2 = 0x2F8;
		constexpr auto COM3 = 0x3E8;
		constexpr auto COM4 = 0x2E8;
		constexpr auto COM5 = 0x5F8;
		constexpr auto COM6 = 0x4F8;
		constexpr auto COM7 = 0x5E8;
		constexpr auto COM8 = 0x4E8;

		class pic_manager
		{
		public:
			pic_manager();

			pic_manager* get_instance();
			
			void init_pic();

			void send_8(u16 port, u8 value);
			void send_16(u16 port, u16 value);
			void send_32(u16 port, u32 value);

			u8 receive_8(u16 port);
			u16 receive_16(u16 port);
			u32 receive_32(u16 port);

		private:
			static pic_manager* instance;

		};
	}
}