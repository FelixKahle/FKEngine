# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Print out some information about the buidling progress.
fkemessage(STATUS "Module: fkecore")

# Include the settings for the fkecore module.
include(fkecore_module_settings.cmake)

# The fkecore module project.
project(fkecore VERSION ${FKE_CORE_VERSION})

# The path to the fkecore module source.
set(FKE_CORE_DIR ${CMAKE_CURRENT_LIST_DIR})

add_compile_definitions(FKECORE_VERSION=${FKE_CORE_VERSION})

# If the fkecore module has to be linked as a dynamic link library this define has to be defined with 1.
# If the fkecore module has to be linked as a static library, this define has to be defined with 0.
# This is important, because the FKECORE_API define has to be set up correctly in the fkecore_module.h file.
if (${FKE_CORE_LINK_TYPE} MATCHES SHARED OR ${FKE_CORE_LINK_TYPE} MATCHES MODULE)
	add_compile_definitions(FKECORE_LINK_DYNAMICALLY=1)
elseif(${FKE_CORE_LINK_TYPE} MATCHES STATIC)
	add_compile_definitions(FKECORE_LINK_DYNAMICALLY=0)
else()
	# All other link types (there are no other link types) are not allowed.
	# This is why the build progress should crash here if an incorrect build type was choosen.
	fkemessage(FATAL_ERROR "The link type of the fkecore module is incorrect. It has to be SHARED, MODULE OR STATIC")
endif()

# Include the sources.
include(fkecore_module_sources.cmake)

if (${FKE_PLATFORM} STREQUAL "Windows")
	set(FKE_CORE_PLATFORM_SPECIFIC_PUBLIC_SOURCES ${FKE_CORE_WINDOWS_PUBLIC_SOURCES})
	set(FKE_CORE_PLATFORM_SPECIFIC_PRIVATE_SOURCES ${FKE_CORE_WINDOWS_PRIVATE_SOURCES})
endif()

if (${FKE_COMPILER} STREQUAL "Clang")
	set(FKE_CORE_COMPILER_SPECIFIC_PUBLIC_SOURCES ${FKE_CORE_CLANG_PUBLIC_SOURCES})
	set(FKE_CORE_COMPILER_SPECIFIC_PRIVATE_SOURCES ${FKE_CORE_CLANG_PRIVATE_SOURCES})
elseif(${FKE_COMPILER} STREQUAL "MSVC")
	set(FKE_CORE_COMPILER_SPECIFIC_PUBLIC_SOURCES ${FKE_CORE_MSVC_PUBLIC_SOURCES})
	set(FKE_CORE_COMPILER_SPECIFIC_PRIVATE_SOURCES ${FKE_CORE_MSVC_PRIVATE_SOURCES})
endif()

# Add the fkecore module.
add_library(fkecore 
	${FKE_CORE_LINK_TYPE} 
	${FKE_CORE_PUBLIC_SOURCES} 
	${FKE_CORE_PLATFORM_SPECIFIC_PUBLIC_SOURCES} 
	${FKE_CORE_PRIVATE_SOURCES} 
	${FKE_CORE_PLATFORM_SPECIFIC_PRIVATE_SOURCES}
	${FKE_CORE_COMPILER_SPECIFIC_PUBLIC_SOURCES}
	${FKE_CORE_COMPILER_SPECIFIC_PRIVATE_SOURCES})

# Set up the properties for the fkecore module.
set_target_properties(fkecore PROPERTIES VERSION ${PROJECT_VERSION})

# The include directories.
target_include_directories(fkecore PUBLIC ${FKE_CORE_DIR}/public)
target_include_directories(fkecore PRIVATE ${FKE_CORE_DIR}/private)

# Print out some information about the buidling progress.
fkemessage(STATUS "fkecore module Version: ${FKE_CORE_VERSION}")
fkemessage(STATUS "fkecore module link type: ${FKE_CORE_LINK_TYPE}")
fkemessage(STATUS "The fkecore module has been processed")