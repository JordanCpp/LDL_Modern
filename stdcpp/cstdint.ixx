// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cstdint;

export namespace std
{
	using int8_t   = signed char;
	using uint8_t  = unsigned char;

	using int16_t  = signed short;
	using uint16_t = unsigned short;

	using int32_t  = signed int;
	using uint32_t = unsigned int;

	using int64_t  = signed long long;
	using uint64_t = unsigned long long;
}