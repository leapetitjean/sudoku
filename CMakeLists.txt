cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

project(
    sudoku
    VERSION 1.0.0
    DESCRIPTION "Sudoku Project"
    LANGUAGES CXX
)

include_directories(include)

file(GLOB SOURCES "src/*.cxx")

add_executable(
    sudoku 
    "${SOURCES}"
)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cxx")

add_library(sudoku_lib STATIC "${SOURCES}")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TESTS "test/*.cxx")

add_executable(
    tests
    "${TESTS}"
)

target_link_libraries(
    tests
    sudoku_lib
    GTest::gtest_main
)

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

include(GoogleTest)
gtest_discover_tests(tests)