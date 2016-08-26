
find_package(Threads REQUIRED)
if (THREADS_FOUND)
    set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif()

find_package(GTest REQUIRED)
if (GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIR})
    set(LIBS ${LIBS}  ${GTEST_LIBRARY})
    set(LIBS ${LIBS} ${GTEST_MAIN_LIBRARY})
endif()

add_executable(hilbert_test
        test_helper.h
        hilbert_test.cpp)

target_link_libraries(hilbert_test
        ${LIBS})

find_package(Benchmark REQUIRED)
if (BENCHMARK_FOUND)
    include_directories(${BENCHMARK_INCLUDE_DIR})
    set(LIBS ${LIBS} ${BENCHMARK_LIBRARY})
    set(LIBS ${LIBS} ${BENCHMARK_MAIN_LIBRARY})
endif()

add_executable(hilbert_benchmark
        ../hilbert/hilbert.h
        hilbert_benchmark.cpp)

target_link_libraries(hilbert_benchmark
        ${LIBS})
