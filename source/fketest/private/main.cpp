// Copyright 2021 Felix Kahle. All rights reserved.

#include "miscellaneous/type_info.h"
#include "fkecore_globals.h"
#include "miscellaneous/iostream_output_device.h"
#include "miscellaneous/ofstream_output_device.h"
#include "miscellaneous/assertion_macros.h"
#include "logging/log_macros.h"
#include "miscellaneous/scope_exit.h"
#include "types/chunk.h"
#include "types/entity.h"
#include <iostream>

using namespace fkengine::fkecore;
using namespace fkengine::fkeentities;

FKE_DEFINE_LOG_CATEGORY_STATIC(log_category_test);

struct test
{

};

int main()
{
	entity e = entity(1, 2);
	iostream_output_device* io_device = new iostream_output_device();
	ofstream_output_device* of_device = new ofstream_output_device(FKE_TEXT("Log File.txt"));
	FKE_ON_SCOPE_EXIT
	{
		delete io_device;
		delete of_device;
	};

	//FKE_LOG(log_category_test, log, FKE_TEXT("%s"), FKE_GET_TYPE_NAME(test));
	output_device_redirector::get().add_output_device(io_device);
	output_device_redirector::get().add_output_device(of_device);

	FKE_LOG(log_category_test, fatal, FKE_TEXT("Hallo %s"), FKE_TEXT("Hallo"));
	FKE_CHECK(false);
	std::cin.get();

	return 0;
}