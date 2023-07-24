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

namespace std
{
    using i8    = signed char;
    using u8    = unsigned char;
    using i16   = signed short;
    using u16   = unsigned short;
    using i32   = signed long;
    using u32   = unsigned long;
    using i64   = signed long long;
    using u64   = unsigned long long;

    using f32   = float;
    using f64   = double;
    using f128  = long double;
}

#ifdef GLOBAL_NUMERICS
using std::i8;
using std::u8;
using std::i16;
using std::u16;
using std::i32;
using std::u32;
using std::i64;
using std::u64;

using std::f32;
using std::f64;
using std::f128;
#endif