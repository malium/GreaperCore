/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_PLAINTYPE_HPP
#define CORE_REFLECTION_PLAINTYPE_HPP 1

#include "BaseType.hpp"
#include "../Base/IStream.hpp"

#define CREATE_BASIC_PLAINTYPE(type, jsonAddFn, jsonIsFn, jsonGetFn)                                                   \
template<>struct PlainType<type> : public BaseType<type> {                                                             \
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
	static std::expected<cJSON*, String> ToJSON(const type& data, cJSON* json, StringView name){                       \
		jsonAddFn(json, name.data(), data); return {};}                                                                \
	static std::expected<void, String> FromJSON(type& data, cJSON* json, StringView name){                             \
		cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.data());                                             \
		if (item == nullptr)                                                                                           \
			return std::unexpected(std::format("[refl::PlainType<"#type">::FromJSON] "                                 \
			"Couldn't obtain the value from json, the item with name '{}' was not found.", name));                     \
		if (jsonIsFn(item)){                                                                                           \
			data = static_cast<type>(jsonGetFn(item));                                                                 \
			return {};}                                                                                                \
		return std::unexpected(std::format("[refl::PlainType<"#type">::FromJSON] "                                     \
			"Couldn't obtain the value from json, the item with name '{}' was not "#jsonIsFn".", name));}              \
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
	CREATE_BASIC_PLAINTYPE(bool, 			cJSON_AddBoolToObject, 		cJSON_IsBool, 	cJSON_IsTrue);
	CREATE_BASIC_PLAINTYPE(int8,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint8,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(int16,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint16,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(int32,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint32,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(int64,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(uint64,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(float,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(double,			cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);
	CREATE_BASIC_PLAINTYPE(long double,		cJSON_AddNumberToObject, 	cJSON_IsNumber, cJSON_GetNumberValue);

	/* Reflected enums need a special BaseType class */
	template<class T>
	struct PlainType<TEnum<T>> : public BaseType<TEnum<T>>
	{
		static_assert(std::is_enum_v<T>, "[refl::BaseType<TEnum>] trying to instantiate a TEnum with a non enum type.");
		static inline constexpr ReflectedTypeID_t ID = RTI_Enum;
		static inline constexpr ReflectedSize_t StaticSize = sizeof(std::underlying_type_t<T>);
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Plain;
		using ArrayValueType = int32;
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
		static std::expected<cJSON*, String> ToJSON(const T& data, cJSON* json, StringView name)
		{
			auto str = TEnum<T>::ToString(data);
			return cJSON_AddStringToObject(json, name.data(), str.data());
		}                                                                        
		static std::expected<void, String> FromJSON(T& data, cJSON* json, StringView name)
		{                          
			cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.data());             
			if (item == nullptr)                                                                                        
				return std::unexpected(std::format("[refl::PlainType<TEnum>::FromJSON] "                              
				"Couldn't obtain the value from json, the item with name '{}' was not found.", name));                  
			if (cJSON_IsString(item))
			{          
				data = TEnum<T>::FromString(cJSON_GetStringValue(item));               
				return {};
			}                                                                                             
			return std::unexpected(std::format("[refl::PlainType<TEnum>::FromJSON] "                                  
				"Couldn't obtain the value from json, the item with name '{}' was not ENUM.", name));
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
}

#if COMPILER_MSVC
#pragma warning(pop)
#endif

#endif /* CORE_REFLECTION_PLAINTYPE_HPP */