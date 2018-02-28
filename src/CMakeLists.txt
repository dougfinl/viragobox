cmake_minimum_required(VERSION 3.9)

project(virago_renderer C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

set(SOURCES main.cc SFMLRenderer.h SFMLRenderer.cc)

include_directories(include)

add_executable(virago ${SOURCES})

find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(virago ${SFML_LIBRARIES})
endif()

install(TARGETS virago DESTINATION bin)

