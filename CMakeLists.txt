cmake_minimum_required(VERSION 3.12)

project(
        lab4
        VERSION 1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fopenmp -O2")

add_library(hit_lib hit.h hit.cpp)
add_library(args_lib args.h args.cpp)
add_executable(${PROJECT_NAME} main.cpp rand_1.cpp rand_2.cpp rand_3.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC hit_lib)
target_link_libraries(${PROJECT_NAME} PUBLIC args_lib)

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()