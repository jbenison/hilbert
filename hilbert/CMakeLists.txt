set(HILBERT_PUBLIC_H
        hilbert.h)

set(HILBERT_SOURCES
        ${HILBERT_PUBLIC_H}
        hilbert.cpp)

add_library(libhilbert
        ${HILBERT_SOURCES})

target_include_directories(libhilbert
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})