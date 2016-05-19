find_package(Benchmark REQUIRED)
if (BENCHMARK_FOUND)
    include_directories(${BENCHMARK_INCLUDE_DIR})
    set(LIBS ${LIBS} ${BENCHMARK_LIBRARY})
    set(LIBS ${LIBS} ${BENCHMARK_MAIN_LIBRARY})
endif()

add_executable(hilbert_benchmark
        hilbert_benchmark.cpp)

target_link_libraries(hilbert_benchmark
        libhilbert
        ${LIBS})