// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

/** The namespace of the FKEngine. */
namespace fkengine
{
	class noncopyable
	{
	protected:
		// ensure the class cannot be constructed directly
		noncopyable() {}
		// the class should not be used polymorphically
		~noncopyable() {}
	private:
		noncopyable(const noncopyable&);
		noncopyable& operator=(const noncopyable&);
	};
}