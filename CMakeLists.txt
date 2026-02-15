cmake_minimum_required(VERSION 3.31)
project(commesso_viaggiatore C)

set(CMAKE_C_STANDARD 99)

add_executable(commesso_viaggiatore main.c
        Graph.c
        Item.c
        ST.c)
