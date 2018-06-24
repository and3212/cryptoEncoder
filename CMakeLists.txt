cmake_minimum_required(VERSION 3.5)
project(encrypt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2 -std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCE src/main.cpp)

add_executable(encrypt ${SOURCE})
target_link_libraries(encrypt ${OpenCV_LIBS})
