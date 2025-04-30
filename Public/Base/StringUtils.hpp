/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

 #pragma once

 #ifndef CORE_STRING_UTILS_HPP
 #define CORE_STRING_UTILS_HPP 1

#include "../CorePrerequisites.hpp"

namespace greaper::StringUtils
{
	namespace Impl
	{
		template<typename T>
		T UTF8To32(T begin, T end, u32char& output, u32char invalidChar = 0) noexcept
		{
			if (begin >= end)
				return begin;

			static constexpr uint32 offsets[6] = { 0x00000000, 0x00003080, 0x000E2080, 0x03C82080, 0xFA082080, 0x82082080 };

			uint32 numBytes;

			const auto firstByte = (uint8)*begin;
			if (firstByte < 192)
				numBytes = 1;
			else if (firstByte < 224)
				numBytes = 2;
			else if (firstByte < 240)
				numBytes = 3;
			else if (firstByte < 248)
				numBytes = 4;
			else if (firstByte < 252)
				numBytes = 5;
			else
				numBytes = 6;

			if ((begin + numBytes) > end)
			{
				output = invalidChar;
				return end;
			}

			output = 0;
			switch (numBytes)
			{
				case 6: output += (uint8)(*begin); ++begin; output <<= 6;
				case 5: output += (uint8)(*begin); ++begin; output <<= 6;
				case 4: output += (uint8)(*begin); ++begin; output <<= 6;
				case 3: output += (uint8)(*begin); ++begin; output <<= 6;
				case 2: output += (uint8)(*begin); ++begin; output <<= 6;
				case 1: output += (uint8)(*begin); ++begin;
				default: break;
			}
			output -= offsets[numBytes - 1];
			return begin;
		}

		template<typename T>
		T UTF32To8(u32char input, T output, uint32 maxElems, achar invalidChar = 0) noexcept
		{
			if (maxElems == 0)
				return output;
			
			static constexpr uint8 headers[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

			if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF)))
			{
				*output = invalidChar;
				++output;
				return output;
			}

			uint32 numBytes;
			if (input < 0x80)
				numBytes = 1;
			else if (input < 0x800)
				numBytes = 2;
			else if (input < 0x10000)
				numBytes = 3;
			else
				numBytes = 4;

			if (numBytes > maxElems)
			{
				*output = invalidChar;
				++output;
				return output;
			}

			achar bytes[4];
			switch (numBytes)
			{
				case 4: bytes[3] = (achar)((input | 0x80) & 0xBF); input >>= 6;
				case 3: bytes[2] = (achar)((input | 0x80) & 0xBF); input >>= 6;
				case 2: bytes[1] = (achar)((input | 0x80) & 0xBF); input >>= 6;
				case 1: bytes[0] = (achar)(input | headers[numBytes]);
				default: break;
			}

			output = std::copy(bytes, bytes + numBytes, output);
			return output;
		}

		template<typename T>
		T UTF16To32(T begin, T end, u32char& output, u32char invalidChar = 0) noexcept
		{
			if (begin >= end)
				return begin;

			const auto firstElem = (u16char)*begin;
			++begin;

			if ((firstElem >= 0xD800) && (firstElem <= 0xDBFF))
			{
				if (begin >= end)
				{
					output = invalidChar;
					return end;
				}

				const auto secondElem = (u32char)*begin;
				++begin;

				if ((secondElem >= 0xDC00) && (secondElem <= 0xDFFF))
					output = (u32char)(((firstElem - 0xD800) << 10) + (secondElem - 0xDC00) + 0x0010000);
				else
					output = invalidChar;
			}
			else
			{
				output = (u32char)firstElem;
				return begin;
			}
			return begin;
		}

		template<typename T>
		static T UTF32To16(u32char input, T output, uint32 maxElems, u16char invalidChar = 0) noexcept
		{
			if (maxElems == 0)
				return output;

			if (input > 0x0010FFFF)
			{
				*output = invalidChar;
				++output;

				return output;
			}

			if (input <= 0xFFFF)
			{
				if ((input >= 0xD800) && (input <= 0xDFFF))
				{
					*output = invalidChar;
					++output;

					return output;
				}

				*output = (u16char)input;
				++output;
			}
			else
			{
				if (maxElems < 2)
				{
					*output = invalidChar;
					++output;

					return output;
				}

				input -= 0x0010000;
				*output = (u16char)((input >> 10) + 0xD800);
				++output;

				*output = (u16char)((input & 0x3FFUL) + 0xDC00);
				++output;
			}
			return output;
		}

		template<typename T>
		INLINE T WIDEToUTF32(T begin, T end, u32char& output, u32char invalidChar = 0) noexcept
		{
#if PLT_LINUX
			output = (u32char)*begin;
			++begin;
			return begin;
#else
			return UTF16To32(begin, end, output, invalidChar);
#endif
		}

		template<typename T>
		INLINE T UTF32ToWIDE(u32char input, T output, uint32 maxElems, wchar invalidChar = 0) noexcept
		{
#if PLT_LINUX
			* output = (wchar)input;
			++output;

			return output;
#else
			return UTF32To16(input, output, maxElems, invalidChar);
#endif
		}

		template<typename T>
		struct CaseImpl {  };

		template<>
		struct CaseImpl<achar>
		{
			int(*Lower)(int C) = &::tolower;
			int(*Upper)(int C) = &::toupper;
		};

		template<>
		struct CaseImpl<wchar>
		{
			wint_t(*Lower)(wint_t c) = &::towlower;
			wint_t(*Upper)(wint_t c) = &::towupper;
		};
	}

	/**
	 * @brief Converts a WIDE string into an ANSI string
	 * 
	 * @param str The WIDE string
	 * @return String The converted ANSI string
	 */
	String FromWIDE(const WString& str) noexcept
	{
		String output;
		output.reserve(str.size());

		auto backInserter = std::back_inserter(output);

		for (auto it = str.begin(); it != str.end();)
		{
			u32char c32 = 0;
			it = Impl::WIDEToUTF32(it, str.end(), c32);
			Impl::UTF32To8(c32, backInserter, 4);
		}
		return output;
	}

	/**
	 * @brief Converts a WIDE string into an ANSI string
	 *
	 * @param str The WIDE string
	 * @return String The converted ANSI string
	 */
	String FromWIDE(WStringView str) noexcept
	{
		String output;
		output.reserve(str.size());

		auto backInserter = std::back_inserter(output);

		for (auto it = str.begin(); it != str.end();)
		{
			u32char c32 = 0;
			it = Impl::WIDEToUTF32(it, str.end(), c32);
			Impl::UTF32To8(c32, backInserter, 4);
		}
		return output;
	}

	/**
	 * @brief Converts a WIDE string into an ANSI string
	 * 
	 * @param str The WIDE string
	 * @return String The converted ANSI string
	 */
	String FromWIDE(const wchar* str) noexcept
	{
		return FromWIDE(WStringView(str));
	}

	/**
	 * @brief Converts an ANSI string into a WIDE string
	 * 
	 * @param str The ANSI string
	 * @return WString The Converted WIDE string
	 */
	WString ToWIDE(const String& str) noexcept
	{
		WString output;
		output.reserve(str.size());

		auto backInserter = std::back_inserter(output);

		for (auto it = str.begin(); it != str.end(); )
		{
			u32char c32 = 0;
			it = Impl::UTF8To32(it, str.end(), c32);
			Impl::UTF32ToWIDE(c32, backInserter, 2);
		}

		return output;
	}

	/**
	 * @brief Converts an ANSI string into a WIDE string
	 *
	 * @param str The ANSI string
	 * @return WString The Converted WIDE string
	 */
	WString ToWIDE(StringView str) noexcept
	{
		WString output;
		output.reserve(str.size());

		auto backInserter = std::back_inserter(output);

		for (auto it = str.begin(); it != str.end(); )
		{
			u32char c32 = 0;
			it = Impl::UTF8To32(it, str.end(), c32);
			Impl::UTF32ToWIDE(c32, backInserter, 2);
		}

		return output;
	}

	/**
	 * @brief Converts an ANSI string into a WIDE string
	 * 
	 * @param str The ANSI string
	 * @return WString The Converted WIDE string
	 */
	WString ToWIDE(const achar* str) noexcept
	{
		return ToWIDE(StringView(str));
	}

	/**
	 * @brief Counts how many characters 'token' are inside the given string
	 * 
	 * @tparam T Type of character, auto deducted by param str
	 * @param str The string to look for tokens
	 * @param token The character to find
	 * @return sizet The amount of characters found
	 */
	template<typename T>
	sizet Contains(const BasicString<T>& str, T token) noexcept
	{
		sizet count = 0;
		for (const T c : str)
		{
			if (c == token)
				++count;
		}
		return count;
	}

	/**
	 * @brief Counts how many characters 'token' are inside the given string
	 *
	 * @tparam T Type of character, auto deducted by param str
	 * @param str The string to look for tokens
	 * @param token The character to find
	 * @return sizet The amount of characters found
	 */
	template<typename T>
	constexpr sizet Contains(BasicStringView<T> str, T token) noexcept
	{
		sizet count = 0;
		for (const T c : str)
		{
			if (c == token)
				++count;
		}
		return count;
	}

	/**
	 * @brief Counts how many strings 'token' are inside the given string
	 * 
	 * @tparam T The type of character, auto deducted by param str
	 * @param str The string to look for tokens
	 * @param token The string to find
	 * @return sizet The amount of strings found
	 */
	template<typename T>
	sizet Contains(const BasicString<T>& str, const BasicString<T>& token) noexcept
	{
		sizet count = 0;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
				++count;
		}
		return count;
	}

	/**
	 * @brief Counts how many strings 'token' are inside the given string
	 *
	 * @tparam T The type of character, auto deducted by param str
	 * @param str The string to look for tokens
	 * @param token The string to find
	 * @return sizet The amount of strings found
	 */
	template<typename T>
	sizet Contains(BasicStringView<T> str, const BasicString<T>& token) noexcept
	{
		sizet count = 0;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
				++count;
		}
		return count;
	}

	/**
	 * @brief Counts how many strings 'token' are inside the given string
	 *
	 * @tparam T The type of character, auto deducted by param str
	 * @param str The string to look for tokens
	 * @param token The string to find
	 * @return sizet The amount of strings found
	 */
	template<typename T>
	sizet Contains(const BasicString<T>& str, BasicStringView<T> token) noexcept
	{
		sizet count = 0;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
				++count;
		}
		return count;
	}

	/**
	 * @brief Counts how many strings 'token' are inside the given string
	 *
	 * @tparam T The type of character, auto deducted by param str
	 * @param str The string to look for tokens
	 * @param token The string to find
	 * @return sizet The amount of strings found
	 */
	template<typename T>
	constexpr sizet Contains(BasicStringView<T> str, BasicStringView<T> token) noexcept
	{
		sizet count = 0;
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
				++count;
		}
		return count;
	}

	/**
	 * @brief Joins a vector of string into a single string with a given separator
	 * 
	 * @tparam T Type of char, auto deducted from vec and separator
	 * @param vec Vector of strings to compose into one
	 * @param separator The character that will be between the strings (NULL/0) no in-between character
	 * @return BasicString<T> The string composed from all the strings in the vector
	 */
	template<typename T>
	BasicString<T> ComposeString(const std::vector<BasicString<T>>& vec, T separator = T(0)) noexcept
	{
		BasicString<T> rtn;
		if(separator != T(0))
		{
			for (sizet i = 0; i < vec.size(); ++i)
			{
				rtn += vec[i];
				if (i != (vec.size() - 1))
					rtn += separator;
			}
		}
		else
		{
			for(const auto& str : vec)
				rtn += str;
		}

		return rtn;
	}

	/**
	 * @brief Joins a vector of string into a single string with a given separator
	 *
	 * @tparam T Type of char, auto deducted from vec and separator
	 * @param vec Vector of strings to compose into one
	 * @param separator The character that will be between the strings (NULL/0) no in-between character
	 * @return BasicString<T> The string composed from all the strings in the vector
	 */
	template<typename T>
	BasicString<T> ComposeString(const std::vector<BasicStringView<T>>& vec, T separator = T(0)) noexcept
	{
		BasicString<T> rtn;
		if (separator != T(0))
		{
			for (sizet i = 0; i < vec.size(); ++i)
			{
				rtn += vec[i];
				if (i != (vec.size() - 1))
					rtn += separator;
			}
		}
		else
		{
			for (const auto& str : vec)
				rtn += str;
		}

		return rtn;
	}

	/**
	 * @brief Joins a vector of string into a single string with a given separator
	 * 
	 * @tparam T Type of char, auto deducted from vec and separator
	 * @param vec Vector of strings to compose into one
	 * @param separator The string that will be between the strings
	 * @return BasicString<T> The string composed from all the strings in the vector
	 */
	template<typename T>
	BasicString<T> ComposeString(const std::vector<BasicString<T>>& vec,
		const BasicString<T>& separator) noexcept
	{
		BasicString<T> rtn;
		for (sizet i = 0; i < vec.size(); ++i)
		{
			rtn += vec[i];
			if (i != (vec.size() - 1))
				rtn += separator;
		}
		return rtn;
	}

	/**
	 * @brief Joins a vector of string into a single string with a given separator
	 *
	 * @tparam T Type of char, auto deducted from vec and separator
	 * @param vec Vector of strings to compose into one
	 * @param separator The string that will be between the strings
	 * @return BasicString<T> The string composed from all the strings in the vector
	 */
	template<typename T>
	BasicString<T> ComposeString(const std::vector<BasicString<T>>& vec, BasicStringView<T> separator) noexcept
	{
		BasicString<T> rtn;
		for (sizet i = 0; i < vec.size(); ++i)
		{
			rtn += vec[i];
			if (i != (vec.size() - 1))
				rtn += separator;
		}
		return rtn;
	}

	/**
	 * @brief Joins a vector of string into a single string with a given separator
	 *
	 * @tparam T Type of char, auto deducted from vec and separator
	 * @param vec Vector of strings to compose into one
	 * @param separator The string that will be between the strings
	 * @return BasicString<T> The string composed from all the strings in the vector
	 */
	template<typename T>
	BasicString<T> ComposeString(const std::vector<BasicStringView<T>>& vec, const BasicString<T>& separator) noexcept
	{
		BasicString<T> rtn;
		for (sizet i = 0; i < vec.size(); ++i)
		{
			rtn += vec[i];
			if (i != (vec.size() - 1))
				rtn += separator;
		}
		return rtn;
	}

	/**
	 * @brief Joins a vector of string into a single string with a given separator
	 *
	 * @tparam T Type of char, auto deducted from vec and separator
	 * @param vec Vector of strings to compose into one
	 * @param separator The string that will be between the strings
	 * @return BasicString<T> The string composed from all the strings in the vector
	 */
	template<typename T>
	BasicString<T> ComposeString(const std::vector<BasicStringView<T>>& vec, BasicStringView<T> separator) noexcept
	{
		BasicString<T> rtn;
		for (sizet i = 0; i < vec.size(); ++i)
		{
			rtn += vec[i];
			if (i != (vec.size() - 1))
				rtn += separator;
		}
		return rtn;
	}

	/**
	 * @brief Separates a string given a token character
	 * 
	 * @tparam T Type of char
	 * @param str The string that is going to be separated
	 * @param token The character to find in order to split the string
	 * @return std::vector<BasicString<T>> The vector of splitted strings
	 */
	template<typename T>
	std::vector<BasicString<T>> Tokenize(const BasicString<T>& str, T token) noexcept
	{
		std::vector<BasicString<T>> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if ((*it) == token)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), std::distance(lastToken, it)));
				lastToken = it;
				++lastToken;
			}
		}
		rtn.push_back(BasicString<T>(lastToken, str.end()));
		return rtn;
	}

	/**
	 * @brief Separates a string given a token character
	 *
	 * @tparam T Type of char
	 * @param str The string that is going to be separated
	 * @param token The character to find in order to split the string
	 * @return std::vector<BasicString<T>> The vector of splitted strings
	 */
	template<typename T>
	std::vector<BasicString<T>> Tokenize(BasicStringView<T> str, T token) noexcept
	{
		std::vector<BasicString<T>> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if ((*it) == token)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), std::distance(lastToken, it)));
				lastToken = it;
				++lastToken;
			}
		}
		rtn.push_back(BasicString<T>(lastToken, str.end()));
		return rtn;
	}

	/**
	 * @brief Splits a string given a token string
	 * 
	 * @tparam T The type of char
	 * @param str The string to split
	 * @param token The string to find
	 * @return std::vector<BasicString<T>> The Vector of strings from str
	 */
	template<typename T>
	std::vector<BasicString<T>> Tokenize(const BasicString<T>& str,
		const BasicString<T>& token) noexcept
	{
		std::vector<BasicString<T>> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		const size_t tokenSize = token.size();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (static_cast<size_t>(std::distance(it, str.end())) < tokenSize)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken)));
				break;
			}
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), tokenSize));
				it += tokenSize;
			}
		}
		rtn.push_back(BasicString<T>(lastToken, str.end()));
		return rtn;
	}

	/**
	 * @brief Splits a string given a token string
	 *
	 * @tparam T The type of char
	 * @param str The string to split
	 * @param token The string to find
	 * @return std::vector<BasicString<T>> The Vector of strings from str
	 */
	template<typename T>
	std::vector<BasicString<T>> Tokenize(BasicStringView<T> str, const BasicString<T>& token) noexcept
	{
		std::vector<BasicString<T>> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		const size_t tokenSize = token.size();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (static_cast<size_t>(std::distance(it, str.end())) < tokenSize)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken)));
				break;
			}
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), tokenSize));
				it += tokenSize;
			}
		}
		rtn.push_back(BasicString<T>(lastToken, str.end()));
		return rtn;
	}

	/**
	 * @brief Splits a string given a token string
	 *
	 * @tparam T The type of char
	 * @param str The string to split
	 * @param token The string to find
	 * @return std::vector<BasicString<T>> The Vector of strings from str
	 */
	template<typename T>
	std::vector<BasicString<T>> Tokenize(BasicStringView<T> str, BasicStringView<T> token) noexcept
	{
		std::vector<BasicString<T>> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		const size_t tokenSize = token.size();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (static_cast<size_t>(std::distance(it, str.end())) < tokenSize)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken)));
				break;
			}
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), tokenSize));
				it += tokenSize;
			}
		}
		rtn.push_back(BasicString<T>(lastToken, str.end()));
		return rtn;
	}

	/**
	 * @brief Splits a string given a token string
	 *
	 * @tparam T The type of char
	 * @param str The string to split
	 * @param token The string to find
	 * @return std::vector<BasicString<T>> The Vector of strings from str
	 */
	template<typename T>
	std::vector<BasicString<T>> Tokenize(const BasicString<T>& str, BasicStringView<T> token) noexcept
	{
		std::vector<BasicString<T>> rtn;
		if (str.empty())
			return rtn;
		auto lastToken = str.begin();
		const size_t tokenSize = token.size();
		for (auto it = str.begin(); it != str.end(); ++it)
		{
			if (static_cast<size_t>(std::distance(it, str.end())) < tokenSize)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken)));
				break;
			}
			auto itt = it;
			bool match = true;
			for (auto ittt = token.begin(); ittt != token.end(); ++ittt)
			{
				if ((*itt) != (*ittt))
				{
					match = false;
					break;
				}
				++itt;
			}
			if (match)
			{
				rtn.emplace_back(str.substr(std::distance(str.begin(), lastToken), tokenSize));
				it += tokenSize;
			}
		}
		rtn.push_back(BasicString<T>(lastToken, str.end()));
		return rtn;
	}

	/**
	 * @brief Splits a string by spaces
	 * 
	 * @tparam T The type of character
	 * @param str The string to split
	 * @return std::vector<BasicString<T>> The vector of strings
	 */
	template<typename T>
	std::vector<BasicString<T>> SeparateBySpace(const BasicString<T>& str) noexcept
	{
		return Tokenize(str, T(' '));
	}

	/**
	 * @brief Splits a string by spaces
	 *
	 * @tparam T The type of character
	 * @param str The string to split
	 * @return std::vector<BasicString<T>> The vector of strings
	 */
	template<typename T>
	std::vector<BasicString<T>> SeparateBySpace(BasicStringView<T> str) noexcept
	{
		return Tokenize(str, T(' '));
	}

	/**
	 * @brief Removes the unnecessary characters from the beginning and the ending of the string
	 * 
	 * @tparam T The type of the character
	 * @param str The string to trim
	 * @param delims Which characters to remove
	 * @param left Trim the beginning?
	 * @param right Trim the ending?
	 * @return BasicString<T>& The trimmed string
	 */
	template<typename T>
	BasicString<T>& TrimSelf(BasicString<T>& str, const Vector<T>& delims,
		bool left = true, bool right = true) noexcept
	{
		bool keepSearching = false;
		if (right)
		{
			keepSearching = true;
			while (keepSearching)
			{
				keepSearching = false;
				for (const auto& d : delims)
				{
					if (str.back() == d)
					{
						str.erase(str.begin() + str.size() - 1);
						keepSearching = true;
						break;
					}
				}
			}
		}
		if (left)
		{
			keepSearching = true;
			while (keepSearching)
			{
				keepSearching = false;
				for (const auto& d : delims)
				{
					if (*str.begin() == d)
					{
						str.erase(str.begin());
						keepSearching = true;
						break;
					}
				}
			}
		}
		return str;
	}

	/**
	 * @brief Removes the unnecessary characters from the beginning and the ending of the string
	 * 
	 * @tparam T The type of the character
	 * @param str The string to trim
	 * @param delims Which characters to remove
	 * @param left Trim the beginning?
	 * @param right Trim the ending?
	 * @return BasicString<T> The trimmed string
	 */
	template<typename T>
	BasicString<T> Trim(const BasicString<T>& str, const Vector<T>& delims,
		bool left = true, bool right = true) noexcept
	{
		BasicString<T> cpy{str};

		TrimSelf(cpy, delims, left, right);
		return cpy;
	}

	/**
	 * @brief Removes the unnecessary characters from the beginning and the ending of the string
	 * 
	 * @tparam T The type of the character
	 * @param str The string to trim
	 * @param left Trim the beginning?
	 * @param right Trim the ending?
	 * @return BasicString<T>& The trimmed string
	 */
	template<typename T>
	BasicString<T>& TrimSelf(BasicString<T>& str, bool left = true, bool right = true) noexcept
	{
		static Vector<T> delims { T(' '), T('\t'), T('\r'), T('\n') };
		return TrimSelf(str, delims, left, right);
	}

	/**
	 * @brief Removes the unnecessary characters from the beginning and the ending of the string
	 * 
	 * @tparam T The type of the character
	 * @param str The string to trim
	 * @param left Trim the beginning?
	 * @param right Trim the ending?
	 * @return BasicString<T> The trimmed string
	 */
	template<typename T>
	BasicString<T> Trim(const BasicString<T>& str, bool left = true, bool right = true) noexcept
	{
		static Vector<T> delims {T(' '), T('\t'), T('\r'), T('\n')};
		return Trim(str, delims, left, right);
	}

	/**
	 * @brief Replaces a given character to another from a string
	 * 
	 * @tparam T The type of the character
	 * @param str The string to replace the character
	 * @param toReplace The character wanted to replace
	 * @param replacement The character that subtitutes
	 * @return BasicString<T, _Alloca_> The string with the characters replaced
	 */
	template<typename T>
	BasicString<T> Replace(const BasicString<T>& str, T toReplace, T replacement) noexcept
	{
		return ComposeString(Tokenize(str, toReplace), replacement);
	}

	/**
	 * @brief Replaces a given character to another from a string
	 *
	 * @tparam T The type of the character
	 * @tparam _Alloca_ The allocator type of the string
	 * @param str The string to replace the character
	 * @param toReplace The character wanted to replace
	 * @param replacement The character that subtitutes
	 * @return BasicString<T, _Alloca_> The string with the characters replaced
	 */
	template<typename T>
	BasicString<T> Replace(BasicStringView<T> str, T toReplace, T replacement) noexcept
	{
		return ComposeString<T>(Tokenize<T>(str, toReplace), replacement);
	}

	/**
	 * @brief Replaces a given string to another from a string
	 * 
	 * @tparam T The type of the character
	 * @param str The string to find toReplace and change it for replacement
	 * @param toReplace The string to find inside str
	 * @param replacement The string to substitute 
	 * @return BasicString<T> The resulting string
	 */
	template<typename T>
	BasicString<T> Replace(const BasicString<T>& str,
		const BasicString<T>& toReplace, const BasicString<T>& replacement) noexcept
	{
		return ComposeString(Tokenize(str, toReplace), replacement);
	}

	/**
	 * @brief Replaces a given string to another from a string
	 *
	 * @tparam T The type of the character
	 * @param str The string to find toReplace and change it for replacement
	 * @param toReplace The string to find inside str
	 * @param replacement The string to substitute
	 * @return BasicString<T> The resulting string
	 */
	template<typename T>
	BasicString<T> Replace(const BasicString<T>& str,
		BasicStringView<T> toReplace, BasicStringView<T> replacement) noexcept
	{
		return ComposeString(Tokenize(str, toReplace), replacement);
	}

	/**
	 * @brief Replaces a given string to another from a string
	 *
	 * @tparam T The type of the character
	 * @param str The string to find toReplace and change it for replacement
	 * @param toReplace The string to find inside str
	 * @param replacement The string to substitute
	 * @return BasicString<T> The resulting string
	 */
	template<typename T>
	BasicString<T> Replace(BasicStringView<T> str,
		const BasicString<T>& toReplace, const BasicString<T>& replacement) noexcept
	{
		return ComposeString(Tokenize(str, toReplace), replacement);
	}

	/**
	 * @brief Replaces a given string to another from a string
	 *
	 * @tparam T The type of the character
	 * @param str The string to find toReplace and change it for replacement
	 * @param toReplace The string to find inside str
	 * @param replacement The string to substitute
	 * @return BasicString<T> The resulting string
	 */
	template<typename T>
	BasicString<T> Replace(BasicStringView<T> str,
		BasicStringView<T> toReplace, BasicStringView<T> replacement) noexcept
	{
		return ComposeString<T>(Tokenize<T>(str, toReplace), replacement);
	}

	/**
	 * @brief Lowers the given string
	 * 
	 * @tparam T The type of the characters
	 * @param str The string to lower
	 * @return BasicString<T>& The string lowered
	 */
	template<typename T>
	BasicString<T>& ToLowerSelf(BasicString<T>& str) noexcept
	{
		Impl::CaseImpl<T> caseTransform;
		for (T& c : str)
			c = (T)caseTransform.Lower(c);
		return str;
	}
	
	/**
	 * @brief Lowers the given string
	 * 
	 * @tparam T The type of the characters
	 * @param str The string to lower
	 * @return BasicString<T> The string lowered
	 */
	template<typename T>
	BasicString<T> ToLower(const BasicString<T>& str) noexcept
	{
		BasicString<T> temp{ str.c_str(), str.size() };
		return ToLowerSelf(temp);
	}

	/**
	 * @brief Lowers the given string
	 *
	 * @tparam T The type of the characters
	 * @param str The string to lower
	 * @return BasicString<T> The string lowered
	 */
	template<typename T>
	BasicString<T> ToLower(BasicStringView<T> str) noexcept
	{
		BasicString<T> temp{ str };
		return ToLowerSelf(temp);
	}

	/**
	 * @brief Uppers the given string
	 * 
	 * @tparam T The type of the characters
	 * @param str The string to upper
	 * @return BasicString<T>& The string uppered
	 */
	template<typename T>
	BasicString<T>& ToUpperSelf(BasicString<T>& str) noexcept
	{
		Impl::CaseImpl<T> caseTransform;
		for (T& c : str)
			c = (T)caseTransform.Upper(c);
		return str;
	}

	/**
	 * @brief Uppers the given string
	 * 
	 * @tparam T The type of the characters
	 * @param str The string to upper
	 * @return BasicString<T, _Alloca_> The string uppered
	 */
	template<typename T>
	BasicString<T> ToUpper(const BasicString<T>& str) noexcept
	{
		BasicString<T> temp{ str.c_str(), str.size() };
		return ToUpperSelf(temp);
	}

	/**
	 * @brief Uppers the given string
	 *
	 * @tparam T The type of the characters
	 * @param str The string to upper
	 * @return BasicString<T> The string uppered
	 */
	template<typename T>
	BasicString<T> ToUpper(BasicStringView<T> str) noexcept
	{
		BasicString<T> temp{ str };
		return ToUpperSelf(temp);
	}

	/**
	 * @brief Returns whether if the given string is only numbers or contains other information
	 * 
	 * @tparam T The type of the characters
	 * @param str The string to check
	 * @return true The string only contains numbers
	 * @return false The string contains other characters
	 */
	template<typename T>
	bool StringNumber(const BasicString<T>& str) noexcept
	{
		for (const auto& chr : str)
		{
			if (!IsWithinInclusive(chr, T('0'), T('9')) && chr != T(',') && chr != T('.') && chr != T('+') && chr != T('-') && chr != T('e') && chr != T('E'))
				return false;
		}
		return true;
	}

	/**
	 * @brief Returns whether if the given string is only numbers or contains other information
	 *
	 * @tparam T The type of the characters
	 * @param str The string to check
	 * @return true The string only contains numbers
	 * @return false The string contains other characters
	 */
	template<typename T>
	constexpr bool StringNumber(BasicStringView<T> str) noexcept
	{
		for (const auto& chr : str)
		{
			if (!IsWithinInclusive(chr, T('0'), T('9')) && chr != T(',') && chr != T('.') && chr != T('+') && chr != T('-') && chr != T('e') && chr != T('E'))
				return false;
		}
		return true;
	}
}

 #endif /* CORE_STRING_UTILS_HPP */