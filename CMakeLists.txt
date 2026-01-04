cmake_minimum_required(VERSION 3.28)
project(LegacyLinkProject LANGUAGES CXX)

set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG          "/INCREMENTAL:NO")
set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE        "/INCREMENTAL:NO")

set(CMAKE_MSVC_RUNTIME_LIBRARY_DEFAULT "") 

if(MSVC)
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        string(REPLACE "/Od"  "" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MDd" "" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MD"  "" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MTd" "" ${flag_var} "${${flag_var}}")
        string(REPLACE "/MT"  "" ${flag_var} "${${flag_var}}")
    endforeach()
endif()

set(CMAKE_GENERATOR_PLATFORM Win32)

set(CUSTOM_LINKER "${CMAKE_CURRENT_SOURCE_DIR}/make/link.exe")

add_executable(main main.cpp)

target_sources(main
    PUBLIC
        FILE_SET CXX_MODULES FILES
            Win32.ixx
            "stdcpp/cstddef.ixx"
            "stdcpp/cstdint.ixx"
            "stdcpp/cstdlib.ixx"
            "stdcpp/cpp_new.ixx"
            "stdcpp/string.ixx"
            "stdcpp/cstring.ixx"
            "stdcpp/allocator.ixx"
            "stdcpp/vector.ixx"
            "stdcpp/unique_ptr.ixx"
            "stdcpp/expected.ixx"
            "stdcpp/ostream.ixx"
            "stdcpp/windows/system.ixx"
            "stdcpp/std.ixx"
            "Graphics.ixx"
            "SDL1.ixx"
            "LDL/LDL.Vec2.ixx"
            "LDL/LDL.Vec2i.ixx"
            "LDL/LDL.Vec2u.ixx"
            "LDL/LDL.BaseWindow.ixx"
            "LDL/LDL.Enums.ixx"
            "LDL/LDL.Color.ixx"
            "LDL/Win9x/LDL.MainWindow.ixx"
            "LDL/LDL.ixx"
)

target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE
    /O2
    /arch:IA32
    /GS-
    /Zc:threadSafeInit-
    /GR-
    /EHa-
    /kernel
    /d2FH4-
)

target_link_options(main PRIVATE "/SUBSYSTEM:CONSOLE,4.0" "/NODEFAULTLIB" "/ENTRY:EntryPoint")
target_link_libraries(main PRIVATE kernel32.lib user32.lib)

set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_LINK_EXECUTABLE "\"${CUSTOM_LINKER}\" <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> /OUT:<TARGET> <LINK_LIBRARIES>")

add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/make/SDL.dll" "$<TARGET_FILE_DIR:main>")
