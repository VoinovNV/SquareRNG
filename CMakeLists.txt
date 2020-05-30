cmake_minimum_required(VERSION 3.5)

project(SquareRNG LANGUAGES CXX)

find_package(benchmark REQUIRED)
add_executable(${PROJECT_NAME} 
src/main.cpp
src/intr_rng.hpp
src/intr_rng.cpp
src/rng.hpp
src/rng.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark_main)
