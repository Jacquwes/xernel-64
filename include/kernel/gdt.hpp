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
		/// <summary>
		/// Describes a long mode segment descriptor.
		/// </summary>
		struct segment_descriptor_t
		{
			/// <summary>
			/// Describes a code or data segment access byte.
			/// </summary>
			struct access_byte_t
			{
				/// <summary>
				/// Creates an empty access byte.
				/// </summary>
				access_byte_t() = default;

				/// <summary>
				/// Creates a new access byte with the given value.
				/// </summary>
				/// <param name="value"></param>
				access_byte_t(u8 value);

				/// <summary>
				/// Raw value of the access byte.
				/// </summary>
				u8 value;

				/// <summary>
				/// Type of the segment descriptor.
				/// </summary>
				enum descriptor_type_t
				{
					SYSTEM = 0x0,
					CODE_OR_DATA = 0x1,
				};

				/// <summary>
				/// For data segments: whether the segment grows up or down.
				/// </summary>
				enum direction_t
				{
					GROW_UP = 0x0,
					GROW_DOWN = 0x1,
				};

				/// <summary>
				/// For code segments: describes from which ring the segment can be accessed.
				/// </summary>
				enum conforming_t
				{
					SAME_RING = 0x0,
					LOWER_RING = 0x1,
				};

				/// <summary>
				/// For code and data segments: whether is data or code.
				/// </summary>
				enum executable_t
				{
					DATA = 0x0,
					CODE = 0x1,
				};

				/// <returns>
				/// Whether the segment has been accessed.
				/// </returns>
				bool get_accessed() const;

				/// <summary>
				/// Set the accessed bit. Should be set to 0, it will be modified by the CPU.
				/// </summary>
				/// <param name="accessed">New value for the accessed bit.</param>
				void set_accessed(bool accessed);



				/// <returns>
				/// For code segments: whether the segment is readable.
				/// For data segments: segment is always readable.
				/// </returns>
				bool get_readable() const;

				/// <summary>
				/// Set the readable bit.
				/// </summary>
				/// <param name="readable">Whether the segment should be readable.</param>
				void set_readable(bool readable);



				/// <returns>
				/// For data segments: whether the segment is writable.
				/// For code segments: segment is never writable.
				/// </returns>
				bool get_writable() const;

				/// <summary>
				/// Set the writable bit.
				/// </summary>
				/// <param name="writable">Whether the segment should be writable.</param>
				void set_writable(bool writable);



				/// <returns>
				/// For data segments: 0 if the segment grows up, 1 if it grows down.
				/// </returns>
				direction_t get_direction() const;

				/// <summary>
				/// Set the direction bit.
				/// </summary>
				/// <param name="direction">New value for the direction bit.</param>
				void set_direction(direction_t direction);



				/// <returns>
				/// For code segments: whether the segment can be accessed from a lower ring.
				/// </returns>
				conforming_t get_conforming() const;

				/// <summary>
				/// Set the conforming bit.
				/// </summary>
				/// <param name="conforming">New value for the conforming bit.</param>
				void set_conforming(conforming_t conforming);



				/// <returns>
				/// For code and data segments: whether the segment is data or code.
				/// </returns>
				executable_t get_executable() const;

				/// <summary>
				/// Set the executable bit.
				/// </summary>
				/// <param name="executable">New value for the executable bit.</param>
				void set_executable(executable_t executable);



				/// <returns>
				/// Whether the segment is a system segment or a code/data segment.
				/// </returns>
				descriptor_type_t get_descriptor_type() const;

				/// <summary>
				/// Set the descriptor type bit.
				/// </summary>
				/// <param name="type">New value for the descriptor type bit.</param>
				void set_descriptor_type(descriptor_type_t type);



				/// <returns>
				/// Contains the privilege level of the segment. 0 is the highest privilege level.
				/// </returns>
				u8 get_privilege_level() const;

				/// <summary>
				/// Set the privilege level of the segment.
				/// </summary>
				/// <param name="privilege_level">New value for the privilege level.</param>
				void set_privilege_level(u8 privilege_level);



				/// <returns>
				/// Whether the segment is present in memory. Must be set to 1.
				/// </returns>
				bool get_present() const;

				/// <summary>
				/// Set the present bit.
				/// </summary>
				/// <param name="present">New value for the present bit.</param>
				void set_present(bool present);
			} __attribute__((packed));



			/// <summary>
			/// System access byte. Used for system segments.
			/// </summary>
			struct system_access_byte_t : access_byte_t
			{
				/// <summary>
				/// Create a new system access byte that is empty.
				/// </summary>
				system_access_byte_t() = default;

				/// <summary>
				/// Create a new system access byte with the given value.
				/// </summary>
				/// <param name="value">Value of the system access byte.</param>
				system_access_byte_t(u8 value);

				/// <summary>
				/// Raw value of the system access byte.
				/// </summary>
				u8 value;

				/// <summary>
				/// Type of the system segment.
				/// </summary>
				enum segment_type_t : u8
				{
					/// <summary>
					/// Local descriptor table.
					/// </summary>
					LDT = 0x2,
					/// <summary>
					/// Task state segment.
					/// </summary>
					TSS_AVAILABLE = 0x9,
					/// <summary>
					/// Task state segment.
					/// </summary>
					TSS_BUSY = 0xB,
				};



				/// <returns>
				/// Type of the system segment.
				/// </returns>
				segment_type_t get_segment_type() const;

				/// <summary>
				/// Set the segment type.
				/// </summary>
				/// <param name="type">New value for the segment type.</param>
				void set_segment_type(segment_type_t type);
			} __attribute__((packed));



			/// <summary>
			/// Flags of a segment descriptor.
			/// </summary>
			struct flags_t
			{
				/// <summary>
				/// Create a new flags object that is empty.
				/// </summary>
				flags_t() = default;

				/// <summary>
				/// Create a new flags object with the given value.
				/// </summary>
				/// <param name="value">Value of the flags.</param>
				flags_t(u8 value);

				/// <summary>
				/// Raw value of the flags.
				/// </summary>
				u8 value;



				/// <returns>
				/// Whether the segment is a long mode segment. If set, the size bit should be clear.
				/// </returns>
				u8 get_long_mode() const;

				/// <summary>
				/// Set the long mode bit.
				/// </summary>
				///	<param name="long_mode">New value for the long mode bit.</param>
				void set_long_mode(u8 long_mode);



				// todo: define an enum for this
				/// <returns>
				/// Whether the segment is a 16 bit segment or a 32 bit segment. If set, the long mode bit should be clear.
				/// </returns>
				u8 get_size() const;

				/// <summary>
				/// Set the size bit.
				/// </summary>
				/// <param name="size">New value for the size bit.</param>
				void set_size(u8 size);



				// todo: define an enum for this
				/// <returns>
				/// Indicates the size is scaled by. 0 = 1B granularity. 1 = 4KiB granularity.
				/// </returns>
				u8 get_granularity() const;

				/// <summary>
				/// Set the granularity bit.
				/// </summary>
				/// <param name="granularity">New value for the granularity bit.</param>
				void set_granularity(u8 granularity);
			} __attribute__((packed));

			/// <summary>
			/// Lower 64 bits of a segment descriptor.
			/// </summary>
			u64 data_low;

			/// <summary>
			/// Upper 64 bits of a segment descriptor.
			/// </summary>
			u64 data_high;

			/// <returns>
			/// The limit of the segment.
			/// </returns>
			u32 get_limit() const;

			/// <summary>
			/// Set the limit of the segment.
			/// </summary>
			/// <param name="limit/>New value for the limit.</param>
			void set_limit(u32 limit);

			// todo: implement base high
			/// <returns>
			/// The base of the segment.
			/// </returns>
			u64 get_base_low() const;
			u64 get_base_high() const;

			/// <summary>
			/// Set the base of the segment.
			/// </summary>
			/// <param name="base">New value for the base.</param>
			void set_base_low(u64 base);
			void set_base_high(u64 base);

			/// <returns>
			/// The access byte of the segment.
			/// </returns>
			access_byte_t get_access_byte() const;

			/// <summary>
			/// Set the access byte of the segment.
			/// </summary>
			/// <param name="access_byte">New value for the access byte.</param>
			void set_access_byte(access_byte_t access_byte);

			/// <returns>
			/// The flags of the segment.
			/// </returns>
			flags_t get_flags() const;

			/// <summary>
			/// Set the flags of the segment.
			/// </summary>
			/// <param name="flags">New value for the flags.</param>
			void set_flags(flags_t flags);
		} __attribute__((packed));

		/// <summary>
		/// Global descriptor table.
		/// </summary>
		struct gdt
		{
			/// <summary>
			/// Store the entries of the GDT.
			/// </summary>
			segment_descriptor_t entries[8];
		} __attribute__((packed));

		/// <summary>
		/// Global descriptor table manager.
		/// </summary>
		class gdt_manager
		{
		public:
			/// <summary>
			/// Singleton instance of the GDT manager.
			/// </summary>
			static gdt_manager* instance;

			/// <summary>
			/// Create a new GDT manager.
			/// </summary>
			gdt_manager();

			/// <returns>
			/// One of the entries of the GDT.
			/// </returns>
			/// <param name="index">Index of the entry to get.</param>
			segment_descriptor_t get_entry(u8 index) const;

			/// <summary>
			/// Set one of the entries of the GDT.
			/// </summary>
			/// <param name="index">Index of the entry to set.</param>
			void set_entry(u8 index, segment_descriptor_t entry);

			/// <summary>
			/// Load a default GDT.
			/// </summary>
			void load_default();

			/// <summary>
			/// Flush the GDT.
			/// </summary>
			void flush();

			/// <summary>
			/// Calls lgdt with the managed GDT.
			/// </summary>
			void lgdt();

		private:
			gdt m_gdt;
			u64 m_gdtr;
		};
	}
}