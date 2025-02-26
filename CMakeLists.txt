cmake_minimum_required(VERSION 3.10)
project(MicrogradCpp)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Include headers
include_directories(src)

file(GLOB SOURCES src/*.cpp src/tests/*.cpp)

# Create playground executable
add_executable(playground.app Main.cpp ${SOURCES})

