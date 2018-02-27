cmake_minimum_required(VERSION 3.9)

project(virago_renderer C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES main.cc)

include_directories(include)

add_executable(virago ${SOURCES})

install(TARGETS virago DESTINATION bin)

