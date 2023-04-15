project(lab_tests)
set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_test lab2_test.cpp ../lab2/src/parent.c ../lab2/include/parent.h
       )

target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab2/include)

add_test(lab2_test lab2_test)


add_executable(lab3_test lab3_test.cpp ../lab3/src/lab3.c ../lab3/include/lab3.h) 
target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)


add_test(lab3_test lab3_test)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
add_executable(lab4_test lab4_test.cpp ../lab4/src/parent.c ../lab4/include/parent.h
       )
target_link_libraries(lab4_test PRIVATE rt)
target_link_libraries(lab4_test PRIVATE GTest::GTest)
target_include_directories(lab4_test PRIVATE ../lab4/include)

add_test(lab4_test lab4_test)


add_executable(lab5_1_test lab5_test.cpp ../lab5/include/func.h ../lab5/src/lib1.c )

target_link_libraries(lab5_1_test PRIVATE GTest::GTest)
target_include_directories(lab5_1_test PRIVATE ../lab5/include)

add_test(lab5_1_test lab5_1_test)

add_executable(lab5_2_test lab5_test.cpp ../lab5/include/func.h ../lab5/src/lib2.c )

target_link_libraries(lab5_2_test PRIVATE GTest::GTest)
target_include_directories(lab5_2_test PRIVATE ../lab5/include)

add_test(lab5_2_test lab5_2_test)
