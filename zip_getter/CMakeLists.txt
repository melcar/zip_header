set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 3.26)
project(zip_header_getter)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE headers 
     "source/*.cpp"
)
add_compile_options(-std=c++23 -O3 -ggdb3 -march=core2 -fno-common -pipe -Werror -Wall -Wextra -Wvla -Wreorder -Wnon-virtual-dtor -Wpacked -Wcast-align -Wenum-compare -Wpointer-arith -Wunused -Wuninitialized -Winit-self -Winvalid-pch -Woverlength-strings -Woverloaded-virtual -Woverflow -Wsequence-point -Wno-unknown-pragmas -Wtrigraphs -finput-charset=UTF-8 -Wpacked-bitfield-compat -Wlogical-op -Wsync-nand -Wstrict-null-sentinel -Wnoexcept)
include_directories(header)
add_executable(zip_header_getter main.cpp ${headers}) 
target_include_directories(zip_header_getter PRIVATE ${YOUR_DIRECTORY})
include_directories(zip_getter zip_getter/header)