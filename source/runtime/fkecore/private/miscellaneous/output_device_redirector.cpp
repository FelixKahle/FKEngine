// Copyright 2021 Felix Kahle.All rights reserved.

#include "fkecore_types.h"
#include "miscellaneous/output_device_redirector.h"
#include "miscellaneous/assertion_macros.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	buffered_log::buffered_log(const char_t* in_data, const char_t_string& in_category_name, const log_type in_type, const double in_time)
		: category_name(in_category_name)
		, time(in_time)
		, type(in_type)
	{
		int32_t num_chars = c_string::strlen(in_data) + 1;
		void* dest = malloc(sizeof(char_t) * num_chars);
		data = (char_t*)memcpy(dest, in_data, sizeof(char_t) * num_chars);
	}

	buffered_log::~buffered_log()
	{
		free(const_cast<char_t*>(data));
	}


	output_device_redirector& output_device_redirector::get()
	{
		static output_device_redirector output_device_redirector_singleton_instance;
		return output_device_redirector_singleton_instance;
	}

	output_device_redirector::output_device_redirector()
		: master_thread_id(this_thread::get_id())
	{
	}

	void output_device_redirector::serialize(const char_t* v, log_type type, const char_t_string& category)
	{
		serialize_impl(v, type, category);
	}

	void output_device_redirector::flush()
	{
		// TODO: Consider removing this.
		flush_threaded_logs();

		for (output_device* device : output_devices)
		{
			device->flush();
		}
	}

	void output_device_redirector::add_output_device(output_device* device)
	{
		if (device)
		{
			FKE_CHECKF(this_thread::get_id() == master_thread_id, FKE_TEXT("add_output_device() can only be called from the main thread"));
			output_devices.push_back(static_cast<output_device*>(device));
		}
	}

	void output_device_redirector::remove_output_device(output_device* device)
	{
		if (device)
		{
			FKE_CHECKF(this_thread::get_id() == master_thread_id, FKE_TEXT("add_output_device() can only be called from the main thread"));
			output_devices.erase(remove(output_devices.begin(), output_devices.end(), device), output_devices.end());
		}
	}

	void output_device_redirector::serialize_impl(const char_t* data, log_type type, const char_t_string& category, const double time)
	{
		if (this_thread::get_id() != master_thread_id)
		{
			buffer_mutex.lock();
			buffered_logs.push_back(new buffered_log(data, category, type, time));
			buffer_mutex.unlock();
		}
		else
		{
			// Flush logs.
			flush_threaded_logs();

			for (output_device* device : output_devices)
			{
				device->serialize(data, type, category, time);
			}
		}
	}

	void output_device_redirector::flush_threaded_logs()
	{
		FKE_CHECKF(this_thread::get_id() == master_thread_id, FKE_TEXT("flush_threaded_logs() can only be called from the main thread"));

		for (buffered_log* log : buffered_logs)
		{
			for (output_device* device : output_devices)
			{
				device->serialize(log->data, log->type, log->category_name);
			}
		}

		buffered_logs.clear();
	}
}