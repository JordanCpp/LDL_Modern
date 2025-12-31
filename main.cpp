// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

import std;
import Win32;

LRESULT __stdcall WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) 
    {
    case WM_DESTROY:

        //PostQuitMessage(0);
        break;
    }

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

int main()
{
    MSG msg      = {};
    HWND hwnd    = {};
    WNDCLASSA wc = {};

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.lpszClassName = "Window";
    wc.hInstance     = GetModuleHandleA(nullptr);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = nullptr;
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursorA(nullptr, IDC_ARROW);
    wc.hIcon         = LoadIconA(nullptr, IDI_APPLICATION);

    RegisterClassA(&wc);
    hwnd = CreateWindowExA(0L, wc.lpszClassName, "Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 350, 250, nullptr, nullptr, wc.hInstance, nullptr);

    while (GetMessageA(&msg, nullptr, 0, 0)) 
    {
        DispatchMessageA(&msg);
    }

    return 0;
}
