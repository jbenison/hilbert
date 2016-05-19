add_library(libhilbert
        hilbert.h
        hilbert.cpp)

target_include_directories(libhilbert
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})