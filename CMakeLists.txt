cmake_minimum_required(VERSION 3.10)
project(NESulator)
set(CMAKE_C_STANDARD 11)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(gui_runtime)
enable_testing()

add_test(Testulator test/TestMain.c)