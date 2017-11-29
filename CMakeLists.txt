cmake_minimum_required(VERSION 2.6)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/../Compile/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})
SET(EXECUTABLE_OUTPUT_PATH ${dir})
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})

project(Converter)
include_directories("./pg")
add_executable(Converter 
Converter.cpp 
Converter.h
ListEmulator.cpp 
ListEmulator.h
ListContainer.cpp 
ListContainer.h)

