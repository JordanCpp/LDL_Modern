cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)

set(SOURCES 
    Win32.ixx)

add_executable(main "main.cpp")
target_sources(main PUBLIC FILE_SET CXX_MODULES FILES ${SOURCES})
