// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cstring;

export namespace std
{
	[[nodiscard]]
	constexpr int strcmp(const char* s1, const char* s2)
	{
		while (*s1 && (*s1 == *s2)) 
		{
			s1++;
			s2++;
		}

		return static_cast<int>(static_cast<unsigned char>(*s1)) - static_cast<int>(static_cast<unsigned char>(*s2));
	}

	[[nodiscard]]
	constexpr size_t strlen(const char* src)
	{
		size_t i = 0;

		while (src[i] != 0)
		{
			i++;
		}

		return i;
	}
}