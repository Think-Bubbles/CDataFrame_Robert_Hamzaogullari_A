cmake_minimum_required(VERSION 3.27)
project(projet_dataframe C)

set(CMAKE_C_STANDARD 11)

add_executable(projet_dataframe main.c
        column.c
        column.h
        CDataframe.c
        CDataframe.h)
