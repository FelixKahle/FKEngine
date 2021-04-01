// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_module.h"
#include "miscellaneous/output_device.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	struct FKECORE_API buffered_log
	{
		const char_t* data;
		const char_t_string category_name;
		const double time;
		const log_type type;

		buffered_log(const char_t* in_data, const char_t_string& in_category_name, const log_type in_type, const double in_time = -1);

		buffered_log(buffered_log& in_buffered_log)
			: data(in_buffered_log.data)
			, category_name(in_buffered_log.category_name)
			, time(in_buffered_log.time)
			, type(in_buffered_log.type)
		{
			in_buffered_log.data = nullptr;
		}

		~buffered_log();

		FKE_NONCOPYABLE(buffered_log);
	};

	class FKECORE_API output_device_redirector : public output_device
	{
	public:

		typedef dynamic_array<output_device*> output_device_array;

	public:

		static output_device_redirector& get();

	public:

		virtual void serialize(const char_t* v, log_type type, const char_t_string& category) override;
		virtual void flush() override;

	public:

		output_device_redirector();

		void add_output_device(output_device* device);
		void remove_output_device(output_device* device);
		void flush_threaded_logs();

	private:

		void serialize_impl(const char_t* data, log_type type, const char_t_string& category, const double time = -1.0f);

	private:

		dynamic_array<buffered_log*> buffered_logs;
		output_device_array output_devices;

		/** The id of the master thread. */
		thread::id master_thread_id;

		mutex output_device_mutex;
		mutex buffer_mutex;
	};
}