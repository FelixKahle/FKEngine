# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# The public files/sources of the fkeentities module.
set(FKE_ENTITIES_PUBLIC_SOURCES
	# root
	${FKE_ENTITIES_DIR}/public/fkeentities_module.h
	# types
	${FKE_ENTITIES_DIR}/public/types/archetype.h
	${FKE_ENTITIES_DIR}/public/types/archetype_chunk_data.h
	${FKE_ENTITIES_DIR}/public/types/chunk.h
	${FKE_ENTITIES_DIR}/public/types/entity.h
	${FKE_ENTITIES_DIR}/public/types/types_forward.h
)

# The private files/sources of the fkeentities module.
set(FKE_ENTITIES_PRIVATE_SOURCES
	${FKE_ENTITIES_DIR}/private/fkeentities_module.cpp
	# types
	${FKE_ENTITIES_DIR}/private/types/archetype_chunk_data.cpp
	${FKE_ENTITIES_DIR}/private/types/chunk.cpp
)

# Platform specific sources

set(FKE_ENTITIES_WINDOWS_PUBLIC_SOURCES)

set(FKE_ENTITIES_WINDOWS_PRIVATE_SOURCES)

# Compiler specific sources.

set(FKE_ENTITIES_CLANG_PUBLIC_SOURCES)
set(FKE_ENTITIES_CLANG_PRIVATE_SOURCES)

set(FKE_ENTITIES_MSVC_PUBLIC_SOURCES)
set(FKE_ENTITIES_MSVC_PRIVATE_SOURCES)