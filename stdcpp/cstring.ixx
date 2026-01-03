// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cstring;

export namespace std
{
	size_t strlen(const char* src)
	{
		size_t i = 0;

		while (src[i] != 0)
		{
			i++;
		}

		return i;
	}
}