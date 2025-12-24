
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"

cl /O2 /std:c++20 /arch:IA32 /GS- /Zc:threadSafeInit- /GR- /EHa- /c ../Win32.ixx
cl /O2 /std:c++20 /arch:IA32 /GS- /Zc:threadSafeInit- /GR- /EHa- /c ../std.ixx
cl /O2 /std:c++20 /arch:IA32 /GS- /Zc:threadSafeInit- /GR- /EHa- /c ../main.cpp

pause
