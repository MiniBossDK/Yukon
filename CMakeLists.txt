cmake_minimum_required(VERSION 3.14)
project(Yukon)

set(USER_INTERFACE ON)

option(USER_INTERFACE "Build with user interface" ON)
option(USER_INTERFACE "Build with terminal" OFF)

add_subdirectory(src)
add_subdirectory(tests)