/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_COMPLEX_FIELD_HPP
#define CORE_REFLECTION_COMPLEX_FIELD_HPP 1

#include "IField.hpp"

namespace greaper::refl
{
	template<class T>
	struct ComplexType : public BaseType<T>
	{
		static const Vector<std::shared_ptr<IField>> Fields;

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Complex;

		static inline constexpr ssizet StaticSize = 0;

		using ArrayValueType = int32;

		REFL_CREATE_METHODS(T);
		
		static std::expected<ReflectedSize_t, String> ToStream(const T& data, IStream& stream)
		{
			ReflectedSize_t totalSize = 0;
			for (const auto& field : Fields)
			{
				auto res = field->ToStream(&data, stream);
				if (!res.has_value())
					return res;
				
				totalSize += res.value();
			}
			return totalSize;
		}

		static std::expected<ReflectedSize_t, String> FromStream(T& data, IStream& stream)
		{
			ReflectedSize_t totalSize = 0;
			for (const auto& field : Fields)
			{
				auto res = field->FromStream(&data, stream);
				if (!res.has_value())
					return res;
				
				totalSize += res.value();
			}
			return totalSize;
		}

		static std::expected<cJSON*, String> ToJSON(const T& data, cJSON* json, StringView name)
		{
			cJSON* obj = cJSON_AddObjectToObject(json, name.data());
			for (const auto& field : Fields)
			{
				auto res = field->ToJSON(&data, obj);
				if (!res.has_value())
					return res;
			}
			return obj;
		}

		static std::expected<void, String> FromJSON(T& data, cJSON* json, StringView name)
		{
			cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (item == nullptr)
				return std::unexpected(std::format("[refl::ComplexType<T>::FromJSON] "
					"Couldn't obtain the value from json, the item with name '{}' was not found.", name));
			
			for (const auto& field : Fields)
			{
				auto res = field->FromJSON(&data, item);
				if (!res.has_value())
					return res;
			}
			return {};
		}

		static std::expected<String, String> ToString(const T& data)
		{
			String output {};
			output += "(";
			sizet i = 0;
			for (const auto& field : Fields)
			{
				auto res = field->ToString(&data);
				if (!res.has_value())
					return res;
				output += res.value();
				if (i < (Fields.size() - 1))
					output += ", ";
				++i;
			}
			output += ")";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const T& data)
		{
			ReflectedSize_t totalSize = 0;
			for (const auto& field : Fields)
			{
				auto sres = field->GetStaticSize();
				if (!sres.has_value())
					return sres;

				auto dres = field->GetDynamicSize(&data);
				if (!dres.has_value())
					return dres;

				totalSize += sres.value() + dres.value();
			}
			return totalSize;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(UNUSED const T& data)
		{
			return std::unexpected("Function 'ComplexType<T>::GetArraySize' Trying to use a ComplexType as array!");
		}

		static std::expected<void, String> SetArraySize(UNUSED T& data, UNUSED ReflectedSize_t size)
		{
			return std::unexpected("Function 'ComplexType<T>::SetArraySize' Trying to use a ComplexType as array!");
		}

		static std::expected<const ArrayValueType*, String> GetArrayValue(UNUSED const T& data,
			UNUSED ReflectedSize_t index)
		{
			return std::unexpected("Function 'ComplexType<T>::GetArrayValue' Trying to use a ComplexType as array!");
		}

		static std::expected<void, String> SetArrayValue(UNUSED T& data, UNUSED const ArrayValueType& value,
			UNUSED ReflectedSize_t index)
		{
			return std::unexpected("Function 'ComplexType<T>::SetArrayValue' Trying to use a ComplexType as array!");
		}
	};
}

#endif /* CORE_REFLECTION_COMPLEX_FIELD_HPP */