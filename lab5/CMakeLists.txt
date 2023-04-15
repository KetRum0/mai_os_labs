project(lab_5)
set(CMAKE_C_STANDARD 11)
cmake_minimum_required(VERSION 3.16)

add_library(d1_static STATIC src/lib1.c include/func.h)
add_library(d2_static STATIC src/lib2.c include/func.h)
add_library(d1_dynamic SHARED src/lib1.c include/func.h)
add_library(d2_dynamic SHARED src/lib2.c include/func.h)

# target_include_directories(d1_static PRIVATE include)
# target_include_directories(d2_static PRIVATE include)
# target_include_directories(d1_dynamic PRIVATE include)
# target_include_directories(d2_dynamic PRIVATE include)

add_executable(main_static_1 main_static.c)
add_executable(main_static_2 main_static.c)
add_executable(main_dynamic main_dynamic.c)

target_include_directories(main_static_1 PRIVATE include)
target_include_directories(main_static_2 PRIVATE include)

target_link_libraries(main_dynamic ${CMAKE_DL_LIBS})
target_link_libraries(main_static_1 PRIVATE d1_static)
target_link_libraries(main_static_2 PRIVATE d2_static)
target_include_directories(main_dynamic PRIVATE include)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(d1_dynamic PUBLIC ${MATH_LIBRARY})
    target_link_libraries(d2_dynamic PUBLIC ${MATH_LIBRARY})
    target_link_libraries(main_static_1 PUBLIC ${MATH_LIBRARY})
    target_link_libraries(main_static_2 PUBLIC ${MATH_LIBRARY})
    target_link_libraries(main_dynamic PUBLIC ${MATH_LIBRARY})
endif()
