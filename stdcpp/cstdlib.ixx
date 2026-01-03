// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cstdlib;

import Win32;
import stdcpp.cstddef;

export namespace std
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
}