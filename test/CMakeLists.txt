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
        libhilbert
        ${LIBS})
