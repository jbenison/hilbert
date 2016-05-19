cmake_minimum_required(VERSION 3.4)
project(hilbert)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14")

find_package(Threads REQUIRED)
if (THREADS_FOUND)
    set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()

add_subdirectory(hilbert)
add_subdirectory(benchmark)
add_subdirectory(test)