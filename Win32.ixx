// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

export module Win32;

extern "C" 
{
    /********************************************************************************************************************
                                                             Types
    ********************************************************************************************************************/
    using HANDLE  = void*;
    using HWND    = HANDLE;
    using HMODULE = HANDLE;
    using BOOL    = int;
    using LPCSTR  = const char*;
    using PROC    = int(__stdcall*)();

    /********************************************************************************************************************
                                                            Process
    ********************************************************************************************************************/
    __declspec(dllimport) void* __stdcall GetProcessHeap();
    __declspec(dllimport) void  __stdcall ExitProcess(unsigned int);

    /********************************************************************************************************************
                                                             Heap
    ********************************************************************************************************************/
    __declspec(dllimport) void* __stdcall HeapAlloc(HANDLE hHeap, unsigned int dwFlags, unsigned int dwBytes);
    __declspec(dllimport) int   __stdcall HeapFree(HANDLE hHeap, unsigned int dwFlags, void* lpMem);

    /********************************************************************************************************************
                                                             Window
    ********************************************************************************************************************/
    __declspec(dllimport) void* __stdcall GetActiveWindow();
    __declspec(dllimport) int   __stdcall MessageBoxA(HWND hWnd, const char* lpText, const char* lpCaption, unsigned int uType);

    /********************************************************************************************************************
                                                            Library
    ********************************************************************************************************************/
    __declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR lpLibFileName);
    __declspec(dllimport) BOOL    __stdcall FreeLibrary(HMODULE hLibModule);
    __declspec(dllimport) PROC    __stdcall GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
}
