cmake_minimum_required(VERSION 3.20)
project(Colorful-MHX3gx)

set(CMAKE_CXX_STANDARD 20)

include_directories(C:/devkitPro/libctrpf/include)
include_directories(C:/devkitPro/libctru/include)
include_directories(Includes)
include_directories(Sources)

file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS
        "Sources/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_LIST})
