// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.cstdlib;

import stdcpp.cstddef;
import stdcpp.system;

export namespace std
{
    void* malloc(size_t size)
    {
        return system::malloc(size);
    }

    void free(void* ptr)
    {
        if (ptr)
        {
            system::free(ptr);
        }
    }
}