/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_BASETYPE_HPP
#define CORE_REFLECTION_BASETYPE_HPP 1

#include "../CorePrerequisites.hpp"
#include "../Base/cJSON.hpp"
#include "../Base/IStream.hpp"

ENUMERATION(TypeCategory, Plain, Container, Complex);

#define REFL_CREATE_METHODS(Type)                                                                                      \
static std::expected<std::pair<Type, ReflectedSize_t>, String> CreateFromStream(IStream& stream){                      \
	Type elem;                                                                                                         \
	auto res = FromStream(elem, stream);                                                                               \
	if (res.has_value())                                                                                               \
		return std::make_pair(elem, res.value());                                                                      \
	return std::unexpected(res.error());}                                                                              \
static std::expected<std::shared_ptr<cJSON>, String> CreateJSON(const Type& data, StringView name){                    \
	auto* obj = cJSON_CreateObject();                                                                                  \
	auto res = ToJSON(data, obj, name);                                                                                \
	if (res.has_value())                                                                                               \
		return std::shared_ptr<cJSON>(obj, cJSON_Delete);                                                              \
	return std::unexpected(res.error());}                                                                              \
static std::expected<Type, String> CreateFromJSON(cJSON* json, StringView name, bool caseSensitive = false){           \
	Type elem;                                                                                                         \
	auto res = FromJSON(elem, json, name, caseSensitive);                                                              \
	if (res.has_value())                                                                                               \
		return elem;                                                                                                   \
	return std::unexpected(res.error());}                                                                              \
static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name, bool caseSensitive = false){     \
	cJSON* item = nullptr;                                                                                             \
	if (!caseSensitive)                                                                                                \
		item = cJSON_GetObjectItemCaseSensitive(json, name.data());                                                    \
	else                                                                                                               \
		item = cJSON_GetObjectItem(json, name.data());                                                                 \
	if (item == nullptr)                                                                                               \
		return std::unexpected(std::format("["#Type"::FromJSON] "                                                      \
			"Couldn't obtain the value from json, the item with name '{}' was not found.", name));                     \
	auto res = FromJSON_Item(data, item);                                                                              \
	if (res.has_value())                                                                                               \
		return {};                                                                                                     \
	return std::unexpected(std::format("{}, item name '{}'", res.error(), name));}                                     \
static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name){                           \
	auto item_res = ToJSON_Item(data);                                                                                 \
	if (!item_res.has_value())                                                                                         \
		return std::unexpected(std::format("{}, item name '{}'", item_res.error(), name));                             \
	if (item_res.value() == nullptr)                                                                                   \
		return std::unexpected(std::format("["#Type"::ToJSON] Couldn't create the json item, with name '{}'.", name)); \
	auto ok = cJSON_AddItemToObject(json, name.data(), item_res.value());                                              \
	if (ok == 0)                                                                                                       \
		return std::unexpected(std::format("["#Type"::ToJSON] "                                                        \
			"Couldn't attach item, with name '{}', to the json object.", name));                                       \
	return item_res.value();}

namespace greaper::refl
{
	template<class T>
	struct BaseType
	{
		static_assert(TypeInfo<T>::ID != RTI_Unknown, "[refl::BaseType<T>] instantiated with an Unknown TypeID.");
		static_assert(!std::is_same_v<typename TypeInfo<T>::Type, void>, 
			"[refl::BaseType<T>] instantiated with a void type.");
			
		using ArrayValueType = void*;

		static inline constexpr ReflectedTypeID_t ID = TypeInfo_t<T>::ID;

		static inline constexpr ReflectedSize_t StaticSize = sizeof(T);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::COUNT;

		REFL_CREATE_METHODS(T);
		static std::expected<ReflectedSize_t, String> ToStream(UNUSED const T& data, UNUSED IStream& stream)
		{
			return std::unexpected("Function 'BaseType<T>::ToStream' not overriden!");
		}

		static std::expected<ReflectedSize_t, String> FromStream(UNUSED T& data, UNUSED IStream& stream)
		{
			return std::unexpected("Function 'BaseType<T>::FromStream' not overriden!");
		}

		static std::expected<cJSON*, String> ToJSON_Item(UNUSED const T& data)
		{
			return std::unexpected("Function 'BaseType<T>::ToJSON_Item' not overriden!");
		}

		static std::expected<void, String> FromJSON_Item(UNUSED T& data, UNUSED cJSON* item)
		{
			return std::unexpected("Function 'BaseType<T>::FromJSON_Item' not overriden!");
		}

		static std::expected<String, String> ToString(UNUSED const T& data)
		{
			return std::unexpected("Function 'BaseType<T>::ToString' not overriden!");
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(UNUSED const T& data)
		{
			return std::unexpected("Function 'BaseType<T>::GetDynamicSize' not overriden!");
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(UNUSED const T& data)
		{
			return std::unexpected("Function 'BaseType<T>::GetArraySize' not overriden!");
		}

		static std::expected<void, String> SetArraySize(UNUSED T& data, UNUSED ReflectedSize_t size)
		{
			return std::unexpected("Function 'BaseType<T>::SetArraySize' not overriden!");
		}

		static std::expected<const ArrayValueType*, String> GetArrayValue(UNUSED const T& data,
			UNUSED ReflectedSize_t index)
		{
			return std::unexpected("Function 'BaseType<T>::GetArrayValue' not overriden!");
		}

		static std::expected<void, String> SetArrayValue(UNUSED T& data, UNUSED const ArrayValueType& value,
			UNUSED ReflectedSize_t index)
		{
			return std::unexpected("Function 'BaseType<T>::SetArrayValue' not overriden!");
		}
	};
}

#endif /* CORE_REFLECTION_BASETYPE_HPP */