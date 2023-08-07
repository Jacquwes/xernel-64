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

#include <idt.hpp>
#include <gdt.hpp>
#include <halt.hpp>
#include <terminal.hpp>

namespace kernel
{
	namespace idt
	{
		void default_interrupt_routine()
		{
			terminal::instance->put_string("An interrupt ocurred; Halting the CPU.");
			halt();
		}

		idt_manager::idt_manager()
		{}

		gate_descriptor_t idt_manager::get_entry(u8 index) const
		{
			return m_idt.entries[index];
		}

		void idt_manager::set_entry(u8 index, gate_descriptor_t entry)
		{
			m_idt.entries[index] = entry;
		}

		void idt_manager::load_default()
		{
			for (gate_descriptor_t& entry : m_idt.entries)
			{
				entry.set_present(true);
				entry.set_descriptor_privilege_level(0);
				// todo: interrupt gates
				entry.set_gate_type(gate_descriptor_t::TRAP_GATE);
				entry.set_interrupt_stack_table(0);
				gdt::segment_selector_t selector;
				selector.set_index(0);
				selector.set_table(0);
				selector.set_requested_privilege_level(0);
				entry.set_segment_selector(selector);
				entry.set_offset(&default_interrupt_routine);
			}
		}

		void idt_manager::flush()
		{
			for (gate_descriptor_t& entry : m_idt.entries)
				entry = gate_descriptor_t();
		}

		void idt_manager::lidt()
		{
			m_idtr.offset = (u64)&m_idt;
			m_idtr.size = sizeof(m_idt) - 1;

			asm volatile("lidt %0" : : "m"(m_idtr));
		}
	}
}