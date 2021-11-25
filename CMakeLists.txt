cmake_minimum_required(VERSION 3.11)
project(ant)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# JSON Lib
include(FetchContent)

FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
#

# SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED) # SFML must be in the PATH
#

add_executable(ant ${SOURCES})

target_link_libraries(ant PRIVATE nlohmann_json::nlohmann_json sfml-graphics sfml-audio)