cmake_minimum_required(VERSION 3.9.6)
project(intrusive_ptr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -fsanitize=address -Wall -Wextra")

add_executable(intrusive_ptr intrusive_ptr.h main.cpp)
