// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

import std;
import Win32;

int main()
{
    std::vector<int> vec;

    std::string title   = "Hello Habr!";
    std::string message = "Crazy programming!";

    MessageBoxA(GetActiveWindow(), title.c_str(), message.c_str(), 0x00000000L);

    return 0;
}
