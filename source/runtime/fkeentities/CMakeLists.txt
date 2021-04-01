# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# Print out some information about the buidling progress.
fkemessage(STATUS "Module: fkeentities")

# Include the settings for the fkeentities module.
include(fkeentities_module_settings.cmake)

# The fkeentities module project.
project(fkeentities VERSION ${FKE_ENTITIES_VERSION})

# The path to the fkeentities module source.
set(FKE_ENTITIES_DIR ${CMAKE_CURRENT_LIST_DIR})

add_compile_definitions(FKEENTITIES_VERSION=${FKE_ENTITIES_VERSION})

# If the fkeentities module has to be linked as a dynamic link library this define has to be defined with 1.
# If the fkeentities module has to be linked as a static library, this define has to be defined with 0.
# This is important, because the FKEENTITIES_API define has to be set up correctly in the fkeentities_module.h file.
if (${FKE_ENTITIES_LINK_TYPE} MATCHES SHARED OR ${FKE_ENTITIES_LINK_TYPE} MATCHES MODULE)
	add_compile_definitions(FKEENTITIES_LINK_DYNAMICALLY=1)
elseif(${FKE_ENTITIES_LINK_TYPE} MATCHES STATIC)
	add_compile_definitions(FKEENTITIES_LINK_DYNAMICALLY=0)
else()
	# All other link types (there are no other link types) are not allowed.
	# This is why the build progress should crash here if an incorrect build type was choosen.
	fkemessage(FATAL_ERROR "The link type of the fkeentities module is incorrect. It has to be SHARED, MODULE OR STATIC")
endif()

# Include the sources.
include(fkeentities_module_sources.cmake)

if (${FKE_PLATFORM} STREQUAL "Windows")
	set(FKE_ENTITIES_PLATFORM_SPECIFIC_PUBLIC_SOURCES ${FKE_ENTITIES_WINDOWS_PUBLIC_SOURCES})
	set(FKE_ENTITIES_PLATFORM_SPECIFIC_PRIVATE_SOURCES ${FKE_ENTITIES_WINDOWS_PRIVATE_SOURCES})
endif()

if (${FKE_COMPILER} STREQUAL "Clang")
	set(FKE_ENTITIES_COMPILER_SPECIFIC_PUBLIC_SOURCES ${FKE_ENTITIES_CLANG_PUBLIC_SOURCES})
	set(FKE_ENTITIES_COMPILER_SPECIFIC_PRIVATE_SOURCES ${FKE_ENTITIES_CLANG_PRIVATE_SOURCES})
elseif(${FKE_COMPILER} STREQUAL "MSVC")
	set(FKE_ENTITIES_COMPILER_SPECIFIC_PUBLIC_SOURCES ${FKE_ENTITIES_MSVC_PUBLIC_SOURCES})
	set(FKE_ENTITIES_COMPILER_SPECIFIC_PRIVATE_SOURCES ${FKE_ENTITIES_MSVC_PRIVATE_SOURCES})
endif()

# Add the fkeentities module.
add_library(fkeentities 
	${FKE_ENTITIES_LINK_TYPE} 
	${FKE_ENTITIES_PUBLIC_SOURCES} 
	${FKE_ENTITIES_PLATFORM_SPECIFIC_PUBLIC_SOURCES} 
	${FKE_ENTITIES_PRIVATE_SOURCES} 
	${FKE_ENTITIES_PLATFORM_SPECIFIC_PRIVATE_SOURCES}
	${FKE_ENTITIES_COMPILER_SPECIFIC_PUBLIC_SOURCES}
	${FKE_ENTITIES_COMPILER_SPECIFIC_PRIVATE_SOURCES}
)

target_link_libraries(fkeentities ${FKE_ENTITIES_DEPENDENCIES})

# Set up the properties for the fkeentities module.
set_target_properties(fkeentities PROPERTIES VERSION ${PROJECT_VERSION})

# The include directories.
target_include_directories(fkeentities PUBLIC ${FKE_ENTITIES_DIR}/public)
target_include_directories(fkeentities PRIVATE ${FKE_ENTITIES_DIR}/private)

# Print out some information about the buidling progress.
fkemessage(STATUS "fkeentities module Version: ${FKE_ENTITIES_VERSION}")
fkemessage(STATUS "fkeentities module link type: ${FKE_ENTITIES_LINK_TYPE}")
fkemessage(STATUS "The fkeentities module has been processed")