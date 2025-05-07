# --- Define a 'subproject'
project (test VERSION 1.0.0 LANGUAGES C CXX)


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


#--- Enable testing
enable_testing ()

#--- Add GoogleTest
add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest ${CMAKE_BINARY_DIR}/googletest-build)
#add_subdirectory (../../external/googletest)


# --- Info Build Type
message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")


if 		(${PROFILE} EQUAL 1)

	message (STATUS "Preset: DEBUG")
	add_compile_definitions (DEBUG_TYPE=${DEBUG_FLAG_LOGGING}+${DEBUG_FLAG_MEMORY})

elseif 	(${PROFILE} EQUAL 2)

	message (STATUS "Preset: RELEASE")
	add_compile_definitions (DEBUG_TYPE=0)

endif ()


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
target_link_libraries (${PROJECT_NAME} gtest gtest_main)


# Register the test with CTest
include (GoogleTest)
gtest_discover_tests (${PROJECT_NAME})


# --- Creates a 'symlink' for resources in builds directory.
add_custom_command (
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_SOURCE_DIR}/project/${PROJECT_NAME}/res
	${CMAKE_CURRENT_BINARY_DIR}/res
)
