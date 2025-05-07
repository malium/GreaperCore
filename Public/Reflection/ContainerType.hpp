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
		static inline constexpr ReflectedTypeID_t ID = RTI_String;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(String);

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

		static std::expected<cJSON*, String> ToJSON_Item(const String& data)
		{
			cJSON* res = cJSON_CreateString(data.c_str());
			if (res != nullptr)
				return res;
			return std::unexpected("[refl::ContainerType<String>::ToJSON_Item] "
				"Couldn't add a string to the object");
		}

		static std::expected<void, String> FromJSON_Item(String& data, cJSON* item)
		{
			if (cJSON_IsString(item))
			{
				data.assign(cJSON_GetStringValue(item));
				return {};	
			}
			return std::unexpected("[refl::ContainerType<String>::FromJSON_Item] "
				"Couldn't obtain the value from json, the item was not String.");
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const String& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
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
		static inline constexpr ReflectedTypeID_t ID = RTI_WString;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(WString);

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

		static std::expected<cJSON*, String> ToJSON_Item(const WString& data)
		{
			cJSON* res = cJSON_CreateString(StringUtils::FromWIDE(data).c_str());
			if (res != nullptr)
				return res;
			return std::unexpected("[refl::ContainerType<WString>::ToJSON_Item] "
				"Couldn't add a string to the object");
		}

		static std::expected<void, String> FromJSON_Item(WString& data, cJSON* item)
		{
			if (cJSON_IsString(item))
			{
				data = StringUtils::ToWIDE(cJSON_GetStringValue(item));
				return {};	
			}
			return std::unexpected("[refl::ContainerType<WString>::FromJSON_Item] "
				"Couldn't obtain the value from json, the item was not String.");
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const WString& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<WString>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, sizet N>
	struct ContainerType<std::array<T, N>> : public BaseType<std::array<T, N>>
	{
		using Type = std::array<T, N>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<array>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = ValueCat::StaticSize * N;
		static inline constexpr ReflectedTypeID_t ID = RTI_Array;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<array>::ToJSON_Item] "
						"Error while adding an item to the array, idx {}.", i));
				++i;
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<array>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the item was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			if (arraySize != N)
				return std::unexpected(std::format("[refl::ContainerType<array>::FromJSON_Item] "                             
					"Couldn't obtain the value from json, the array "
					"have an expected size {} but obtained {}.", N, arraySize));

			for (sizet i = 0; i < N; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<array>::FromJSON_Item] "
						"Couldn't obtain the value from json, the array "
						"returned a null child at index {}.", i));

				auto res = ValueCat::FromJSON_Item(data[i], item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<array>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::list<T>> : public BaseType<std::list<T>>
	{
		using Type = std::list<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<list>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_List;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<list>::ToJSON_Item] "
						"Error while adding an item to the list, idx {}.", i));
				++i;
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<list>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the item was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<list>::FromJSON_Item] "
						"Couldn't obtain the value from json, the list "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<list>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::vector<T>> : public BaseType<std::vector<T>>
	{
		using Type = std::vector<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<vector>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_Vector;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			return std::unexpected(std::format("[refl::ContainerType<vector>::ToStream] "
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
			ReflectedSize_t dynamicSize = 0;

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
			return std::unexpected(std::format("[refl::ContainerType<vector>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			
			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<vector>::ToJSON_Item] "
						"Error while adding an item to the vector, idx {}.", i));
				++i;
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<vector>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the vector was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<vector>::FromJSON_Item] "
						"Couldn't obtain the value from json, the vector "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
			return std::unexpected(std::format("[refl::ContainerType<vector>::GetArrayValue] "
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
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<vector>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::deque<T>> : public BaseType<std::deque<T>>
	{
		using Type = std::deque<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<deque>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_Deque;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();

			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<deque>::ToJSON_Item] "
						"Error while adding an item to the deque, idx {}.", i));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<deque>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the deque was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON_Item] "
						"Couldn't obtain the value from json, the deque "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<deque>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T>
	struct ContainerType<std::set<T>> : public BaseType<std::set<T>>
	{
		using Type = std::set<T>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<set>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_Set;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();

			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<set>::ToJSON_Item] "
						"Error while adding an item to the set, idx {}.", i));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<set>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the set was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON_Item] "
						"Couldn't obtain the value from json, the deque "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<set>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, class C>
	struct ContainerType<std::multiset<T, C>> : public BaseType<std::multiset<T, C>>
	{
		using Type = std::multiset<T, C>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<multiset>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_MultiSet;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();

			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<multiset>::ToJSON_Item] "
						"Error while adding an item to the multiset, idx {}.", i));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<multiset>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the multiset was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON_Item] "
						"Couldn't obtain the value from json, the deque "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<multiset>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, class H, class C>
	struct ContainerType<std::unordered_set<T, H, C>> : public BaseType<std::unordered_set<T, H, C>>
	{
		using Type = std::unordered_set<T, H, C>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_set>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_UnorderedSet;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();

			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<unordered_set>::ToJSON_Item] "
						"Error while adding an item to the unordered_set, idx {}.", i));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<unordered_set>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the unordered_set was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON_Item] "
						"Couldn't obtain the value from json, the deque "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_set>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class T, class H, class C>
	struct ContainerType<std::unordered_multiset<T, H, C>> : public BaseType<std::unordered_multiset<T, H, C>>
	{
		using Type = std::unordered_multiset<T, H, C>;
		using ArrayValueType = typename Type::value_type;
		using ValueCat = typename TypeInfo_t<ArrayValueType>::Type;

		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_multiset>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_UnorderedMultiSet;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

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

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();

			sizet i = 0;
			for (const ArrayValueType& elem : data)
			{
				auto res = ValueCat::ToJSON_Item(elem);
				if (!res.has_value())
					return std::unexpected(res.error());
				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, res.value());
				if (ok == 0)
					return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::ToJSON_Item] "
						"Error while adding an item to the unordered_multiset, idx {}.", i));
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected("[refl::ContainerType<unordered_multiset>::FromJSON_Item] "                               
					"Couldn't obtain the value from json, the unordered_multiset was not an array.");

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			
			for (sizet i = 0; i < arraySize; ++i)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<deque>::FromJSON_Item] "
						"Couldn't obtain the value from json, the deque "
						"returned a null child at index {}.", i));
				ArrayValueType elem;
				auto res = ValueCat::FromJSON_Item(elem, item);
				if (!res.has_value())
					return std::unexpected(res.error());
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "[";
			sizet i = 0;
			for (const ArrayValueType& item : data)
			{
				auto res = ValueCat::ToString(item);
				if (!res.has_value())
					return std::unexpected(res.error());
				output += res.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
			ReflectedSize_t index)
		{
			auto res_arraySize = GetArraySize(data);
			if (!res_arraySize.has_value())
				return std::unexpected(res_arraySize.error());
			auto arraySize = res_arraySize.value();
			if (index < arraySize)
				return &data[index];
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
			{
				data[index] = value;
				return {};
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_multiset>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class P>
	struct ContainerType<std::map<K, V, P>> : public BaseType<std::map<K, V, P>>
	{
		using Type = std::map<K, V, P>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo_t<K>::Type;
		using ValueCat = typename TypeInfo_t<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<map>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<map>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_Map;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(key);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += kres.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(value);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += vres.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<map>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, obj);
				if (ok == 0)
					return std::unexpected("[refl::ContainerType<map>::ToJSON_Item] "
						"Error while adding a key-value item to the map.");
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON_Item] "                               
				"Couldn't obtain the value from json, the map was not an array."));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			sizet i = 0;
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON_Item] "
						"Couldn't obtain the value from json, the map "
						"returned a null child at index {}.", i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
				++i;
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			size_t i = 0;
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() + " : " + vres.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
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
						return &keyvalue;
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
					{
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
					}
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<map>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class P>
	struct ContainerType<std::multimap<K, V, P>> : public BaseType<std::multimap<K, V, P>>
	{
		using Type = std::multimap<K, V, P>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo_t<K>::Type;
		using ValueCat = typename TypeInfo_t<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<multimap>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<multimap>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_MultiMap;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(key);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += kres.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(value);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += vres.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<multimap>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, obj);
				if (ok == 0)
					return std::unexpected("[refl::ContainerType<map>::ToJSON_Item] "
						"Error while adding a key-value item to the map.");
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON_Item] "                               
				"Couldn't obtain the value from json, the map was not an array."));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			sizet i = 0;
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON_Item] "
						"Couldn't obtain the value from json, the map "
						"returned a null child at index {}.", i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
				++i;
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			sizet i = 0;
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() + " : " + vres.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
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
						return &keyvalue;
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
					{
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
					}
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<multimap>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class H, class C>
	struct ContainerType<std::unordered_map<K, V, H, C>> : public BaseType<std::unordered_map<K, V, H, C>>
	{
		using Type = std::unordered_map<K, V, H, C>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo_t<K>::Type;
		using ValueCat = typename TypeInfo_t<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<unordered_map>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_map>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_UnorderedMap;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(key);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += kres.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(value);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += vres.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_map>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, obj);
				if (ok == 0)
					return std::unexpected("[refl::ContainerType<unordered_map>::ToJSON_Item] "
						"Error while adding a key-value item to the map.");
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON_Item] "                               
				"Couldn't obtain the value from json, the map was not an array."));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			sizet i = 0;
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<map>::FromJSON_Item] "
						"Couldn't obtain the value from json, the map "
						"returned a null child at index {}.", i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
				++i;
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			sizet i = 0;
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() + " : " + vres.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
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
						return &keyvalue;
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
					{
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
					}
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_map>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};

	template<class K, class V, class H, class C>
	struct ContainerType<std::unordered_multimap<K, V, H, C>> : public BaseType<std::unordered_multimap<K, V, H, C>>
	{
		using Type = std::unordered_multimap<K, V, H, C>;
		using ArrayValueType = typename Type::value_type;
		using KeyCat = typename TypeInfo_t<K>::Type;
		using ValueCat = typename TypeInfo_t<V>::Type;

		static_assert(!std::is_same_v<KeyCat, void>,
			"[refl::ContainerType<unordered_multimap>] Trying to use a Container with not refl key_value!");
		static_assert(!std::is_same_v<ValueCat, void>,
			"[refl::ContainerType<unordered_multimap>] Trying to use a Container with not refl value_type!");

		static inline constexpr ReflectedSize_t StaticSize = sizeof(sizet);
		static inline constexpr ReflectedTypeID_t ID = RTI_UnorderedMultiMap;
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Container;

		REFL_CREATE_METHODS(Type);

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
			ReflectedSize_t dynamicSize = 0;

			for (decltype(elemCount) i = 0; i < elemCount; ++i)
			{
				K key;
				auto kres = KeyCat::FromStream(key, stream);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto kresDynamicSize = KeyCat::GetDynamicSize(key);
				if (!kresDynamicSize.has_value())
					return std::unexpected(kresDynamicSize.error());
				dynamicSize += KeyCat::StaticSize + kresDynamicSize.value();
				size += kres.value();

				V value;
				auto vres = ValueCat::FromStream(value, stream);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				auto vresDynamicSize = ValueCat::GetDynamicSize(value);
				if (!vresDynamicSize.has_value())
					return std::unexpected(vresDynamicSize.error());
				dynamicSize += ValueCat::StaticSize + vresDynamicSize.value();
				size += vres.value();

				data.emplace(key, value);
			}
			auto expectedSize = dynamicSize + StaticSize;
			if (size == expectedSize)
				return size;
			return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromStream] "
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",
				expectedSize, size));
		}

		static std::expected<cJSON*, String> ToJSON_Item(const Type& data)
		{
			cJSON* arrayObject = cJSON_CreateArray();
			for (const ArrayValueType& elem : data)
			{
				cJSON* obj = cJSON_CreateObject();
				auto kres = KeyCat::ToJSON(elem, obj, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				auto vres = ValueCat::ToJSON(elem, obj, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());

				cJSON_bool ok = cJSON_AddItemToArray(arrayObject, obj);
				if (ok == 0)
					return std::unexpected("[refl::ContainerType<unordered_multimap>::ToJSON_Item] "
						"Error while adding a key-value item to the map.");
			}
			return arrayObject;
		}

		static std::expected<void, String> FromJSON_Item(Type& data, cJSON* arrayObject)
		{
			if (!cJSON_IsArray(arrayObject))
				return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromJSON_Item] "                               
				"Couldn't obtain the value from json, the unordered_multimap was not an array."));

			sizet arraySize = cJSON_GetArraySize(arrayObject);
			
			data.clear();
			sizet i = 0;
			for (ArrayValueType& elem : data)
			{
				cJSON* item = cJSON_GetArrayItem(arrayObject, i);
				if (item == nullptr)
					return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::FromJSON_Item] "
						"Couldn't obtain the value from json, the unordered_multimap "
						"returned a null child at index {}.", i));
				
				K key;
				auto kres = KeyCat::FromJSON(key, item, "key"sv);
				if (!kres.has_value())
					return std::unexpected(kres.error());

				V value;
				auto vres = KeyCat::FromJSON(value, item, "value"sv);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				
				data.emplace(key, value);
				++i;
			}
			return {};
		}

		static std::expected<String, String> ToString(const Type& data)
		{
			String output {};
			output += "{";
			sizet i = 0;
			for (const auto& [key, value] : data)
			{
				auto kres = KeyCat::ToString(key);
				if (!kres.has_value())
					return std::unexpected(kres.error());
				
				auto vres = ValueCat::ToString(value);
				if (!vres.has_value())
					return std::unexpected(vres.error());
				output += kres.value() + " : " + vres.value();
				if (i < (data.size() -1))
					output += ", ";
				++i;
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

		static std::expected<const ArrayValueType*, String> GetArrayValue(const Type& data,
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
						return &keyvalue;
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
					{
						data.erase(keyvalue.first);
						data.emplace(value);
						return {};
					}
				}
			}
			return std::unexpected(std::format("[refl::ContainerType<unordered_multimap>::SetArrayValue] "
				"Index '{}' out of bounds [0,{}]", index, arraySize)); 
		}
	};
}

#endif /* CORE_REFLECTION_CONTAINERTYPE_HPP */