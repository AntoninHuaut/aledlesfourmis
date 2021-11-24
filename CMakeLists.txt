cmake_minimum_required(VERSION 3.10)
project(ant)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) # SFML must be in the PATH
add_executable(ant ${SOURCES})
target_link_libraries(ant sfml-graphics sfml-audio)