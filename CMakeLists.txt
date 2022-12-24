cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(
    sudoku
    VERSION 1.0.0
    DESCRIPTION "Sudoku Project"
    LANGUAGES CXX
)

include_directories(include)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB SOURCES "src/*.cxx")

add_executable(
    sudoku 
    "${SOURCES}"
)