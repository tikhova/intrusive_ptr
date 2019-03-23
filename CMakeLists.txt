cmake_minimum_required(VERSION 3.9.6)
project(intrusive_ptr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(intrusive_ptr main.cpp intrusive_ptr.h)
