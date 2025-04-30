/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_CONTAINERTYPE_HPP
#define CORE_REFLECTION_CONTAINERTYPE_HPP 1

#include "BaseType.hpp"
#include "../Base/StringUtils.hpp"

namespace greaper::refl
{
	template<>
	struct ContainerType<String> : public BaseType<String>
	{
		using Type = String;
		using ArrayValueType = typename Type::value_type;

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const String& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();
			size += stream.Write(data.data(), dynamicSize);
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<String>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(String& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();
			size += stream.Read(data.data(), dynamicSize);
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<String>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const String& data, cJSON* json, StringView name)
		{
			cJSON* res = cJSON_AddStringToObject(json, name.data(), data.c_str());
			if (res != nullptr)
				return res;
			return std::unexpected(std::format("[refl::ContainerType<String>::ToJSON] "
				"Couldn't add a string with name '{}' to the object", name));
		}

		static std::expected<void, String> FromJSON(String& data, cJSON* json, StringView name)
		{
			cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (item == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<String>::FromJSON] "                                 
				"Couldn't obtain the value from json, the item with name '{}' was not found.", name));
			if (cJSON_IsString(item))
			{
				data.assign(cJSON_GetStringValue(item));
				return {};	
			}
			return std::unexpected(std::format("[refl::ContainerType<String>::FromJSON] "
				"Couldn't obtain the value from json, the item with name '{}' was not String.", name));
		}

		static std::expected<String, String> ToString(const String& data)
		{
			return data;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const String& data)
		{
			return data.size() * sizeof(ArrayValueType);
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const String& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(String& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const String& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<String>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(String& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<String>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<>
	struct ContainerType<WString> : public BaseType<WString>
	{
		using Type = WString;
		using ArrayValueType = typename Type::value_type;

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const WString& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();
			size += stream.Write(data.data(), dynamicSize);
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<WString>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(WString& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();
			size += stream.Read(data.data(), dynamicSize);
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<WString>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const WString& data, cJSON* json, StringView name)
		{
			cJSON* res = cJSON_AddStringToObject(json, name.data(), StringUtils::FromWIDE(data).c_str());
			if (res != nullptr)
				return res;
			return std::unexpected(std::format("[refl::ContainerType<String>::ToJSON] "
				"Couldn't add a string with name '{}' to the object", name));
		}

		static std::expected<void, String> FromJSON(WString& data, cJSON* json, StringView name)
		{
			cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (item == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<WString>::FromJSON] "                                 
				"Couldn't obtain the value from json, the item with name '{}' was not found.", name));
			if (cJSON_IsString(item))
			{
				data = StringUtils::ToWIDE(cJSON_GetStringValue(item));
				return {};	
			}
			return std::unexpected(std::format("[refl::ContainerType<WString>::FromJSON] "
				"Couldn't obtain the value from json, the item with name '{}' was not String.", name));
		}

		static std::expected<String, String> ToString(const WString& data)
		{
			return StringUtils::FromWIDE(data);
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const WString& data)
		{
			return data.size() * sizeof(ArrayValueType);
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const WString& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(WString& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const WString& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<WString>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(WString& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<WString>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, sizet N>
	struct ContainerType<std::array<T, N>> : public BaseType<std::array<T, N>>
	{
		using Type = std::array<T, N>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<array>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = ValueCat::StaticSize * N;

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			// If we have an array of plain data, we can just copy the whole data.
			if constexpr(std::is_same_v<ValueCat, PlainType<ArrayValueType>>)
			{
				size += stream.Write(data.data(), StaticSize);
			}
			// Otherwise we have to copy each value
			else
			{
				for (const ArrayValueType& elem : data)
				{
					auto res = ValueCat::ToStream(elem, stream);
					if (!res.has_value())
						return std::unexpected(res.error());
					
					size += res.value();
				}
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<array>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			ReflectedSize_t dynamicSize = 0;

			// If we have an array of plain data, we can just copy the whole data.
			if constexpr(std::is_same_v<ValueCat, PlainType<ArrayValueType>>)
			{
				size += stream.Read(data.data(), StaticSize);
			}
			// Otherwise we have to copy each value
			else
			{
				for (ArrayValueType& elem : data)
				{
					auto res = ValueCat::FromStream(elem, stream);
					if (!res.has_value())
						return std::unexpected(res.error());
					
					auto resDynamicSize = ValueCat::GetDynamicSize(elem);
					if (!resDynamicSize.has_value())
						return std::unexpected(resDynamicSize.error());
					dynamicSize += resDynamicSize.value();
					size += res.value();
				}
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<array>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<array>::ToJSON] "
						"Error while adding an item to the array, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<array>::FromJSON] "                                
				"Couldn't obtain the value from json, the array with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<array>::FromJSON] "                               
				"Couldn't obtain the value from json, the array with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			if (arraySize != N)
				return std::unexpected(std::format("[refl::ContainerType<array>::FromJSON] "                             
					"Couldn't obtain the value from json, the array with name '{}' "
					"have an expected size {} but obtained {}.", name, N, arraySize));

			achar buffer[32];
			for (sizet i = 0; i < N; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<array>::FromJSON] "
						"Couldn't obtain the value from json, the array with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(data[i], item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

#if COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable:4702)
#endif
		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			if constexpr (std::is_same_v<ValueCat, PlainType<ArrayValueType>>)
				return 0ll;
			
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += res_dynamicSize.value();
			}
			return size;
		}
#if COMPILER_MSVC
#pragma warning(pop)
#endif

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return N;
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			if (size == N)
				return {};
			return std::unexpected("[refl::ContainerType<array>::GetArrayValue] "
				"Trying to change the size of an array, different than its initial size.");
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<array>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<array>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::list<T>> : public BaseType<std::list<T>>
	{
		using Type = std::list<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<list>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<list>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (ArrayValueType& elem : data)
			{
				auto res = ValueCat::FromStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				auto resDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!resDynamicSize.has_value())
					return std::unexpected(resDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + resDynamicSize.value();
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<list>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<list>::ToJSON] "
						"Error while adding an item to the list, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<list>::FromJSON] "                                
				"Couldn't obtain the value from json, the list with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<list>::FromJSON] "                               
				"Couldn't obtain the value from json, the list with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			data.resize(arraySize);

			achar buffer[32];
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<list>::FromJSON] "
						"Couldn't obtain the value from json, the list with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(elem, item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += ValueCat::StaticSize + res_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<list>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<list>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::deque<T>> : public BaseType<std::deque<T>>
	{
		using Type = std::deque<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<deque>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<deque>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (ArrayValueType& elem : data)
			{
				auto res = ValueCat::FromStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				auto resDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!resDynamicSize.has_value())
					return std::unexpected(resDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + resDynamicSize.value();
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<deque>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<deque>::ToJSON] "
						"Error while adding an item to the deque, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON] "                                
				"Couldn't obtain the value from json, the deque with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON] "                               
				"Couldn't obtain the value from json, the deque with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			data.resize(arraySize);

			achar buffer[32];
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON] "
						"Couldn't obtain the value from json, the deque with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(elem, item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += ValueCat::StaticSize + res_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<deque>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<deque>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::set<T>> : public BaseType<std::set<T>>
	{
		using Type = std::set<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<set>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<set>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (ArrayValueType& elem : data)
			{
				auto res = ValueCat::FromStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				auto resDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!resDynamicSize.has_value())
					return std::unexpected(resDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + resDynamicSize.value();
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<set>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<set>::ToJSON] "
						"Error while adding an item to the set, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<set>::FromJSON] "                                
				"Couldn't obtain the value from json, the set with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<set>::FromJSON] "                               
				"Couldn't obtain the value from json, the set with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			data.resize(arraySize);

			achar buffer[32];
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<set>::FromJSON] "
						"Couldn't obtain the value from json, the set with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(elem, item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += ValueCat::StaticSize + res_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<set>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<set>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, class C>
	struct ContainerType<std::multiset<T, C>> : public BaseType<std::multiset<T, C>>
	{
		using Type = std::multiset<T, C>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<multiset>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<multiset>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (ArrayValueType& elem : data)
			{
				auto res = ValueCat::FromStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				auto resDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!resDynamicSize.has_value())
					return std::unexpected(resDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + resDynamicSize.value();
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<multiset>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<multiset>::ToJSON] "
						"Error while adding an item to the multiset, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<multiset>::FromJSON] "                                
				"Couldn't obtain the value from json, the multiset with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<multiset>::FromJSON] "                               
				"Couldn't obtain the value from json, the multiset with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			data.resize(arraySize);

			achar buffer[32];
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<multiset>::FromJSON] "
						"Couldn't obtain the value from json, the multiset with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(elem, item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += ValueCat::StaticSize + res_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<multiset>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<multiset>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, class H, class C>
	struct ContainerType<std::unordered_set<T, H, C>> : public BaseType<std::unordered_set<T, H, C>>
	{
		using Type = std::unordered_set<T, H, C>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_set>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_set>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (ArrayValueType& elem : data)
			{
				auto res = ValueCat::FromStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				auto resDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!resDynamicSize.has_value())
					return std::unexpected(resDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + resDynamicSize.value();
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_set>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<unordered_set>::ToJSON] "
						"Error while adding an item to the unordered_set, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<unordered_set>::FromJSON] "                                
				"Couldn't obtain the value from json, the unordered_set with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<unordered_set>::FromJSON] "                               
				"Couldn't obtain the value from json, the unordered_set with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			data.resize(arraySize);

			achar buffer[32];
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<unordered_set>::FromJSON] "
						"Couldn't obtain the value from json, the unordered_set with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(elem, item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += ValueCat::StaticSize + res_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<unordered_set>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<unordered_set>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, class H, class C>
	struct ContainerType<std::unordered_multiset<T, H, C>> : public BaseType<std::unordered_multiset<T, H, C>>
	{
		using Type = std::unordered_multiset<T, H, C>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_multiset>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (ArrayValueType& elem : data)
			{
				auto res = ValueCat::FromStream(elem, stream);
				if (!res.has_value())
					return std::unexpected(res.error());
				
				auto resDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!resDynamicSize.has_value())
					return std::unexpected(resDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + resDynamicSize.value();
				size += res.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			achar buffer[32];
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				cJSON* obj = cJSON_CreateObject();
				auto res = ValueCat::ToJSON(elem, obj, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::ToJSON] "
						"Error while adding an item to the unordered_multiset, name {}, idx {}.", name, i-1));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::FromJSON] "                                
				"Couldn't obtain the value from json, the unordered_multiset with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
			return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::FromJSON] "                               
				"Couldn't obtain the value from json, the unordered_multiset with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			data.resize(arraySize);

			achar buffer[32];
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::FromJSON] "
						"Couldn't obtain the value from json, the unordered_multiset with name '{}' "
						"returned a null child at index {}.", name, i));
				const std::format_to_n_result fres = std::format_to_n(buffer, ARRAY_SIZE(buffer), "Elem_{}", i++);
				*fres.out = '\0';
				auto res = ValueCat::FromJSON(elem, item, StringView(buffer, fres.out));
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value() + ", ";
			}
			output += "]";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res_dynamicSize = ValueCat::GetDynamicSize(elem);
				if (!res_dynamicSize.has_value())
					return std::unexpected(res_dynamicSize.error());
				size += ValueCat::StaticSize + res_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			data.resize(size);
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return data[index];
			return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				data[index] = value;
				return {};
			return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class P>
	struct ContainerType<std::map<K, V, P>> : public BaseType<std::map<K, V, P>>
	{
		using Type = std::map<K, V, P>>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo<K>::Type;
		using ValueCat = typename TypeInfo<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<map>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<map>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				size += kres.value();

				auto vres = ValueCat::ToStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				size += vres.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<map>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(elem);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += res.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += res.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<map>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<map>::ToJSON] "
						"Error while adding a key-value item to the map, name {}.", name));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON] "                                
				"Couldn't obtain the value from json, the map with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON] "                               
				"Couldn't obtain the value from json, the map with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();

			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON] "
						"Couldn't obtain the value from json, the map with name '{}' "
						"returned a null child at index {}.", name, i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() " : " + vres.value() + ", ";
			}
			output += "}";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const auto& [key, value] : data)
			{
				auto kres_dynamicSize = KeyCat::GetDynamicSize(key);
				if (!kres_dynamicSize.has_value())
					return std::unexpected(kres_dynamicSize.error());
				auto vres_dynamicSize = ValueCat::GetDynamicSize(value);
				if (!vres_dynamicSize.has_value())
					return std::unexpected(vres_dynamicSize.error());
				size += KeyCat::StaticSize + kres_dynamicSize.value() + ValueCat::StaticSize + vres_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						return keyvalue;
					++i;
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<map>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<map>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class P>
	struct ContainerType<std::multimap<K, V, P>> : public BaseType<std::multimap<K, V, P>>
	{
		using Type = std::multimap<K, V, P>>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo<K>::Type;
		using ValueCat = typename TypeInfo<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<multimap>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<multimap>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				size += kres.value();

				auto vres = ValueCat::ToStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				size += vres.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<multimap>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(elem);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += res.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += res.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<multimap>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<multimap>::ToJSON] "
						"Error while adding a key-value item to the multimap, name {}.", name));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<multimap>::FromJSON] "                                
				"Couldn't obtain the value from json, the multimap with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<multimap>::FromJSON] "                               
				"Couldn't obtain the value from json, the multimap with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();

			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<multimap>::FromJSON] "
						"Couldn't obtain the value from json, the multimap with name '{}' "
						"returned a null child at index {}.", name, i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() " : " + vres.value() + ", ";
			}
			output += "}";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const auto& [key, value] : data)
			{
				auto kres_dynamicSize = KeyCat::GetDynamicSize(key);
				if (!kres_dynamicSize.has_value())
					return std::unexpected(kres_dynamicSize.error());
				auto vres_dynamicSize = ValueCat::GetDynamicSize(value);
				if (!vres_dynamicSize.has_value())
					return std::unexpected(vres_dynamicSize.error());
				size += KeyCat::StaticSize + kres_dynamicSize.value() + ValueCat::StaticSize + vres_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						return keyvalue;
					++i;
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<multimap>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<multimap>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class H, class C>
	struct ContainerType<std::unordered_map<K, V, H, C>> : public BaseType<std::unordered_map<K, V, H, C>>
	{
		using Type = std::unordered_map<K, V, H, C>>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo<K>::Type;
		using ValueCat = typename TypeInfo<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<unordered_map>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_map>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				size += kres.value();

				auto vres = ValueCat::ToStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				size += vres.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_map>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(elem);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += res.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += res.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_map>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<unordered_map>::ToJSON] "
						"Error while adding a key-value item to the unordered_map, name {}.", name));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<unordered_map>::FromJSON] "                                
				"Couldn't obtain the value from json, the unordered_map with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<unordered_map>::FromJSON] "                               
				"Couldn't obtain the value from json, the unordered_map with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();

			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<unordered_map>::FromJSON] "
						"Couldn't obtain the value from json, the unordered_map with name '{}' "
						"returned a null child at index {}.", name, i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() " : " + vres.value() + ", ";
			}
			output += "}";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const auto& [key, value] : data)
			{
				auto kres_dynamicSize = KeyCat::GetDynamicSize(key);
				if (!kres_dynamicSize.has_value())
					return std::unexpected(kres_dynamicSize.error());
				auto vres_dynamicSize = ValueCat::GetDynamicSize(value);
				if (!vres_dynamicSize.has_value())
					return std::unexpected(vres_dynamicSize.error());
				size += KeyCat::StaticSize + kres_dynamicSize.value() + ValueCat::StaticSize + vres_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						return keyvalue;
					++i;
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_map>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_map>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class H, class C>
	struct ContainerType<std::unordered_multimap<K, V, H, C>> : public BaseType<std::unordered_multimap<K, V, H, C>>
	{
		using Type = std::unordered_multimap<K, V, H, C>>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo<K>::Type;
		using ValueCat = typename TypeInfo<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<unordered_multimap>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_multimap>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);

		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		static std::expected<ReflectedSize_t, String> ToStream(const Type& data, IStream& stream)
		{
			ReflectedSize_t size = 0;
			sizet elemCount = data.size();
			size += stream.Write(&elemCount, sizeof(elemCount));
			auto resDynamicSize = GetDynamicSize(data);
			if (!resDynamicSize.has_value())
				return std::unexpected(resDynamicSize.error());
			auto dynamicSize = resDynamicSize.value();

			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				size += kres.value();

				auto vres = ValueCat::ToStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				size += vres.value();
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::ToStream] "
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<ReflectedSize_t, String> FromStream(Type& data, IStream& stream)
		{
			sizet elemCount;
			ReflectedSize_t size = 0;
			size += stream.Read(&elemCount, sizeof(elemCount));
			data.clear();
			data.resize(elemCount);
			ReflectedSize_t dynamic_size = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(elem);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += res.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(elem);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += res.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON(const Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_AddArrayToObject(json, name.data());
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arr, obj);
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::ToJSON] "
						"Error while adding a key-value item to the unordered_multimap, name {}.", name));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON(Type& data, cJSON* json, StringView name)
		{
			cJSON* arrayObject = cJSON_GetObjectItemCaseSensitive(json, name.data());
			if (arrayObject == nullptr)
				return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromJSON] "                                
				"Couldn't obtain the value from json, the unordered_multimap with name '{}' was not found.", name));
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromJSON] "                               
				"Couldn't obtain the value from json, the unordered_multimap with name '{}' was not an array.", name));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();

			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromJSON] "
						"Couldn't obtain the value from json, the unordered_multimap with name '{}' "
						"returned a null child at index {}.", name, i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() " : " + vres.value() + ", ";
			}
			output += "}";
			return output;
		}

		static std::expected<ReflectedSize_t, String> GetDynamicSize(const Type& data)
		{
			ReflectedSize_t size = 0;
			for (const auto& [key, value] : data)
			{
				auto kres_dynamicSize = KeyCat::GetDynamicSize(key);
				if (!kres_dynamicSize.has_value())
					return std::unexpected(kres_dynamicSize.error());
				auto vres_dynamicSize = ValueCat::GetDynamicSize(value);
				if (!vres_dynamicSize.has_value())
					return std::unexpected(vres_dynamicSize.error());
				size += KeyCat::StaticSize + kres_dynamicSize.value() + ValueCat::StaticSize + vres_dynamicSize.value();
			}
			return size;
		}

		static std::expected<ReflectedSize_t, String> GetArraySize(const Type& data)
		{
			return data.size();
		}

		static std::expected<void, String> SetArraySize(Type& data, ReflectedSize_t size)
		{
			return {};
		}

		static std::expected<const ArrayValueType&, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						return keyvalue;
					++i;
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::GetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize));
		}

		static std::expected<void, String> SetArrayValue(Type& data, const ArrayValueType& value,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
			{
				sizet i = 0;
				for (const auto& keyvalue : data)
				{
					if (i == index)
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};
}

#endif /* CORE_REFLECTION_CONTAINERTYPE_HPP */