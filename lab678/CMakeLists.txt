project(lab_678)
set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

add_library(topology STATIC src/topology.cpp include/topology.h)
add_library(zmfq STATIC src/zmqf.cpp include/zmqf.h)

target_include_directories(topology PRIVATE include)
target_include_directories(zmfq PRIVATE include)

target_link_libraries(topology PRIVATE zmq)
target_link_libraries(zmfq PRIVATE zmq)

add_executable(client client.cpp)
target_link_libraries(client PRIVATE topology)
target_link_libraries(client PRIVATE zmfq)

add_executable(server server.cpp)
target_link_libraries(server PRIVATE topology)
target_link_libraries(server PRIVATE zmfq)


find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )

target_include_directories(client PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_include_directories(server PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(client PUBLIC ${ZeroMQ_LIBRARY})
target_link_libraries(server PUBLIC ${ZeroMQ_LIBRARY})

target_include_directories(client PRIVATE include)
target_include_directories(server PRIVATE include)



