# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Define the root directory of the FKEngine, if it was not defined already.
if (NOT DEFINED FKENGINE_DIR)
	set (FKENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# Define the root directory of the project, if it was not defined already.
if (NOT DEFINED PROJECT_DIR)
	set (PROJECT_DIR "${CMAKE_SOURCE_DIR}")
endif()

# Define the path to the source directory, if it was not already defined.
if (NOT DEFINED FKENGINE_SOURCE_DIR)
	set (FKENGINE_SOURCE_DIR "${FKENGINE_DIR}/source")
endif()

# Define the Tools/Cmake path, if it was not defined already.
if (NOT DEFINED FKENGINE_TOOLS_CMAKE_DIR)
	set (FKENGINE_TOOLS_CMAKE_DIR "${FKENGINE_DIR}/tools/cmake")
endif()

# Fix slashes on the root directory path of the FKEngine.
string(REPLACE "\\" "/" FKENGINE_DIR "${FKENGINE_DIR}")
# Fix slashes on the root directory path of the project.
string(REPLACE "\\" "/" PROJECT_DIR "${PROJECT_DIR}")
# Fix slashes on the source directory path.
string(REPLACE "\\" "/" FKENGINE_SOURCE_DIR "${FKENGINE_SOURCE_DIR}")
# Fix slashes on the Tools/CMake path.
string(REPLACE "\\" "/" FKENGINE_TOOLS_CMAKE_DIR "${FKENGINE_TOOLS_CMAKE_DIR}")

# C language required.
enable_language(C)
# C++ language required.
enable_language(CXX)
# C++11 support requirement.
set (CMAKE_CXX_STANDARD 20)

# Check if the OUTPUT_DIRECTORY_NAME is defined.
# This should happen in the toolchain file from the current platform.
if (NOT DEFINED OUTPUT_DIRECTORY_NAME_PLATFORM)
	fkemessage(FATAL_ERROR "OUTPUT_DIRECTORY_NAME_PLATFORM was not defined")
endif()

if (${FKE_PLATFORM} STREQUAL "Windows")
	# The name of the output directory for binaries and libraries.
	# Microsoft Visual C++ puts these files automaticly in a folder which is named after the current configuration.
	# An example would be release or debug. OUTPUT_DIRECTORY would then be Win64/Release.
	# This can be different with other compilers.
	set(OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY_NAME_PLATFORM})
elseif (${FKE_PLATFORM} STREQUAL "Linux")
	set(OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY_NAME_PLATFORM}/${FKENGINE_CONFIGURATION})
endif()

# Check if the OUTPUT_DIRECTORY is defined.
if (NOT DEFINED OUTPUT_DIRECTORY)
	fkemessage(FATAL_ERROR "OUTPUT_DIRECTORY was not defined")
endif()

# Set up the paths for outputting the binaries and libraries.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_DIR}/binaries/${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_DIR}/libraries/${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_DIR}/binaries/${OUTPUT_DIRECTORY})

# Print out some information about the buidling progress.
fkemessage(STATUS "Archive output directory: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
fkemessage(STATUS "Library output directory: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
fkemessage(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Print out some information about the buidling progress.
fkemessage(STATUS "CMake has been configured for building the FKEngine")