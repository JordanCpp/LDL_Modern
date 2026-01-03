// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cpp_new;

import stdcpp.cstdlib;

export
{
	void* operator new(size_t bytes)
	{
		return std::malloc(bytes);
	}

	void operator delete(void* ptr)
	{
		return std::free(ptr);
	}

	void* operator new[](size_t bytes)
	{
		return ::operator new(bytes);
	}

	void operator delete[](void* ptr)
	{
		::operator delete(ptr);
	}

	void* operator new(size_t bytes, void* ptr)
	{
		return ptr;
	}

	void* operator new[](size_t bytes, void* ptr)
	{
		return ptr;
	}

	void __cdecl operator delete(void* ptr, size_t size) noexcept
	{
		::operator delete(ptr);
	}

	void __cdecl operator delete[](void* ptr, size_t size) noexcept
	{
		::operator delete[](ptr);
	}
}