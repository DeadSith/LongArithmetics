cmake_minimum_required(VERSION 3.6)
project(LongArithmetics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES T4.cpp BigInt.cpp BigInt.h BigIntInherited.cpp BigIntInherited.h)
add_executable(BigInt ${SOURCE_FILES})