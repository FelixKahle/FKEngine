# Copyright 2021 Felix Kahle. All rights reserved.

# The minimal required version of CMake.
cmake_minimum_required(VERSION 3.6.2)

# The public files/sources of the fkecore module.
set(FKE_CORE_PUBLIC_SOURCES
	# root
	${FKE_CORE_DIR}/public/fkecore.h
	${FKE_CORE_DIR}/public/fkecore_globals.h
	${FKE_CORE_DIR}/public/fkecore_types.h
	${FKE_CORE_DIR}/public/fkecore_module.h
	# algorithm
	${FKE_CORE_DIR}/public/algorithm/equal_range.h
	# compile_time_type_info
	${FKE_CORE_DIR}/public/compile_time_type_info/name_filters.h
	${FKE_CORE_DIR}/public/compile_time_type_info/name_filters.h
	${FKE_CORE_DIR}/public/compile_time_type_info/type_id.h
	${FKE_CORE_DIR}/public/compile_time_type_info/type_tag.h
	# container
	${FKE_CORE_DIR}/public/container/compile_time_string.h
	${FKE_CORE_DIR}/public/container/static_value.h
	# generic_platform
	${FKE_CORE_DIR}/public/generic_platform/generic_platform.h
	${FKE_CORE_DIR}/public/generic_platform/generic_platform_compiler_pre_setup.h
	${FKE_CORE_DIR}/public/generic_platform/generic_platform_misc.h
	${FKE_CORE_DIR}/public/generic_platform/generic_platform_stricmp.h
	${FKE_CORE_DIR}/public/generic_platform/generic_platform_string.h
	# hardware_abstraction_layer
	${FKE_CORE_DIR}/public/hardware_abstraction_layer/platform.h
	${FKE_CORE_DIR}/public/hardware_abstraction_layer/platform_misc.h
	${FKE_CORE_DIR}/public/hardware_abstraction_layer/platform_string.h
	${FKE_CORE_DIR}/public/hardware_abstraction_layer/preprocessor_helpers.h
	# hash
	${FKE_CORE_DIR}/public/hash/hash.h
	# logging
	${FKE_CORE_DIR}/public/logging/log_category.h
	${FKE_CORE_DIR}/public/logging/log_type.h
	# miscellaneous
	${FKE_CORE_DIR}/public/miscellaneous/assertion_macros.h
	${FKE_CORE_DIR}/public/miscellaneous/build.h
	${FKE_CORE_DIR}/public/miscellaneous/c_string.h
	${FKE_CORE_DIR}/public/miscellaneous/char.h
	${FKE_CORE_DIR}/public/miscellaneous/eastl_pre_setup.h
	${FKE_CORE_DIR}/public/miscellaneous/fkecore_misc_defines.h
	${FKE_CORE_DIR}/public/miscellaneous/iostream_output_device.h
	${FKE_CORE_DIR}/public/miscellaneous/ofstream_output_device.h
	${FKE_CORE_DIR}/public/miscellaneous/output_device_helper.h
	${FKE_CORE_DIR}/public/miscellaneous/output_device.h
	${FKE_CORE_DIR}/public/miscellaneous/output_device_redirector.h
	${FKE_CORE_DIR}/public/miscellaneous/scope_exit.h
	${FKE_CORE_DIR}/public/miscellaneous/standard_library_include.h
	${FKE_CORE_DIR}/public/miscellaneous/time.h
	${FKE_CORE_DIR}/public/miscellaneous/type_info.h
	${FKE_CORE_DIR}/public/miscellaneous/var_args.h
	${FKE_CORE_DIR}/public/miscellaneous/var_args_helper.h
	# module
	${FKE_CORE_DIR}/public/module/module_setup.h
	# templates
	${FKE_CORE_DIR}/public/templates/array_count.h
	${FKE_CORE_DIR}/public/templates/fkengine_template.h
	${FKE_CORE_DIR}/public/templates/is_array_or_ref_of_type.h
	${FKE_CORE_DIR}/public/templates/is_character.h
	${FKE_CORE_DIR}/public/templates/is_valid_variadic_function_arg.h
	# traits
	${FKE_CORE_DIR}/public/traits/int_type.h
)

# The private files/sources of the fkecore module.
set(FKE_CORE_PRIVATE_SOURCES
	# root
	${FKE_CORE_DIR}/private/fkecore_module.cpp
	${FKE_CORE_DIR}/private/fkecore_globals.cpp
	# generic_platform
	${FKE_CORE_DIR}/private/generic_platform/generic_platform_stricmp.cpp
	${FKE_CORE_DIR}/private/generic_platform/generic_platform_string.cpp
	# logging
	${FKE_CORE_DIR}/private/logging/log_macros.cpp
	# miscellaneous
	${FKE_CORE_DIR}/private/miscellaneous/assertion_macros.cpp
	${FKE_CORE_DIR}/private/miscellaneous/c_string.cpp
	${FKE_CORE_DIR}/private/miscellaneous/iostream_output_device.cpp
	${FKE_CORE_DIR}/private/miscellaneous/ofstream_output_device.cpp
	${FKE_CORE_DIR}/private/miscellaneous/output_device.cpp
	${FKE_CORE_DIR}/private/miscellaneous/output_device_helper.cpp
	${FKE_CORE_DIR}/private/miscellaneous/output_device_redirector.cpp
	${FKE_CORE_DIR}/private/miscellaneous/standard_library_include.cpp
)

# Platform specific sources

set(FKE_CORE_WINDOWS_PUBLIC_SOURCES
	${FKE_CORE_DIR}/public/windows_platform/windows_platform.h
	${FKE_CORE_DIR}/public/windows_platform/windows_platform_code_analysis.h
	${FKE_CORE_DIR}/public/windows_platform/windows_platform_compiler_pre_setup.h
	${FKE_CORE_DIR}/public/windows_platform/windows_platform_compiler_setup.h
	${FKE_CORE_DIR}/public/windows_platform/windows_platform_misc.h
	${FKE_CORE_DIR}/public/windows_platform/windows_platform_string.h
)

set(FKE_CORE_WINDOWS_PRIVATE_SOURCES
	${FKE_CORE_DIR}/private/windows_platform/windows_platform_misc.cpp
)

# Compiler specific sources.

set(FKE_CORE_CLANG_PUBLIC_SOURCES
	${FKE_CORE_DIR}/public/clang_platform/clang_platform.h
	${FKE_CORE_DIR}/public/clang_platform/clang_platform_code_analysis.h
)
set(FKE_CORE_CLANG_PRIVATE_SOURCES)

set(FKE_CORE_MSVC_PUBLIC_SOURCES
	${FKE_CORE_DIR}/public/msvc_platform/msvc_platform.h
)
set(FKE_CORE_MSVC_PRIVATE_SOURCES)