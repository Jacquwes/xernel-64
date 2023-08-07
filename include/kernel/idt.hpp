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
	namespace gdt
	{
		struct segment_selector_t;
	}
	namespace idt
	{
		struct gate_descriptor_t
		{
			enum gate_type_t
			{
				INTERRUPT_GATE = 0b1110,
				TRAP_GATE = 0b1111,
			};

			u8 get_present() const;
			void set_present(u8);

			u8 get_descriptor_privilege_level() const;
			void set_descriptor_privilege_level(u8);

			gate_type_t get_gate_type() const;
			void set_gate_type(gate_type_t);

			u8 get_interrupt_stack_table() const;
			void set_interrupt_stack_table(u8);

			gdt::segment_selector_t get_segment_selector() const;
			void set_segment_selector(gdt::segment_selector_t);

			u64 get_offset() const;
			void set_offset(u64);

			u64 data_low = 0;
			u64 data_high = 0;
		} __attribute__((packed));

		struct idt_t
		{
			gate_descriptor_t entries[0x100];
		} __attribute__((packed));

		struct idtr_t
		{
			u16 size = 0;
			u64 offset = 0;
		} __attribute__((packed));

		struct idt_manager
		{
			static idt_manager* instance;

			idt_manager();

			gate_descriptor_t get_entry(u8 index) const;
			void set_entry(u8 index, gate_descriptor_t entry);

			void load_default();

			void flush();

			void lidt();

		private:
			idt_t m_idt;
			idtr_t m_idtr;
		};
	}
}