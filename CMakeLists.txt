cmake_minimum_required(VERSION 3.16)

project(sum_columns_project)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #
set(CMAKE_C_FLAGS "-g -Og -std=gnu99 -static-libasan -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage") # -g -Og -std=gnu99 -static-libasan
set(CMAKE_CXX_FLAGS " -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
SET(MYCOMPILE_FLAGS "-std=c11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address") #
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address") #

include_directories(project/include) #

add_library(sum_consistent STATIC project/src/matrix_operations.c project/src/consistent_sum_columns.c project/include/matrix_operations.h)

add_library(sum_parallel SHARED project/src/matrix_operations.c project/src/parallel_sum_columns.c project/include/matrix_operations.h)

add_executable(consistent project/src/main.c)

add_executable(parallel project/src/main.c)

#add_executable(stress_test project/src/stress_test.c)

#add_executable(trash_test project/src/trash_test.c) # trash


target_link_libraries(consistent sum_consistent)
target_link_libraries(parallel sum_parallel)
#target_link_libraries(stress_test dl sum_consistent sum_parallel)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
#include_directories(${GTEST_INCLUDE_DIRS})
add_executable(matrix_test_consistent project/tests/matrix_test.cpp project/src/consistent_sum_columns.c)
add_executable(matrix_test_parallel project/tests/matrix_test.cpp project/src/parallel_sum_columns.c)

add_executable(stress_gtest project/tests/stress_gtest.cpp)#project/src/parallel_sum_columns.c project/src/consistent_sum_columns.c

target_link_libraries(matrix_test_consistent ${GTEST_LIBRARIES} sum_consistent)
target_link_libraries(matrix_test_consistent gtest pthread) #!
target_link_libraries(matrix_test_parallel ${GTEST_LIBRARIES} sum_parallel)
target_link_libraries(matrix_test_parallel gtest pthread) #!

target_link_libraries(stress_gtest ${GTEST_LIBRARIES} dl sum_parallel sum_consistent)
target_link_libraries(stress_gtest gtest pthread) #!
#target_link_libraries(matrix_test_consistent ${GTEST_LIBRARIES} matrix_operate)

# execute_process(
#     COMMAND bash "-c" "astyle -n project/src/*.c" 
# )