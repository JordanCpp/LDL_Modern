// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module stdcpp.ostream;

import stdcpp.cstdint;
import stdcpp.cstring;
import stdcpp.string;
import stdcpp.system;

export namespace std
{
    class ostream
    {
    private:

    public:
        ostream& operator<<(const string& str)
        {
            system::write(str.c_str(), str.size());

            return *this;
        }

        ostream& operator<<(const char* str)
        {
            system::write(str, strlen(str));

            return *this;
        }

        ostream& operator<<(char c)
        {
            system::write(&c, 1);

            return *this;
        }

        ostream& operator<<(ostream& (*pf)(ostream&))
        {
            return pf(*this);
        }
    };

    inline ostream cout;

    ostream& endl(ostream& os)
    {
        os << '\n';

        return os;
    }
}