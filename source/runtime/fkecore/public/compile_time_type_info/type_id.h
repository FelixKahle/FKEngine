// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "compile_time_type_info/name_of.h"
#include "hash/hash.h"
#include "miscellaneous/standard_library_include.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
    struct type_id
    {
        FKE_CONSTEXPR type_id(const compile_time_ansi_string& name) :
            actual_name{ name }
        {}

        FKE_CONSTEXPR type_id() :
            type_id{ "void" }
        {}

        type_id& operator=(const type_id&) = default;

        FKE_CONSTEXPR uint64_t hash() const
        {
            return actual_name.hash();
        }

        FKE_CONSTEXPR const compile_time_ansi_string& name() const
        {
            return actual_name;
        }

        friend FKE_CONSTEXPR bool operator==(const type_id& lhs, const type_id& rhs)
        {
            return lhs.hash() == rhs.hash();
        }

        friend FKE_CONSTEXPR bool operator!=(const type_id& lhs, const type_id& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        compile_time_ansi_string actual_name;
    };

    struct unnamed_type_id
    {
        FKE_CONSTEXPR unnamed_type_id(const uint64_t hash) :
            actual_hash{ hash }
        {}

        FKE_CONSTEXPR unnamed_type_id(const type_id& id) :
            actual_hash{ id.hash() }
        {}

        unnamed_type_id& operator=(const unnamed_type_id&) = default;

        FKE_CONSTEXPR uint64_t hash() const
        {
            return actual_hash;
        }

        friend FKE_CONSTEXPR bool operator==(const unnamed_type_id& lhs, const unnamed_type_id& rhs)
        {
            return lhs.hash() == rhs.hash();
        }

        friend FKE_CONSTEXPR bool operator!=(const unnamed_type_id& lhs, const unnamed_type_id& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        uint64_t actual_hash;
    };

    template<size_t n>
    FKE_CONSTEXPR unnamed_type_id id_from_name(const ansichar_t(&typeName)[n])
    {
        return hashing::fnv1a_hash<ansichar_t, uint64_t>(typeName);
    }

    FKE_CONSTEXPR unnamed_type_id id_from_name(const ansichar_t* typeName, size_t length)
    {
        return hashing::fnv1a_hash<ansichar_t, uint64_t>(length, typeName);
    }

    FKE_CONSTEXPR unnamed_type_id id_from_name(const compile_time_ansi_string& name)
    {
        return hashing::fnv1a_hash<ansichar_t, uint64_t>(name.size(), name.begin());
    }

    // Inline to prevent ODR violation.
    inline unnamed_type_id id_from_name(const std::string& typeName)
    {
        return hashing::fnv1a_hash<ansichar_t, uint64_t>(typeName.size(), typeName.data());
    }

    namespace fke_type_id_private
    {
        template<typename t>
        FKE_CONSTEXPR type_id get_type_id()
        {
            return { fkengine::nameof<t>() };
        }

        template<typename t>
        FKE_CONSTEXPR unnamed_type_id get_unnamed_type_id()
        {
            return { id_from_name(fkengine::nameof<t>()) };
        }
    }

    template<typename t>
    FKE_CONSTEXPR type_id get_type_id(t&&)
    {
        return fke_type_id_private::get_type_id<typename decay<t>::type>();
    }

    template<typename t>
    FKE_CONSTEXPR type_id get_type_id()
    {
        return fke_type_id_private::get_type_id<t>();
    }

    template<typename t>
    FKE_CONSTEXPR unnamed_type_id get_unnamed_type_id(t&&)
    {
        return fke_type_id_private::get_unnamed_type_id<typename decay<t>::type>();
    }

    template<typename t>
    FKE_CONSTEXPR unnamed_type_id get_unnamed_type_id()
    {
        return fke_type_id_private::get_unnamed_type_id<t>();
    }
}