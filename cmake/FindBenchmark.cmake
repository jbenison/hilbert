# - Try to find Benchmark
# Once done this will define
#  BENCHMARK_FOUND - System has Benchmark
#  BENCHMARK_INCLUDE_DIRS - The Benchmark include directories
#  BENCHMARK_LIBRARIES - The libraries needed to use Benchmark
#  BENCHMARK_DEFINITIONS - Compiler switches required for using Benchmark

find_package(PkgConfig)
pkg_check_modules(PC_BENCHMARK QUIET benchmark)
set(BENCHMARK_DEFINITIONS ${PC_BENCHMARK_CFLAGS_OTHER})

find_path(BENCHMARK_INCLUDE_DIR
      benchmark/benchmark.h
    HINTS
      ${PC_BENCHMARK_INCLUDEDIR}
      ${PC_BENCHMARK_INCLUDE_DIRS}
    PATH_SUFFIXES
      benchmark
    )

find_library(BENCHMARK_LIBRARY
    NAMES
      benchmark
    HINTS
      ${PC_BENCHMARK_LIBDIR}
      ${PC_BENCHMARK_LIBRARY_DIRS}
    )

set(BENCHMARK_LIBRARIES ${BENCHMARK_LIBRARY} )
set(BENCHMARK_INCLUDE_DIRS ${BENCHMARK_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set BENCHMARK_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Benchmark DEFAULT_MSG
    BENCHMARK_LIBRARY BENCHMARK_INCLUDE_DIR)

mark_as_advanced(BENCHMARK_INCLUDE_DIR BENCHMARK_LIBRARY)