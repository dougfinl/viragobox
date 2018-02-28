cmake_minimum_required(VERSION 3.9)

project(virago_renderer C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

set(SOURCES main.cc ViragoBox.h ViragoBox.cc SFMLRenderer.h SFMLRenderer.cc DMXListener.h DMXListener.cc)

include_directories(include)

add_executable(virago ${SOURCES})

# SFML2
find_package(SFML 2 REQUIRED system window graphics)
target_include_directories(virago PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(virago ${SFML_LIBRARIES})

# OLA
find_package(PkgConfig REQUIRED)
pkg_check_modules(OLA REQUIRED libola)
target_include_directories(virago PUBLIC ${OLA_INCLUDE_DIRS})
target_link_libraries(virago ${OLA_LIBRARIES})
target_compile_options(virago PUBLIC ${OLA_CFLAGS_OTHER})

install(TARGETS virago DESTINATION bin)

