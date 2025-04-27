/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_BASETYPE_HPP
#define CORE_REFLECTION_BASETYPE_HPP 1

#include "../CorePrerequisites.hpp"
#include <expected>
#include "../Base/cJSON.hpp"
#include "../Base/IStream.hpp"

ENUMERATION(TypeCategory, Plain, Container, Complex);

namespace greaper::refl
{
	template<class T>
	struct BaseType
	{
		static_assert(TypeInfo<T>::ID != RTI_Unknown, "[refl::BaseType<T>] instantiated with an Unknown TypeID.");
		static_assert(!std::is_same_v<typename TypeInfo<T>::Type, void>, 
			"[refl::BaseType<T>] instantiated with a void type.");

		using ArrayValueType = int32;

		static inline constexpr ReflectedTypeID_t ID = TypeInfo<T>::ID;

		static inline constexpr ReflectedSize_t StaticSize = sizeof(T);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::COUNT;

		static std::expected<ReflectedSize_t, String> ToStream(UNUSED const T& data, UNUSED IStream& stream)
		{
			return std::unexpected("Function 'BaseType<T>::ToStream' not overriden!");
		}

		static std::expected<ReflectedSize_t, String> FromStream(UNUSED T& data, UNUSED IStream& stream)
		{
			return std::unexpected("Function 'BaseType<T>::FromStream' not overriden!");
		}

		static std::expected<std::pair<T, ReflectedSize_t>, String> CreateFromStream(IStream& stream)
		{
			T elem;
			auto res = FromStream(elem, stream);
			if (res.has_value())
				return std::make_pair(elem, res.value());
			return res.error();
		}

		static std::expected<cJSON*, String> ToJSON(UNUSED const T& data, UNUSED cJSON* json, UNUSED StringView name)
		{
			return std::unexpected("Function 'BaseType<T>::ToJSON' not overriden!"); 
		}

		static std::expected<void, String> FromJSON(UNUSED T& data, UNUSED cJSON* json, UNUSED StringView name)
		{
			return std::unexpected("Function 'BaseType<T>::FromJSON' not overriden!");
		}

		static std::expected<std::shared_ptr<cJSON>, String> CreateJSON(const T& data, StringView name)
		{
			auto* obj = cJSON_CreateObject();
			auto res = ToJSON(data, obj, name);
			if (res.has_value())
				return std::shared_ptr<cJSON>(obj, cJSON_Delete);
			return std::unexpected(res.error());
		}

		static std::expected<T, String> CreateFromJSON(cJSON* json, StringView name)
		{
			T elem;
			auto res = FromJSON(elem, json, name);
			if (res.has_value())
				return elem;
			return res.error();
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

		static std::expected<const ArrayValueType&, String> GetArrayValue(UNUSED const T& data,
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