// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.system;

import Win32;
import stdcpp.cstddef;
import stdcpp.cstdint;
import stdcpp.cstring;

extern "C" int main();

static HANDLE currentProcessHeap = nullptr;

extern "C" void EntryPoint()
{
	currentProcessHeap = GetProcessHeap();

	int result = main();

	ExitProcess(result);
}

using namespace std;

export namespace system
{
	void* malloc(size_t size)
	{
		return HeapAlloc(currentProcessHeap, 0, size);
	}

	void free(void* ptr)
	{
		if (ptr)
		{
			HeapFree(currentProcessHeap, 0, ptr);
		}
	}

	void write(const char* source, size_t length)
	{
		if (source)
		{
			DWORD  written = 0;
			HANDLE handle  = GetStdHandle(STD_OUTPUT_HANDLE);

			WriteFile(handle, source, length, &written, nullptr);
		}
	}
}