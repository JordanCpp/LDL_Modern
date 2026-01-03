// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.ostream;

import Win32;
import stdcpp.cstdint;
import stdcpp.cstring;
import stdcpp.cpp_string;

export namespace std
{
    class ostream
    {
    private:
        void* _handle;

    public:
        constexpr ostream() noexcept : _handle(nullptr) {}

        void init()
        {
            if (!_handle)
            {
                _handle = GetStdHandle(STD_OUTPUT_HANDLE);
            }
        }

        ostream& operator<<(const string& str)
        {
            init();

            DWORD written;
            WriteFile(_handle, str.c_str(), (uint32_t)str.size(), &written, nullptr);

            return *this;
        }

        ostream& operator<<(const char* str)
        {
            init();

            if (str)
            {
                DWORD written;
                WriteFile(_handle, str, (uint32_t)strlen(str), &written, nullptr);
            }

            return *this;
        }

        ostream& operator<<(char c)
        {
            init();

            DWORD written;
            WriteFile(_handle, &c, 1, &written, nullptr);

            return *this;
        }
    };

    inline ostream cout;
    inline constexpr char endl = '\n';
}