cmake_minimum_required(VERSION 3.20)
project(MHX3gx)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:/devkitPro/libctrpf/include)
include_directories(C:/devkitPro/libctru/include)
include_directories(Includes)
include_directories(Sources)

add_executable(MHX3gx Sources/main.cpp
        Sources/cheats.cpp
        Sources/patch.cpp
        Sources/player.cpp
        Sources/team_and_conditions.cpp)