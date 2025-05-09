﻿cmake_minimum_required (VERSION 3.27 FATAL_ERROR)

# --- Name, Version, Language compilers in use.
project (blue-all VERSION 1.0.0 LANGUAGES C CXX)

# --- Includes
list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (properties)

option (BLUE_ENABLE_TESTS       "Enable unit tests" OFF)
option (BLUE_ENABLE_BENCHMARKS  "Enable benchmarks" OFF)

# --- Dependencies
add_subdirectory (dependencies)

# --- Add 'defines' to all projects
add_compile_definitions (_CRT_SECURE_NO_WARNINGS)
add_compile_definitions (DEBUG_FLAG_LOGGING=${DEBUG_FLAG_LOGGING})
add_compile_definitions (DEBUG_FLAG_MEMORY=${DEBUG_FLAG_MEMORY})
add_compile_definitions (DEBUG_FLAG_CLOCKS=${DEBUG_FLAG_CLOCKS})
add_compile_definitions (DEBUG_FLAG_POSTLOGGING=${DEBUG_FLAG_POSTLOGGING})

# --- Project's sources
add_subdirectory (project/bluelib)

if (BLUE_ENABLE_TESTS)
    add_subdirectory (project/test)
endif ()

if (BLUE_ENABLE_BENCHMARKS)
    add_subdirectory (project/measure)
endif ()
