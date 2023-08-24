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

#include "pic.hpp"

namespace kernel
{
	namespace pic
	{
		pic_manager* pic_manager::instance = nullptr;

		pic_manager::pic_manager()
		{
			instance = this;
		}

		pic_manager* pic_manager::get_instance()
		{
			return instance;
		}

		void pic_manager::init_pic()
		{
			send_8(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
			send_8(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);

			send_8(MASTER_PIC_DATA, MASTER_PIC_ADDRESS);
			send_8(SLAVE_PIC_DATA, SLAVE_PIC_ADDRESS);

			send_8(MASTER_PIC_DATA, 0x04);
			send_8(SLAVE_PIC_DATA, 0x02);

			send_8(MASTER_PIC_DATA, ICW4_8086);
			send_8(SLAVE_PIC_DATA, ICW4_8086);

			send_8(MASTER_PIC_DATA, 0xff);
			send_8(SLAVE_PIC_DATA, 0xff);
		}

		void pic_manager::send_8(u16 port, u8 value)
		{
			asm volatile("outb %0, %1" : : "a"(value), "dN"(port));
		}
		
		void pic_manager::send_16(u16 port, u16 value)
		{
			asm volatile("outw %0, %1" : : "a"(value), "dN"(port));
		}

		void pic_manager::send_32(u16 port, u32 value)
		{
			asm volatile("outl %%eax, %%dx" : : "dN"(port), "a"(value));
		}

		u8 pic_manager::receive_8(u16 port)
		{
			u8 value;
			asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
			return value;
		}

		u16 pic_manager::receive_16(u16 port)
		{
			u16 value;
			asm volatile("inw %1, %0" : "=a"(value) : "dN"(port));
			return value;
		}

		u32 pic_manager::receive_32(u16 port)
		{
			u32 value;
			asm volatile("inl %%dx, %%eax" : "=a"(value) : "dN"(port));
			return value;
		}
	}
}