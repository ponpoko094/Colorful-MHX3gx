cmake_minimum_required(VERSION 3.20)
project(Colorful-MHX3gx)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/devkitPro/libctrpf/include)
include_directories(C:/devkitPro/libctru/include)
include_directories(Includes)
include_directories(Sources)

add_executable(Colorful-MHX3gx
        Sources/main.cpp
        Sources/cheats.cpp
        Sources/patch.cpp
        Sources/team_and_conditions.cpp
        Sources/Helpers/AutoRegion.cpp
        Sources/Helpers/HoldKey.cpp
        Sources/Helpers/KeySequence.cpp
        Sources/Helpers/OSDManager.cpp
        Sources/Helpers/QuickMenu.cpp
        Sources/Helpers/Strings.cpp
        Sources/Helpers/Wrappers.cpp
        Sources/libpon/bitmap.cpp
        Sources/libpon/keyboard_plus.cpp
        Sources/libpon/osd_plus.cpp
        Sources/libpon/process_plus.cpp
        Sources/libpon/security.cpp)
