cmake_minimum_required(VERSION 3.29)
project(advent_of_code C)

set(CMAKE_C_STANDARD 23)

add_executable(advent_of_code main.c
        src/1/advent-of-code-1.c
        src/1/advent-of-code-1.h
        src/2/advent-of-code-2.c
        src/2/advent-of-code-2.h
        src/util/string.c
        src/util/string.h
        src/util/file.c
        src/util/file.h
        src/3/advent-of-code-3.c
        src/3/advent-of-code-3.h)
