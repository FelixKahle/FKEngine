// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"
#include "compile_time_type_info/name_filters.h"
#include "container/compile_time_string.h"
#include "container/static_value.h"
#include "compile_time_type_info/type_tag.h"

#if !FKE_SUPPORT_COMPILE_TIME_TYPE_INFO
    #error Compile-time type info header included but the functionality is not supported by the current compiler
#endif

//
// TODO: Testing other compilers. Prefix and Suffix is just set up correctly for MSVC !!!
//

#if defined(__clang__)
    #define FKE_TYPE_PRETTY_FUNCTION_PREFIX "basic_compile_time_string<char> fkengine::fkecore::fke_nameof_private::pretty_function_type() [T = "
    #define FKE_TYPE_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(__GNUC__) && !defined(__clang__)
    #define FKE_TYPE_PRETTY_FUNCTION_PREFIX "constexpr basic_compile_time_string<char> fkengine::fkecore::fke_nameof_private::pretty_function_type() [with T = "
    #define FKE_TYPE_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(_MSC_VER)
    #define FKE_TYPE_PRETTY_FUNCTION_PREFIX "class fkengine::fkecore::basic_compile_time_string<char,struct std::enable_if<1,char> > __cdecl fkengine::fkecore::fke_nameof_private::pretty_function_type<"
    #define FKE_TYPE_PRETTY_FUNCTION_SUFFIX ">(void)"
#endif

#define FKE_TYPE_PRETTY_FUNCTION_LEFT (sizeof(FKE_TYPE_PRETTY_FUNCTION_PREFIX) - 1)
#define FKE_TYPE_PRETTY_FUNCTION_RIGHT (sizeof(FKE_TYPE_PRETTY_FUNCTION_SUFFIX) - 1)

#if defined(__clang__)
    #define FKE_VALUE_PRETTY_FUNCTION_PREFIX "basic_compile_time_string<char> fkengine::fke_nameof_private::pretty_function_value() [T = "
    #define FKE_VALUE_PRETTY_FUNCTION_SEPARATOR "; Value = "
    #define FKE_VALUE_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(__GNUC__) && !defined(__clang__)
    #define FKE_VALUE_PRETTY_FUNCTION_PREFIX "constexpr basic_compile_time_string<char> fkengine::fke_nameof_private::pretty_function_value() [with T = "
    #define FKE_VALUE_PRETTY_FUNCTION_SEPARATOR "; T Value = "
    #define FKE_VALUE_PRETTY_FUNCTION_SUFFIX "]"
#elif defined(_MSC_VER)
    #define FKE_VALUE_PRETTY_FUNCTION_PREFIX "class fkengine::fkecore::basic_compile_time_string<char,struct std::enable_if<1,char> > __cdecl fkengine::fkecore::fke_nameof_private::pretty_function_value<"
    #define FKE_VALUE_PRETTY_FUNCTION_SEPARATOR "; T Value = "
    #define FKE_VALUE_PRETTY_FUNCTION_SUFFIX ">(void)"
#endif

#define FKE_VALUE_PRETTY_FUNCTION_LEFT (sizeof(FKE_VALUE_PRETTY_FUNCTION_PREFIX) - 1)
#define FKE_VALUE_PRETTY_FUNCTION_SEPARATION (sizeof(FKE_VALUE_PRETTY_FUNCTION_SEPARATOR) - 1)
#define FKE_VALUE_PRETTY_FUNCTION_RIGHT (sizeof(FKE_VALUE_PRETTY_FUNCTION_SUFFIX) - 1)


/** The namespace of the FKEngine. */
namespace fkengine
{
    namespace fkecore
    {
        template<typename t>
        FKE_CONSTEXPR compile_time_ansi_string nameof();

        template<typename t, t val>
        FKE_CONSTEXPR compile_time_ansi_string nameof();

        namespace fke_nameof_private
        {
            template<typename t>
            FKE_CONSTEXPR compile_time_ansi_string pretty_function_type()
            {
                return { FKE_PRETTY_FUNCTION };
            }

            template<typename t, t val>
            FKE_CONSTEXPR compile_time_ansi_string pretty_function_value()
            {
                return { FKE_PRETTY_FUNCTION };
            }

            template<typename t, typename = void>
            struct type_name_length : integral_constant<size_t, fkengine::fkecore::nameof<t>().length()>
            {};

            template<typename r, typename tclass>
            struct type_name_length<r tclass::*, void> : integral_constant<size_t, fkengine::fkecore::nameof<r tclass::*>().length()>
            {};

            template<typename tenum>
            struct type_name_length<tenum, typename enable_if<std::is_enum<tenum>::value>::type> : integral_constant<size_t, fkengine::fkecore::nameof<tenum>().length()>
            {};

            template<typename T>
            struct another_level_of_indirection {};

            template<typename t, typename = void>
            struct nameof_impl
            {
                static FKE_CONSTEXPR compile_time_ansi_string apply()
                {
                    return name_filters<ansichar_t>::filter_typename_prefix(pretty_function_type<t>().pad(FKE_TYPE_PRETTY_FUNCTION_LEFT, FKE_TYPE_PRETTY_FUNCTION_RIGHT));
                }
            };

            template<typename t>
            struct nameof_impl<t, void_t<decltype(t::compile_time_nameof())>>
            {
                static FKE_CONSTEXPR compile_time_ansi_string apply()
                {
                    return t::compile_time_nameof();
                }
            };

            template<typename t, t val>
            struct nameof_impl<another_level_of_indirection<static_value<t, val>>, void>
            {
                static FKE_CONSTEXPR compile_time_ansi_string apply()
                {
                    return pretty_function_value<t, val>().pad(FKE_VALUE_PRETTY_FUNCTION_LEFT + type_name_length<t>::value + FKE_VALUE_PRETTY_FUNCTION_SEPARATION, FKE_VALUE_PRETTY_FUNCTION_RIGHT);
                }
            };

            template<typename t, t val>
            struct nameof_impl<static_value<t, val>, void>
            {
                static FKE_CONSTEXPR compile_time_ansi_string apply()
                {
                    return fkengine::fkecore::nameof<t, val>();
                }
            };
        }

        template<typename t>
        FKE_CONSTEXPR compile_time_ansi_string compile_time_nameof(type_tag<t>)
        {
            return fke_nameof_private::nameof_impl<t>::apply();
        }

        template<typename t, t val>
        FKE_CONSTEXPR compile_time_ansi_string compile_time_nameof(static_value<t, val>)
        {
            return fke_nameof_private::nameof_impl<fke_nameof_private::another_level_of_indirection<static_value<t, val>>>::apply();
        }

        template<typename t>
        FKE_CONSTEXPR compile_time_ansi_string nameof()
        {
            return fkengine::fkecore::compile_time_nameof(type_tag<t>());
        }

        template<typename t, t val>
        FKE_CONSTEXPR compile_time_ansi_string nameof()
        {
            return fkengine::fkecore::compile_time_nameof(static_value<t, val>());
        }

#ifdef FKE_HAS_VARIABLE_TEMPLATES
        template<typename t>
        FKE_CONSTEXPR compile_time_ansi_string nameof_v = fkengine::fkecore::nameof<t>();

        template<typename t, t val>
        FKE_CONSTEXPR compile_time_ansi_string nameof_value_v = fkengine::fkecore::nameof<t, val>();
#endif
    }
}