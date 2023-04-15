project(lab_3)
set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

add_executable(lab3 main.c include/lab3.h src/lab3.c)
find_package(Threads REQUIRED)
target_include_directories(lab3 PRIVATE include)
target_link_libraries(lab3 PRIVATE Threads::Threads)
