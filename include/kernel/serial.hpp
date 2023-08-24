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
#include <pic.hpp>

namespace kernel
{
	namespace serial
	{
		class serial_manager
		{
		public:
			serial_manager();

			static serial_manager* get_instance();

			void init_port(pic::com_ports_t port = pic::com_ports_t::COM1);

			void put_char(char c, pic::com_ports_t port = pic::com_ports_t::COM1);
			void put_string(char const* s, pic::com_ports_t port = pic::com_ports_t::COM1);

		private:
			static serial_manager* instance;
		};
	}
}