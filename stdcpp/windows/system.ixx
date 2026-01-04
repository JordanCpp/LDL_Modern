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

extern "C" void EntryPoint()
{
	int result = main();

	ExitProcess(result);
}

using namespace std;

export namespace system
{
	void* malloc(size_t size)
	{
		return HeapAlloc(GetProcessHeap(), 0, size);
	}

	void free(void* ptr)
	{
		if (ptr)
		{
			HeapFree(GetProcessHeap(), 0, ptr);
		}
	}

	class Writer
	{
	public:
		Writer() :
			_handle(nullptr)
		{
			_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		void Write(const char* source, std::size_t size)
		{
			if (source)
			{
				DWORD written;
				WriteFile(_handle, source, (uint32_t)strlen(source), &written, nullptr);
			}
		}
	private:
		HANDLE _handle;
	};
}