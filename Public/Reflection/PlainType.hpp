/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_PLAINTYPE_HPP
#define CORE_REFLECTION_PLAINTYPE_HPP 1

#include "BaseType.hpp"
#include "../Base/IStream.hpp"

#define CREATE_BASIC_PLAINTYPE(type, jsonCreateFn, jsonIsFn, jsonGetFn)                                                \
template<>struct PlainType<type> : public BaseType<type> {                                                             \
	static inline constexpr ReflectedTypeID_t ID = TypeInfo_t<type>::ID;                                               \
	static inline constexpr ReflectedSize_t StaticSize = sizeof(type);                                                 \
	static inline constexpr TypeCategory_t Category = TypeCategory_t::Plain;                                           \
	REFL_CREATE_METHODS(type);                                                                                         \
	static std::expected<ReflectedSize_t, String> ToStream(const type& data, IStream& stream){                         \
		const auto size = stream.Write(&data, sizeof(data));                                                           \
		if (size == sizeof(data))                                                                                      \
			return size;                                                                                               \
		return std::unexpected(std::format("[refl::PlainType<"#type">::ToStream] "                                     \
			"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",                     \
			sizeof(data), size));}                                                                                     \
	static std::expected<ReflectedSize_t, String> FromStream(type& data, IStream& stream){                             \
		const auto size = stream.Read(&data, sizeof(data));                                                            \
		if (size == sizeof(data))                                                                                      \
			return size;                                                                                               \
		return std::unexpected(std::format("[refl::PlainType<"#type">::FromStream] "                                   \
			"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",                      \
			sizeof(data), size));}                                                                                     \
	static std::expected<cJSON*, String> ToJSON_Item(const type& data){                                                \
		return jsonCreateFn(data);}                                                                                    \
	static std::expected<void, String> FromJSON_Item(type& data, cJSON* jsonItem){                                     \
		if (jsonIsFn(jsonItem)){                                                                                       \
			data = static_cast<type>(jsonGetFn(jsonItem));                                                             \
			return {};}                                                                                                \
		return std::unexpected("[refl::PlainType<"#type">::FromJSON] "                                                 \
			"Couldn't obtain the value from json, the item was not "#jsonIsFn".");}                                    \
	static std::expected<String, String> ToString(const type& data){                                                   \
		return std::format("{}", data);}                                                                               \
	static std::expected<ReflectedSize_t, String> GetDynamicSize(UNUSED const type& data){                             \
		return 0ll;}                                                                                                   \
	static std::expected<ReflectedSize_t, String> GetArraySize(UNUSED const type& data){                               \
		return std::unexpected("Function 'PlainType<"#type">::GetArraySize' Trying to use a PlainType as array!");}    \
	static std::expected<void, String> SetArraySize(UNUSED type& data, UNUSED ReflectedSize_t size){                   \
		return std::unexpected("Function 'PlainType<"#type">::SetArraySize' Trying to use a PlainType as array!");}    \
	static std::expected<const ArrayValueType*, String> GetArrayValue(UNUSED const type& data,                         \
		UNUSED ReflectedSize_t index){                                                                                 \
		return std::unexpected("Function 'PlainType<"#type">::GetArrayValue' Trying to use a PlainType as array!");}   \
	static std::expected<void, String> SetArrayValue(UNUSED type& data, UNUSED const ArrayValueType& value,            \
		UNUSED ReflectedSize_t index){                                                                                 \
		return std::unexpected("Function 'PlainType<"#type">::SetArrayValue' Trying to use a PlainType as array!");}   \
}

#if COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable:4244)
#endif
namespace greaper::refl
{
	CREATE_BASIC_PLAINTYPE(bool, 			cJSON_CreateBool, 		cJSON_IsBool, 	cJSON_IsTrue);
	CREATE_BASIC_PLAINTYPE(int8,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint8,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(int16,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint16,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(int32,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint32,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(int64,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint64,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(float,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(double,			cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(long double,		cJSON_CreateNumber, 	cJSON_IsNumber, cJSON_GetNumberValue);

	/* Reflected enums need a special BaseType class */
	template<class T>
	struct PlainType<TEnum<T>> : public BaseType<TEnum<T>>
	{
		static_assert(std::is_enum_v<T>, "[refl::BaseType<TEnum>] trying to instantiate a TEnum with a non enum type.");
		static inline constexpr ReflectedTypeID_t ID = RTI_Enum;
		static inline constexpr ReflectedSize_t StaticSize = sizeof(std::underlying_type_t<T>);
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Plain;
		using ArrayValueType = int32;
		REFL_CREATE_METHODS(T);
		static std::expected<ReflectedSize_t, String> ToStream(const T& data, IStream& stream)
		{
			const auto size = stream.Write(&data, sizeof(data));
			if (size == sizeof(data))
				return size;
			return std::unexpected(std::format("[refl::PlainType<TEnum>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				sizeof(data), size));
		}
		static std::expected<ReflectedSize_t, String> FromStream(T& data, IStream& stream)
		{
			const auto size = stream.Read(&data, sizeof(data));
			if (size == sizeof(data))
				return size;
			return std::unexpected(std::format("[refl::PlainType<TEnum>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				sizeof(data), size));
		}
		static std::expected<cJSON*, String> ToJSON_Item(const T& data)
		{
			auto str = TEnum<T>::ToString(data);
			return cJSON_CreateString(str.data());
		}
		static std::expected<void, String> FromJSON_Item(T& data, cJSON* jsonItem)
		{
			if (cJSON_IsString(jsonItem))
			{
				data = TEnum<T>::FromString(cJSON_GetStringValue(jsonItem));
				return {};
			}
			return std::unexpected("[refl::PlainType<TEnum>::FromJSON] "
				"Couldn't obtain the value from json, the item was not ENUM.");
		}
		static std::expected<String, String> ToString(const T& data)
		{
			return TEnum<T>::ToString(data);
		}
		static std::expected<ReflectedSize_t, String> GetDynamicSize(UNUSED const T& data)
		{
			return 0ll;
		}
		static std::expected<ReflectedSize_t, String> GetArraySize(UNUSED const T& data)
		{
			return std::unexpected("Function 'PlainType<TEnum>::GetArraySize' Trying to use a PlainType as array!");
		}
		static std::expected<void, String> SetArraySize(UNUSED T& data, UNUSED ReflectedSize_t size)
		{
			return std::unexpected("Function 'PlainType<TEnum>::SetArraySize' Trying to use a PlainType as array!");
		}
		static std::expected<const ArrayValueType*, String> GetArrayValue(UNUSED const T& data,
			UNUSED ReflectedSize_t index)
		{
			return std::unexpected("Function 'PlainType<TEnum>::GetArrayValue' Trying to use a PlainType as array!");
		}
		static std::expected<void, String> SetArrayValue(UNUSED T& data, UNUSED const ArrayValueType& value,         
			UNUSED ReflectedSize_t index)
		{
			return std::unexpected("Function 'PlainType<TEnum>::SetArrayValue' Trying to use a PlainType as array!");
		}
	};

	template<class First, class Second>
	struct PlainType<std::pair<First, Second>> : BaseType<std::pair<First, Second>>
	{
		using Type = std::pair<First, Second>;
		using FirstCat = typename TypeInfo_t<First>::Type;
		using SecondCat = typename TypeInfo_t<Second>::Type;

		static_assert(!std::is_same_v<FirstCat, void>,
			"[refl::PlainType<pair>] Trying to use a pair but the First value doesn't have TypeInfo.");
		static_assert(!std::is_same_v<SecondCat, void>,
			"[refl::PlainType<pair>] Trying to use a pair but the Second value doesn't have TypeInfo.");

		static inline constexpr ReflectedTypeID_t ID = RTI_Pair;
		static inline constexpr ReflectedSize_t StaticSize = FirstCat::StaticSize + SecondCat::StaticSize;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Plain;
		using ArrayValueType = void*;
		
		REFL_CREATE_METHODS(Type);

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			auto res_DynamicSize = GetDynamicSize(data);
			if (!res_DynamicSize.has_value())
				return std::unexpected(res_DynamicSize.error());
			auto dynamicSize = res_DynamicSize.value();

			auto res_firstSize = FirstCat::ToStream(data.first, stream);
			if (!res_firstSize.has_value())
				return std::unexpected(res_firstSize.error());
			auto res_secondSize = SecondCat::ToStream(data.second, stream);
			if (!res_secondSize.has_value())
				return std::unexpected(res_secondSize.error());
			ReflectedSize_t size = res_firstSize.value() + res_secondSize.value();
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::PlainType<pair>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}
		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			auto res_DynamicSize = GetDynamicSize(data);
			if (!res_DynamicSize.has_value())
				return std::unexpected(res_DynamicSize.error());
			auto dynamicSize = res_DynamicSize.value();

			auto res_firstSize = FirstCat::FromStream(data.first, stream);
			if (!res_firstSize.has_value())
				return std::unexpected(res_firstSize.error());
			auto res_secondSize = SecondCat::FromStream(data.second, stream);
			if (!res_secondSize.has_value())
				return std::unexpected(res_secondSize.error());
			ReflectedSize_t size = res_firstSize.value() + res_secondSize.value();
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::PlainType<pair>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}
		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* jsonObj = cJSON_CreateObject();
			auto res_firstJSON = FirstCat::ToJSON(data.first, jsonObj, "first"sv);
			if (!res_firstJSON.has_value())
			{
				cJSON_Delete(jsonObj);
				return std::unexpected(res_firstJSON.error());
			}
			auto res_secondJSON = SecondCat::ToJSON(data.second, jsonObj, "second"sv);
			if (!res_secondJSON.has_value())
			{
				cJSON_Delete(jsonObj);
				return std::unexpected(res_secondJSON.error());
			}
			return jsonObj;
		}
		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* jsonItem)
		{
			auto res_firstJSON = FirstCat::FromJSON(data.first, jsonItem, "first"sv);
			if (!res_firstJSON.has_value())
				return std::unexpected(res_firstJSON.error());
			auto res_secondJSON = SecondCat::FromJSON(data.second, jsonItem, "second"sv);
			if (!res_secondJSON.has_value())
				return std::unexpected(res_secondJSON.error());
			return {};
		}
		static std::expected<String, String> ToString(const Type& data)
		{
			auto res_firstString = FirstCat::ToString(data.first);
			if (!res_firstString.has_value())
					return std::unexpected(res_firstString.error());
			auto res_secondString = SecondCat::ToString(data.second);
			if (!res_secondString.has_value())
					return std::unexpected(res_secondString.error());

			return std::format("[{}, {}]", res_firstString.value(), res_secondString.value());
		}
		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			auto res_firstDynamicSize = FirstCat::GetDynamicSize(data.first);
			if (!res_firstDynamicSize.has_value())
				return std::unexpected(res_firstDynamicSize.error());
			auto res_secondDynamicSize = SecondCat::GetDynamicSize(data.second);
			if (!res_secondDynamicSize.has_value())
				return std::unexpected(res_secondDynamicSize.error());
			return res_firstDynamicSize.value() + res_secondDynamicSize.value();
		}
		static std::expected<ReflectedSize_t, String> GetArraySize(UNUSED const Type& data)
		{
			return 2;
		}
		static std::expected<void, String> SetArraySize(UNUSED Type& data, ReflectedSize_t size)
		{
			if(size == 2)
				return {};
			return std::unexpected("[refl::PlainType<pair>::SetArraySize] Trying to change the size of a pair.");
		}
		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data, ReflectedSize_t index)
		{
			if (index == 0)
				return (const ArrayValueType*)&data.first;
			if (index == 1)
				return (const ArrayValueType*)&data.second;
			return std::unexpected(std::format("[refl::PlainType<pair>::GetArrayValue] "
				"Index '{}' out of bounds [0,2]", index));
		}
		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value, ReflectedSize_t index)
		{
			if (index == 0)
			{
				data.first = *static_cast<Type::first_type*>((ArrayValueType)value);
				return {};
			}
			if (index == 1)
			{
				data.second = *static_cast<Type::second_type*>((ArrayValueType)value);
				return {};
			}
			return std::unexpected(std::format("[refl::PlainType<pair>::SetArrayValue] "
				"Index '{}' out of bounds [0,2]", index));
		}
	};
}

#if COMPILER_MSVC
#pragma warning(pop)
#endif

#endif /* CORE_REFLECTION_PLAINTYPE_HPP */