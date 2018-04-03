cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(doc EXCLUDE_FROM_ALL)

