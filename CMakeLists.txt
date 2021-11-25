cmake_minimum_required(VERSION 3.11)
project(ant)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp") # Load cpp src files
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}) # Copy assets folder in the build folder

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) # SFML must be in the PATH
add_executable(ant ${SOURCES})
target_link_libraries(ant sfml-graphics sfml-audio)