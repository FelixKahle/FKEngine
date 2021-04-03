// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkeentities_module.h"
#include "fkecore.h"

namespace fkengine
{
	namespace fkeentities
	{
		/**
		 * Identifies an entity.
		 * The entity is a fundamental part of the Entity Component System. Everything in your application that has data or an
		 * identity of its own is an entity. However, an entity does not contain either data or behavior itself. Instead,
		 * the data is stored in the components and the behavior is provided by the systems that process those
		 * components. The entity acts as an identifier or key to the data stored in components.
		 * Entities are managed by the entity_manager class and exist within a world. An
		 * entity refers to an entity, but is not a reference. Rather the Entity struct contains an index
		 * used to access entity data and a version used to check whether the index is
		 * still valid. Note that you generally do not use the index or version values directly, but instead pass the
		 * entity to the relevant API methods.
		 * Pass an entity to methods of the entity_manager, entity_command_buffer,
		 * or the component_system in order to add or remove components, to access components, or to destroy
		 * the entity.
		 */
		class entity
		{
		public:

			/**
			 * Constructor.
			 * Constructs an entity.
			 *
			 * @param in_index - The index.
			 * @param in_version - The version.
			 */
			FKE_FORCEINLINE entity(uint32_t in_index, uint32_t in_version)
				: index(in_index)
				, version(in_version)
			{}

			/**
			 * Copy assignment operator.
			 *
			 * @param other - Other entity to copy assign to.
			 */
			FKE_FORCEINLINE entity& operator=(const entity& other)
			{
				index = other.index;
				version = other.version;
				return *this;
			}

			/**
			 * Compare this entity against a given one.
			 *
			 * @param other - The other entity to compare to.
			 * @return - Difference based on the Entity Index value.
			 */
			FKE_FORCEINLINE uint32_t compare_to(const entity& other) const
			{
				return index - other.index;
			}

			/**
			 * A hash used for comparisons.
			 *
			 * @return - A unique hash code.
			 */
			FKE_FORCEINLINE uint32_t get_hash_code() const
			{
				return index;
			}

		public:

			/**
			 * The ID of an entity.
			 * The index into the internal list of entities.
			 * Entity indexes are recycled when an entity is destroyed. When an entity is destroyed, the
			 * entity_manager increments the version identifier. To represent the same entity, both the index and the
			 * version fields of the entity must match. If the index is the same, but the version is different,
			 * then the entity has been recycled.
			 */
			uint32_t index;

			/**
			 * The generational version of the entity.
			 * The version number can, theoretically, overflow and wrap around within the lifetime of an
			 * application. For this reason, you cannot assume that an entity instance with a larger version is a more
			 * recent incarnation of the entity than one with a smaller version (and the same index).
			 * Used to determine whether this entity still identifies an existing entity.
			 */
			uint32_t version;
		};

		/**
		 * Entity instances are equal if they refer to the same entity.
		 * @param lhs - An entity.
		 * @param rhs - Another entity.
		 * @return - True, if both index and version are identical.
		 */
		FKE_FORCEINLINE bool operator==(const entity& lhs, const entity& rhs)
		{
			return lhs.index == rhs.index && lhs.version == rhs.version;
		}

		/**
		 * Entity instances are equal if they refer to the same entity.
		 * @param lhs - An entity.
		 * @param rhs - Another entity.
		 * @return - True, if both index and version are identical.
		 */
		FKE_FORCEINLINE bool operator!=(const entity& lhs, const entity& rhs)
		{
			return !(lhs == rhs);
		}
	}
}