/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_PREREQUISITES_HPP
#define CORE_PREREQUISITES_HPP 1

#include "Base/PHAL.hpp"
#include "Base/Enumeration.hpp"
#include <string>
#include <string_view>
#include <chrono>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <deque>
#include <queue>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <stack>
#include <utility>
#include <memory>
#include <expected>

using namespace std::string_view_literals;

namespace greaper
{
	class Uuid;
	class IStream;
	class MemoryStream;
	class FileStream;

	template<typename T>
	using BasicString = std::basic_string<T, std::char_traits<T>>;
	template<typename T>
	using BasicStringView = std::basic_string_view<T, std::char_traits<T>>;
	template<typename T>
	using BasicStringStream = std::basic_stringstream<T, std::char_traits<T>>;

	template<typename T>
	using Vector = std::vector<T>;
	template<typename T>
	using Queue = std::queue<T, std::deque<T>>;
	template<typename T>
	using Deque = std::deque<T>;
	template<typename T>
	using List = std::list<T>;
	template<typename T>
	using ForwardList = std::forward_list<T>;
	template<typename T>
	using Stack = std::stack<T, std::deque<T>>;
	template<typename K, typename C = std::less<K>>
	using Set = std::set<K, C>;
	template<typename K, typename V, typename P = std::less<K>>
	using Map = std::map<K, V, P>;
	template<typename K, typename C = std::less<K>>
	using MultiSet = std::multiset<K, C>;
	template<typename K, typename V, typename P = std::less<K>>
	using MultiMap = std::multimap<K, V, P>;
	namespace Impl
	{
		struct EnumClassHash
		{
			template<typename T>
			INLINE constexpr std::size_t operator()(T t)const
			{
				return static_cast<std::size_t>(t);
			}
		};
	}
	template<typename Key>
	using HashType = typename std::conditional_t<std::is_enum_v<Key>, Impl::EnumClassHash, std::hash<Key>>;
	template<typename T, typename H = HashType<T>, typename C = std::equal_to<T>>
	using UnorderedSet = std::unordered_set<T, H, C>;
	template<typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>>
	using UnorderedMap = std::unordered_map<K, V, H, C>;
	template<typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>>
	using UnorderedMultiMap = std::unordered_multimap<K, V, H, C>;
	template<typename T, typename H = HashType<T>, typename C = std::equal_to<T>>
	using UnorderedMultiSet = std::unordered_multiset<T, H, C>;

	using String = BasicString<achar>;
	using StringView = BasicStringView<achar>;
	using StringStream = BasicStringStream<achar>;
	using StringVec = Vector<String>;

	using WString = BasicString<wchar>;
	using WStringView = BasicStringView<wchar>;
	using WStringStream = BasicStringStream<wchar>;
	using WStringVec = Vector<WString>;

	using Clock_t = std::chrono::high_resolution_clock;
	using Timepoint_t = Clock_t::time_point;
	using Duration_t = Clock_t::duration;

	using ReflectedFieldID_t = uint16;
	using ReflectedTypeID_t = uint32;
	using ReflectedSize_t = int64;

	namespace refl
	{
		enum CoreReflectedTypeID : ReflectedTypeID_t
		{
			RTI_Unknown = 0,

			// Base types
			RTI_Bool = 1,
			RTI_Int8,
			RTI_Uint8,
			RTI_Int16,
			RTI_Uint16,
			RTI_Int32,
			RTI_Uint32,
			RTI_Int64,
			RTI_Uint64,
			RTI_Float,
			RTI_Double,
			RTI_LongDouble,
			RTI_Enum,
			RTI_UUID = 40,
			RTI_Property,			

			// Base Containers
			RTI_String = 25,
			RTI_WString,
			RTI_Array,
			RTI_Vector,
			RTI_List,
			RTI_Deque,
			RTI_Map,
			RTI_UnorderedMap,
			RTI_MultiMap,
			RTI_UnorderedMultiMap,
			RTI_Pair,
			RTI_Set,
			RTI_UnorderedSet,
			RTI_MultiSet,
			RTI_UnorderedMultiSet,
		};

		template<class T> struct BaseType;
		template<class T> struct PlainType {  };
		template<class T> struct ContainerType {  };
		template<class T> struct ComplexType;

		template<class T> struct TypeInfo
		{
			static constexpr ReflectedTypeID_t ID = std::is_enum_v<T> ? RTI_Enum : RTI_Unknown;
			using Type = std::conditional_t<std::is_enum_v<T>, PlainType<TEnum<T>>, void>;
			static constexpr StringView Name = std::is_enum_v<T> ? "Enum"sv : "Unknown"sv;
		};

		template<class T> using TypeInfo_t = TypeInfo<std::decay_t<T>>;
	}
}

#define CREATE_TYPEINFO_CNAME_TEMPLATELESS(type, RTIType, categoryType, name)                                          \
struct greaper::refl::TypeInfo<type> {                                                                                 \
	static constexpr ReflectedTypeID_t ID = RTIType; using Type = greaper::refl:: categoryType<type>;                  \
	static constexpr StringView Name = name##sv ; }

#define CREATE_TYPEINFO_CNAME(type, RTIType, categoryType, name)                                                       \
template<> CREATE_TYPEINFO_CNAME_TEMPLATELESS(type, RTIType, categoryType, name)

#define CREATE_TYPEINFO(type, RTIType, categoryType) CREATE_TYPEINFO_CNAME(type, RTIType, categoryType, #type)

CREATE_TYPEINFO(bool, greaper::refl::RTI_Bool, PlainType);
CREATE_TYPEINFO(int8, greaper::refl::RTI_Int8, PlainType);
CREATE_TYPEINFO(uint8, greaper::refl::RTI_Uint8, PlainType);
CREATE_TYPEINFO(int16, greaper::refl::RTI_Int16, PlainType);
CREATE_TYPEINFO(uint16, greaper::refl::RTI_Uint16, PlainType);
CREATE_TYPEINFO(int32, greaper::refl::RTI_Int32, PlainType);
CREATE_TYPEINFO(uint32, greaper::refl::RTI_Uint32, PlainType);
CREATE_TYPEINFO(int64, greaper::refl::RTI_Int64, PlainType);
CREATE_TYPEINFO(uint64, greaper::refl::RTI_Uint64, PlainType);
CREATE_TYPEINFO(float, greaper::refl::RTI_Float, PlainType);
CREATE_TYPEINFO(double, greaper::refl::RTI_Double, PlainType);
CREATE_TYPEINFO(long double, greaper::refl::RTI_LongDouble, PlainType);

CREATE_TYPEINFO_CNAME(greaper::Uuid, greaper::refl::RTI_UUID, PlainType, "UUID");
CREATE_TYPEINFO_CNAME(greaper::String, greaper::refl::RTI_String, ContainerType, "String");
CREATE_TYPEINFO_CNAME(greaper::WString, greaper::refl::RTI_WString, ContainerType, "WString");
template<class T>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(TEnum<T>, greaper::refl::RTI_Enum, PlainType, "Enum");
template<typename F, typename S>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::pair<F MACRO_COMMA S>, greaper::refl::RTI_Pair, PlainType, "Pair");
template<typename T, sizet N>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::array<T MACRO_COMMA N>, greaper::refl::RTI_Array, ContainerType, "Array");
template<class T>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::vector<T>, greaper::refl::RTI_Vector, ContainerType, "Vector");
template<class T>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::deque<T>, greaper::refl::RTI_Deque, ContainerType, "Deque");
template<class T>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::list<T>, greaper::refl::RTI_List, ContainerType, "List");
template<typename K, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::set<K MACRO_COMMA C>, greaper::refl::RTI_Set, ContainerType, "Set");
template<typename K, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::multiset<K MACRO_COMMA C>, greaper::refl::RTI_MultiSet, ContainerType,         \
	"MultiSet");
template<typename T, typename H, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::unordered_set<T MACRO_COMMA H MACRO_COMMA C>, greaper::refl::RTI_UnorderedSet, \
	ContainerType, "UnorderedSet");
template<typename T, typename H, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::unordered_multiset<T MACRO_COMMA H MACRO_COMMA C>,                             \
	greaper::refl::RTI_UnorderedMultiSet, ContainerType, "UnorderedMultiSet");
template<typename K, typename V, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::map<K MACRO_COMMA V MACRO_COMMA C>, greaper::refl::RTI_Map, ContainerType,     \
	"Map");
template<typename K, typename V, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::multimap<K MACRO_COMMA V MACRO_COMMA C>, greaper::refl::RTI_MultiMap,          \
	ContainerType, "MultiMap");
template<typename K, typename V, typename H, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::unordered_map<K MACRO_COMMA V MACRO_COMMA H MACRO_COMMA C>,                    \
	greaper::refl::RTI_UnorderedMap, ContainerType, "UnorderedMap");
template<typename K, typename V, typename H, typename C>
CREATE_TYPEINFO_CNAME_TEMPLATELESS(std::unordered_multimap<K MACRO_COMMA V MACRO_COMMA H MACRO_COMMA C>,               \
	greaper::refl::RTI_UnorderedMultiMap, ContainerType, "UnorderedMultiMap");

#ifndef USE_CXX_STACKTRACE
#if __has_cpp_attribute(__cpp_lib_stacktrace)
#define USE_CXX_STACKTRACE 1
#include <stacktrace>
#else
#define USE_CXX_STACKTRACE 0
#endif
#endif

#ifndef USE_CXX_FORMAT
#if __has_cpp_attribute(__cpp_lib_format)
#define USE_CXX_FORMAT 1
#include <format>
#else
#define USE_CXX_FORMAT 0
#endif
#endif

#include "Base/Verify.hpp"

#endif /* CORE_PREREQUISITES_HPP */