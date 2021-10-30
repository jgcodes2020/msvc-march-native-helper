cmake_minimum_required(VERSION 3.15)
project(cpu_test
  LANGUAGES CXX
  DESCRIPTION "test for AVX, AVX2 and AVX512"
)

add_executable(test
  test.cpp
)