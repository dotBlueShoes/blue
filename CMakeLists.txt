cmake_minimum_required (VERSION 3.27 FATAL_ERROR)
project (blue-all VERSION 1.0.0 LANGUAGES C CXX)


# --- Add global settings (for all of the subprojects).
list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (properties)


option (BLUE_ENABLE_TESTS       "Enable unit tests"                 OFF)
option (BLUE_ENABLE_BENCHMARKS  "Enable benchmarks"                 OFF)
option (BLUE_ENABLE_CCC         "Enable cpu-clock-cycles measures"  OFF)


# --- Dependencies directory.
add_subdirectory (dependencies)


# --- Project's sources.
add_subdirectory (project/bluelib)


if (BLUE_ENABLE_TESTS)

    # Add Google-Benchmark dependency.
    add_subdirectory (${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest)

    add_subdirectory (project/blueunit)

endif ()


if (BLUE_ENABLE_BENCHMARKS)

    if (NOT BLUE_ENABLE_TESTS)

        # Add Google-Benchmark dependency.
        add_subdirectory (${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest)
        
    endif()

    # Add Google-Benchmark.
    add_subdirectory (${CMAKE_SOURCE_DIR}/external/benchmark ${CMAKE_BINARY_DIR}/googlebenchmark)

    add_subdirectory (project/bluemetric)

endif ()


if (BLUE_ENABLE_CCC)

    add_subdirectory (project/bluecycle)

endif ()
