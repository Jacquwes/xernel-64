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

#include <serial.hpp>
#include <pic.hpp>

namespace kernel
{
	namespace serial
	{
		serial_manager* serial_manager::instance = nullptr;

		serial_manager::serial_manager()
		{
			instance = this;
		}

		serial_manager* serial_manager::get_instance()
		{
			return instance;
		}

		void serial_manager::init_port(pic::com_ports_t port)
		{
			auto pic_manager = pic::pic_manager::get_instance();
			if (!pic_manager)
			{
				pic::pic_manager();
				pic_manager = pic::pic_manager::get_instance();
			}

			pic_manager->send_8(port + 1, 0x00);
			pic_manager->send_8(port + 3, 0x80);
			pic_manager->send_8(port + 0, 0x03);
			pic_manager->send_8(port + 1, 0x00);
			pic_manager->send_8(port + 3, 0x03);
			pic_manager->send_8(port + 2, 0xc7);
			pic_manager->send_8(port + 4, 0x0b);
			pic_manager->send_8(port + 4, 0x0f);
		}

		void serial_manager::put_char(char c, pic::com_ports_t port)
		{
			auto pic_manager = pic::pic_manager::get_instance();
			if (!pic_manager)
			{
				pic::pic_manager();
				pic_manager = pic::pic_manager::get_instance();
			}
			
			while ((pic_manager->receive_8(pic::COM1 + 5) & 0x20) == 0);
			pic_manager->send_8(pic::COM1, c);
		}

		void serial_manager::put_string(char const* s, pic::com_ports_t port)
		{
			for (; *s; s++)
				put_char(*s, port);
		}
	}
}