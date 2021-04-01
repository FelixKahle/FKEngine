# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Compiling for Windows.
set(CMAKE_SYSTEM_NAME Windows)

# Build for the Windows platform.
set(FKE_PLATFORM "Windows")
add_compile_definitions(FKE_PLATFORM_WINDOWS=1)
add_compile_definitions(FKE_BUILD_SYSTEM_COMPILED_PLATFORM=windows)

if (CMAKE_CL_64 OR ${CMAKE_GENERATOR_PLATFORM} MATCHES "x64")
	set(PLATFORM_NAME "Windows 64-Bit")

	# The name of the output directory for binaries and libraries.
	# Microsoft Visual C++ puts these files automaticly in a folder which is named after the current configuration.
	# An example would be release or debug. OUTPUT_DIRECTORY_NAME_PLATFORM would then be Win64/Release.
	# This can be different with other compilers.
	set(OUTPUT_DIRECTORY_NAME_PLATFORM "win64")
else()
	set(PLATFORM_NAME "Windows 32-Bit")

	# The name of the output directory for binaries and libraries.
	# Microsoft Visual C++ puts these files automaticly in a folder which is named after the current configuration.
	# An example would be release or debug. OUTPUT_DIRECTORY_NAME_PLATFORM would then be Win32/Release.
	# This can be different with other compilers.
	set(OUTPUT_DIRECTORY_NAME_PLATFORM "win32")
endif()