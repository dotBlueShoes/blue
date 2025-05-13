cmake_minimum_required (VERSION 3.27 FATAL_ERROR)
project (BLUECYCLE VERSION 1.0.0 LANGUAGES C CXX)


# Detect whether we're in sub-project or main-project mode.
if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)

    message ("-- Constructing BLUECYCLE in main-project mode!")

    # --- Add global settings (for all of the subprojects)
    list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)
    include (properties)

    # --- Dependencies directory.
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies ${CMAKE_BINARY_DIR}/../dependencies)
    add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/../bluelib ${CMAKE_BINARY_DIR}/../bluelib)

endif ()


# --- Add header files
file (GLOB_RECURSE HEADER_FILES
	${PROJECT_SOURCE_DIR}/inc/*.h
	${PROJECT_SOURCE_DIR}/inc/*.hpp
)


# --- Add needed DEFINE's
add_compile_definitions (_CRT_SECURE_NO_WARNINGS)


# --- OpenAL linked statically requires the following define also.
if (NOT ${OPENAL_SHARED_LIBRARY}) 

	add_compile_definitions (AL_LIBTYPE_STATIC)

endif ()


# --- Info Build Type
message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")


message (STATUS "Preset: DEBUG")
add_compile_definitions (DEBUG_TYPE=${DEBUG_FLAG_LOGGING}+${DEBUG_FLAG_MEMORY})


# --- Define the executable
add_executable (
	${PROJECT_NAME} ${HEADER_FILES} 
	src/main.cpp
)


# --- Make this project 'headers' available to use.
target_include_directories (
	${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)


# --- LIBS.
target_link_libraries (${PROJECT_NAME} BLUELIB)


# --- Creates a 'symlink' for resources in builds directory.
add_custom_command (
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_SOURCE_DIR}/project/${PROJECT_NAME}/res
	${CMAKE_CURRENT_BINARY_DIR}/res
)
