cmake_minimum_required (VERSION 3.27 FATAL_ERROR)
project (BLUELIB VERSION 1.0.0 LANGUAGES C CXX)


# Detect whether we're in sub-project or main-project mode.
if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)

    message ("-- Constructing BLUELIB in main-project mode!")

    # --- Add global settings (for all of the subprojects)
    list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)
    include (properties)

    # --- Dependencies directory.
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies ${CMAKE_BINARY_DIR}/../dependencies)

endif ()


# --- Define a 'library' with it's 'headers'
set (BLUELIB_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
add_library (BLUELIB INTERFACE)
target_include_directories (BLUELIB INTERFACE ${BLUELIB_INC_DIR})
