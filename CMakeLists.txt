cmake_minimum_required (VERSION 3.16.0)

project(McuControl LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_library(McuControl INTERFACE)
add_library(McuControl::Library ALIAS McuControl )

target_sources(McuControl
INTERFACE
    Library.h
    Library.cpp
    McuControlImpl.h
    McuControlImpl.cpp
)

target_include_directories(McuControl
INTERFACE
    .
)