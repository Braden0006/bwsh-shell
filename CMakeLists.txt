cmake_minimum_required(VERSION 3.30)
project(bwsh_shell C)

find_package(Curses REQUIRED)
find_package(SQLite3 REQUIRED)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

add_executable(bwsh_shell main.c
        shellLoop.c
        shell_functions.h
        create_process.c
        tokenize_line.c
        ncurses_terminal.c
        linked_list.c
        sqlite_add_record.c
        sqlite_check_command.c
        sqlite_delete_record.c)

target_link_libraries(bwsh_shell ${CURSES_LIBRARY})
target_link_libraries(bwsh_shell sqlite3)
