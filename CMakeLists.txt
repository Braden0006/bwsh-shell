cmake_minimum_required(VERSION 3.30)
project(bwsh_shell C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

add_executable(bwsh_shell main.c
        shellLoop.c
        shell_functions.h
        create_process.c
        tokenize_line.c)
