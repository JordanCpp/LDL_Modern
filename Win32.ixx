export module Win32;

extern "C" 
{
    __declspec(dllimport) void* __stdcall GetProcessHeap();
    __declspec(dllimport) void* __stdcall HeapAlloc(void* hHeap, unsigned int dwFlags, unsigned int dwBytes);
    __declspec(dllimport) int   __stdcall HeapFree(void* hHeap, unsigned int dwFlags, void* lpMem);
    __declspec(dllimport) void* __stdcall GetActiveWindow();
    __declspec(dllimport) int   __stdcall MessageBoxA(void* hWnd, const char* lpText, const char* lpCaption, unsigned int uType);
    __declspec(dllimport) void  __stdcall ExitProcess(unsigned int);
}
