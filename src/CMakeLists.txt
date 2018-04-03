cmake_minimum_required(VERSION 3.7.2)

project(virago_renderer C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

set(SOURCES main.cc ViragoBox.h ViragoBox.cc SFMLRenderer.h SFMLRenderer.cc DMXListener.h DMXListener.cc OLABoostLogDestination.h OLABoostLogDestination.cc)

include_directories(include)

add_executable(viragobox ${SOURCES})

# SFML2
find_package(SFML 2 REQUIRED system window graphics)
target_include_directories(viragobox PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(viragobox ${SFML_LIBRARIES})

# OLA
find_package(PkgConfig REQUIRED)
pkg_check_modules(OLA REQUIRED libola)
target_include_directories(viragobox PUBLIC ${OLA_INCLUDE_DIRS})
target_link_libraries(viragobox ${OLA_LIBRARIES})
target_compile_options(viragobox PUBLIC ${OLA_CFLAGS_OTHER})

# Boost
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.62 COMPONENTS log program_options REQUIRED)
target_include_directories(viragobox PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(viragobox ${Boost_LIBRARIES})

install(TARGETS viragobox DESTINATION bin)

