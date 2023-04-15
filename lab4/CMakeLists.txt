project(lab_4)
set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

find_package(Threads REQUIRED)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
add_executable(lab4
        main.c
        src/parent.c
       )

target_link_libraries(lab4 PRIVATE rt)
target_link_libraries(lab4 PRIVATE Threads::Threads)
target_include_directories(lab4 PRIVATE include)

add_executable(child
        src/child.c
        )
target_link_libraries(child PRIVATE rt)
target_link_libraries(child PRIVATE Threads::Threads)
target_include_directories(child PRIVATE include)

add_dependencies(lab4 child)
