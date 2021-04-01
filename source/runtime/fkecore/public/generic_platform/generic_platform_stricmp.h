// Copyright 2021 Felix Kahle. All rights reserved.

#pragma once

#include "fkecore_types.h"

/** The namespace of the FKEngine. */
namespace fkengine
{
	/** Generic implementations of Stricmp. */
	struct generic_platform_stricmp
	{
		FKE_STATIC_STRUCT(generic_platform_stricmp)
		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string. 
		 * If they are equal to each other, 
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const ansichar_t* String1, const ansichar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const widechar_t* String1, const widechar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const utf8char_t* String1, const utf8char_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const utf16char_t* String1, const utf16char_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const utf32char_t* String1, const utf32char_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const ansichar_t* String1, const widechar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const ansichar_t* String1, const utf8char_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const ansichar_t* String1, const utf16char_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const ansichar_t* String1, const utf32char_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const widechar_t* String1, const ansichar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const utf8char_t* String1, const ansichar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const utf16char_t* String1, const ansichar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t stricmp(const utf32char_t* String1, const ansichar_t* String2);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t strnicmp(const ansichar_t* String1, const ansichar_t* String2, size_t Count);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t strnicmp(const widechar_t* String1, const widechar_t* String2, size_t Count);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t strnicmp(const ansichar_t* String1, const widechar_t* String2, size_t Count);

		/**
		 * Compares two null-terminated byte strings lexicographically.
		 * This function starts comparing the first character of each string.
		 * If they are equal to each other,
		 * it continues with the following pairs until the characters differ or until a terminating null-character is reached.
		 * This function performs a binary comparison of the characters.
		 *
		 * @param String1 - First string to be compared.
		 * @param String2 - Second string to be compared.
		 * @return - Returns an integral value indicating the relationship between the strings:
		 *			 < 0 : the first character that does not match has a lower value in String1 than in String2.
		 *			   0 : the contents of both strings are equal.
		 *			 > 0 : the first character that does not match has a greater value in String1 than in String2.
		 */
		FKECORE_API static int32_t strnicmp(const widechar_t* string_1, const ansichar_t* string_2, size_t count);
	};
}