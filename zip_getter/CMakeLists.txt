cmake_minimum_required(VERSION 3.26)
project(zip_header_getter)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE headers 
     "source/*.cpp"
)
add_executable(zip_header_getter main.cpp ${headers}) 
target_include_directories(zip_header_getter PRIVATE ${YOUR_DIRECTORY})