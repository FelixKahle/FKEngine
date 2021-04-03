// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_module.h"

#if FKE_SUPPORT_COMPILE_TIME_TYPE_INFO
	#include "compile_time_type_info/type_id.h"
	#define FKE_GET_TYPE_NAME(type_name) fkengine::fkecore::nameof<type_name>().cppstring()
	#define FKE_GET_TYPE_HASH(type_name) fkengine::fkecore::get_unnamed_type_id<type_name>().hash()
#else
	#include <typeinfo>
	#define FKE_GET_TYPE_NAME(type_name) typeid(type_name).name()
	#define FKE_GET_TYPE_HASH(type_name) typeid(type_name).hash_code()
#endif

/** The namespace of the FKEngine. */
namespace fkengine
{
}