#CMakefile version 3.16

cmake_minimum_required(VERSION 3.16..3.30)

project(tconfig VERSION 1.0.0)
cmake_policy(SET CMP0169 OLD)


# Get googletest
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG release-1.11.0)
FetchContent_getProperties(googletest)
if(NOT googletest_POPULATED)
	FetchContent_Populate(googletest)
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BUILD_DIR})
endif()

# Making static library and googletests

add_library(tconfig STATIC src/tconfig.cpp)

add_executable(testRunner src/test.cpp)
target_link_libraries(testRunner tconfig gtest_main gmock_main)

