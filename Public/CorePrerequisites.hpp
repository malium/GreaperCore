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
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <stack>

using namespace std::string_view_literals;

namespace greaper
{
	class IStream;

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

	class IProperty;
	template<class T> class TProperty;
	class Uuid;
	class IGreaperLibrary;

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

#define CREATE_TYPEINFO(type, RTIType, categoryType)                                                                   \
template<> struct greaper::refl::TypeInfo<type> {                                                                      \
	static constexpr ReflectedTypeID_t ID = RTIType; using Type = greaper::refl:: categoryType<type>;                  \
	static constexpr StringView Name = #type##sv ; }

#define CREATE_TYPEINFO_CNAME(type, RTIType, categoryType, name)                                                       \
template<> struct greaper::refl::TypeInfo<type> {                                                                      \
	static constexpr ReflectedTypeID_t ID = RTIType; using Type = greaper::refl:: categoryType<type>;                  \
	static constexpr StringView Name = name##sv ; }

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
CREATE_TYPEINFO_CNAME(greaper::IProperty, greaper::refl::RTI_Property, ComplexType, "Property");
CREATE_TYPEINFO_CNAME(greaper::String, greaper::refl::RTI_String, ContainerType, "String");
CREATE_TYPEINFO_CNAME(greaper::WString, greaper::refl::RTI_WString, ContainerType, "WString");

namespace greaper::refl
{
	template<class T> struct TypeInfo<TEnum<T>> { static constexpr ReflectedTypeID_t ID = RTI_Enum; using Type = PlainType<TEnum<T>>; static constexpr StringView Name = "Enum"sv; };
	template<typename T> struct TypeInfo<TProperty<T>> { static constexpr ReflectedTypeID_t ID = RTI_Property; using Type = ComplexType<TProperty<T>>; static constexpr StringView Name = "Property"sv; };
	template<typename F, typename S> struct TypeInfo<std::pair<F, S>> { static constexpr ReflectedTypeID_t ID = RTI_Pair; using Type = PlainType<std::pair<F, S>>; static constexpr StringView Name = "pair"sv; };
	template<typename T, sizet N> struct TypeInfo<std::array<T, N>> { static constexpr ReflectedTypeID_t ID = RTI_Array; using Type = ContainerType<std::array<T, N>>; static constexpr StringView Name = "array"sv; };
	template<typename T> struct TypeInfo<Vector<T>> { static constexpr ReflectedTypeID_t ID = RTI_Vector; using Type = ContainerType<Vector<T>>; static constexpr StringView Name = "vector"sv; };
	template<typename T> struct TypeInfo<Deque<T>> { static constexpr ReflectedTypeID_t ID = RTI_Deque; using Type = ContainerType<Deque<T>>; static constexpr StringView Name = "deque"sv; };
	template<typename T> struct TypeInfo<List<T>> { static constexpr ReflectedTypeID_t ID = RTI_List; using Type = ContainerType<List<T>>; static constexpr StringView Name = "list"sv; };
	template<typename K, typename C> struct TypeInfo<Set<K, C>> { static constexpr ReflectedTypeID_t ID = RTI_Set; using Type = ContainerType<Set<K, C>>; static constexpr StringView Name = "set"sv; };
	template<typename K, typename V, typename C> struct TypeInfo<Map<K, V, C>> { static constexpr ReflectedTypeID_t ID = RTI_Map; using Type = ContainerType<Map<K, V, C>>; static constexpr StringView Name = "map"sv; };
	template<typename K, typename C> struct TypeInfo<MultiSet<K, C>> { static constexpr ReflectedTypeID_t ID = RTI_MultiSet; using Type = ContainerType<MultiSet<K, C>>; static constexpr StringView Name = "multiset"sv; };
	template<typename K, typename V, typename C> struct TypeInfo<MultiMap<K, V, C>> { static constexpr ReflectedTypeID_t ID = RTI_MultiMap; using Type = ContainerType<MultiMap<K, V, C>>; static constexpr StringView Name = "multimap"sv; };
	template<typename T, typename H, typename C> struct TypeInfo<UnorderedSet<T, H, C>> { static constexpr ReflectedTypeID_t ID = RTI_UnorderedSet; using Type = ContainerType<UnorderedSet<T, H, C>>; static constexpr StringView Name = "unordered_set"sv; };
	template<typename K, typename V, typename H, typename C> struct TypeInfo<UnorderedMap<K, V, H, C>> { static constexpr ReflectedTypeID_t ID = RTI_UnorderedMap; using Type = ContainerType<UnorderedMap<K, V, H, C>>; static constexpr StringView Name = "unordered_map"sv; };
	template<typename K, typename V, typename H, typename C> struct TypeInfo<UnorderedMultiMap<K, V, H, C>> { static constexpr ReflectedTypeID_t ID = RTI_UnorderedMultiMap; using Type = ContainerType<UnorderedMultiMap<K, V, H, C>>; static constexpr StringView Name = "unordered_multimap"sv; };
	template<typename T, typename H, typename C> struct TypeInfo<UnorderedMultiSet<T, H, C>> { static constexpr ReflectedTypeID_t ID = RTI_UnorderedMultiSet; using Type = ContainerType<UnorderedMultiSet<T, H, C>>; static constexpr StringView Name = "unordered_multiset"sv; };
}

#undef CREATE_TYPEINFO
#undef CREATE_TYPEINFO_CNAME

#include "Base/Verify.hpp"

#endif /* CORE_PREREQUISITES_HPP */