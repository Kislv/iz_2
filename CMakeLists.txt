cmake_minimum_required(VERSION 3.16)

project(sum_columns_project)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #
#set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
#set(CMAKE_CXX_FLAGS " -Wall -Werror -Wpedantic -fprofile-arcs -ftest-coverage")

include_directories(project/include) #

add_library(matrix_operate STATIC project/src/matrix_operations.c project/src/consistent_sum_columns.c project/include/matrix_operations.h)

add_executable(main project/src/main.c)

target_link_libraries(main matrix_operate)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
#include_directories(${GTEST_INCLUDE_DIRS})
add_executable(matrix_test project/tests/matrix_test.cpp project/src/consistent_sum_columns.c)
target_link_libraries(matrix_test ${GTEST_LIBRARIES} matrix_operate)
target_link_libraries(matrix_test gtest pthread)
#target_link_libraries(matrix_test ${GTEST_LIBRARIES} matrix_operate)







# option(WITH_SANITIZERS "check coverage")
# if(WITH_SANITIZERS)
#     add_compile_options(-fsanitize=address)
#     add_link_options(-fsanitize=address)
#     set(BUILT_TEST 1)
# endif()

#set(LIB_SOURCE_FILES fib.cpp)
#add_library(fib STATIC ${LIB_SOURCE_FILES})

#add_executable(main main.cpp)
#target_link_libraries(main fib)
  
#enable_testing()
#find_package(GTest REQUIRED)

#include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(fib_test fib_test.cpp)
#target_link_libraries(fib_test gtest pthread)
#target_link_libraries(fib_test ${GTEST_LIBRARIES} fib)