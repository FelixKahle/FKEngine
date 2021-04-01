# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Print out some information about the buidling progress.
fkemessage(STATUS "Application: fketest")

# Include the settings for the fketest module.
include(fketest_application_settings.cmake)

# The fketest application project.
project(fketest VERSION ${FKE_TEST_VERSION})

# The path to the fketest module source.
set(FKE_TEST_DIR ${CMAKE_CURRENT_LIST_DIR})

# Include the sources.
include(fketest_application_sources.cmake)

if (${FKE_PLATFORM} STREQUAL "Windows")
	set(FKE_TEST_PLATFORM_SPECIFIC_PUBLIC_SOURCES ${FKE_TEST_WINDOWS_PUBLIC_SOURCES})
	set(FKE_TEST_PLATFORM_SPECIFIC_PRIVATE_SOURCES ${FKE_TEST_WINDOWS_PRIVATE_SOURCES})
endif()

if (${FKE_COMPILER} STREQUAL "Clang")
	set(FKE_TEST_COMPILER_SPECIFIC_PUBLIC_SOURCES ${FKE_TEST_CLANG_PUBLIC_SOURCES})
	set(FKE_TEST_COMPILER_SPECIFIC_PRIVATE_SOURCES ${FKE_TEST_CLANG_PRIVATE_SOURCES})
elseif(${FKE_COMPILER} STREQUAL "MSVC")
	set(FKE_TEST_COMPILER_SPECIFIC_PUBLIC_SOURCES ${FKE_TEST_MSVC_PUBLIC_SOURCES})
	set(FKE_TEST_COMPILER_SPECIFIC_PRIVATE_SOURCES ${FKE_TEST_MSVC_PRIVATE_SOURCES})
endif()

add_executable(fketest
	${FKE_TEST_PUBLIC_SOURCES} 
	${FKE_TEST_PLATFORM_SPECIFIC_PUBLIC_SOURCES} 
	${FKE_TEST_PRIVATE_SOURCES} 
	${FKE_TEST_PLATFORM_SPECIFIC_PRIVATE_SOURCES}
	${FKE_TEST_COMPILER_SPECIFIC_PUBLIC_SOURCES}
	${FKE_TEST_COMPILER_SPECIFIC_PRIVATE_SOURCES}
)

# fkecore
target_link_libraries(fketest PUBLIC fkecore)

# Set up the properties for the fketest module.
set_target_properties(fketest PROPERTIES VERSION ${PROJECT_VERSION})

# Print out some information about the buidling progress.
fkemessage(STATUS "fketest application Version: ${FKE_TEST_VERSION}")
fkemessage(STATUS "fketest application link type: ${FKE_TEST_LINK_TYPE}")
fkemessage(STATUS "The fketest module has been processed")