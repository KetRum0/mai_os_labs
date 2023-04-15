project(lab_2)
set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

add_executable(lab2
        main.c
        src/parent.c
       )

target_include_directories(lab2 PRIVATE include)

add_executable(child
        src/child.c
        )

target_include_directories(child PRIVATE include)

add_dependencies(lab2 child)
