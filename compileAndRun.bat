@echo off
set PATH=".\CMake\bin\";%PATH%
cmake -G"MinGW Makefiles" -S . -B build
cmake --build build
cd build
ant.exe