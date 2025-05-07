/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_I_FIELD_HPP
#define CORE_REFLECTION_I_FIELD_HPP 1

#include "PlainType.hpp"
#include <functional>

namespace greaper::refl
{
	class IField
	{
	public:
		using GetValueFn = std::function<const void* (const void*)>;
		using SetValueFn = std::function<void(void*, const void*)>;

		IField(StringView fieldName = "unnamed"sv, GetValueFn getValueFn = nullptr,
				SetValueFn setValueFn = nullptr)noexcept;

		virtual std::expected<ReflectedSize_t, String> ToStream(const void* complexPtr, IStream& stream)const = 0;
		virtual std::expected<ReflectedSize_t, String> FromStream(void* complexPtr, IStream& stream)const = 0;

		std::expected<std::shared_ptr<cJSON>, String> CreateJSON(const void* complexPtr)const;
		std::expected<cJSON*, String>  ToJSON(const void* complexPtr, cJSON* json)const;
		virtual std::expected<cJSON*, String>  ToJSON_Item(const void* complexPtr)const = 0;
		std::expected<void, String> FromJSON(void* complexPtr, cJSON* json, bool caseSensitive = false)const;
		virtual std::expected<void, String> FromJSON_Item(void* complexPtr, cJSON* json)const = 0;

		virtual std::expected<String, String> ToString(const void* complexPtr)const = 0;

		virtual std::expected<ReflectedSize_t, String> GetDynamicSize(const void* complexPtr)const = 0;
		virtual std::expected<ReflectedSize_t, String> GetStaticSize()const = 0;

		virtual std::expected<ReflectedSize_t, String> GetArraySize(const void* complexPtr)const = 0;
		virtual std::expected<void, String> SetArraySize(void* complexPtr, sizet size)const = 0;

		virtual std::expected<const void*, String> GetArrayValue(const void* complexPtr, sizet index)const = 0;
		virtual std::expected<void, String> SetArrayValue(void* complexPtr, const void* value, sizet index)const = 0;
		
		std::expected<const void*, String> GetValue(const void* complexPtr)const noexcept;

		std::expected<void, String> SetValue(void* complexPtr, const void* value)const noexcept;

		virtual bool IsArray()const noexcept = 0;
		virtual ReflectedTypeID_t GetTypeID()const noexcept = 0;
		INLINE constexpr StringView GetFieldName()const noexcept { return m_FieldName; }

	protected:
		StringView m_FieldName;
		GetValueFn m_GetValueFn = nullptr;
		SetValueFn m_SetValueFn = nullptr;
	};
	
	template<class T>
	class TField final : public IField
	{
		public:
		using Type = std::decay_t<T>;
		using tInfo = TypeInfo<Type>;
		using ArrayValueType = typename tInfo::Type::ArrayValueType;
		
		static_assert(!std::is_same_v<typename tInfo::Type, void>,
			"[refl::TField<T>] instantiated with an Unknown TypeID.");
			
		TField(StringView fieldName, GetValueFn getValueFn, SetValueFn setValueFn)noexcept;
		
		std::expected<ReflectedSize_t, String> ToStream(const void* complexPtr, IStream& stream)const override;
		std::expected<ReflectedSize_t, String> FromStream(void* complexPtr, IStream& stream)const override;
		
		std::expected<cJSON*, String> ToJSON_Item(const void* complexPtr)const override;
		std::expected<void, String> FromJSON_Item(void* complexPtr, cJSON* json)const override;
		
		std::expected<String, String> ToString(const void* complexPtr)const override;
		
		std::expected<ReflectedSize_t, String> GetDynamicSize(const void* complexPtr)const override;
		std::expected<ReflectedSize_t, String> GetStaticSize()const override;
		
		std::expected<ReflectedSize_t, String> GetArraySize(const void* complexPtr)const override;
		std::expected<void, String> SetArraySize(void* complexPtr, sizet size)const override;

		std::expected<const void*, String> GetArrayValue(const void* complexPtr, sizet index)const override;
		std::expected<void, String> SetArrayValue(void* complexPtr, const void* value, sizet index)const override;
		
		bool IsArray()const noexcept override;
		ReflectedTypeID_t GetTypeID()const noexcept override;
	};
	
	INLINE IField::IField(StringView fieldName, IField::GetValueFn getValueFn, IField::SetValueFn setValueFn) noexcept
		:m_FieldName(std::move(fieldName))
		,m_GetValueFn(std::move(getValueFn))
		,m_SetValueFn(std::move(setValueFn))
	{

	}

	INLINE std::expected<std::shared_ptr<cJSON>, String> IField::CreateJSON(const void* complexPtr)const
	{
		cJSON* json = cJSON_CreateObject();
		auto res = ToJSON(complexPtr, json);
		if (res.has_value())
			return std::shared_ptr<cJSON>(json, cJSON_Delete);
		return std::unexpected(res.error());
	}

	INLINE std::expected<cJSON*, String> IField::ToJSON(const void* complexPtr, cJSON* json) const
	{
		auto item_res = ToJSON_Item(complexPtr);
		if (!item_res.has_value())
			return std::unexpected(std::format("{}, item name '{}'", item_res.error(), name));
		if (item_res.value() == nullptr)
			return std::unexpected(std::format("Couldn't convert to JSON the complex field '{}'.", m_FieldName));
		auto ok = cJSON_AddItemToObject(json, m_FieldName.data(), item_res.value());
		if (ok == 0)
			return std::unexpected(std::format("Couldn't attach item to JSON object, item name '{}'.", m_FieldName));
		return item_res.value();
	}

	INLINE std::expected<void, String> IField::FromJSON(void* complexPtr, cJSON* json, bool caseSensitive) const
	{
		cJSON* item = nullptr;
		if (!caseSensitive)
			item = cJSON_GetObjectItemCaseSensitive(json, m_FieldName.data());
		else
			item = cJSON_GetObjectItem(json, m_FieldName.data());
		if (item == nullptr)
			return std::unexpected(std::format("Couldn't obtain the value from json, the item with name '{}' "
				"was not found.", m_FieldName));
		auto res = FromJSON_Item(complexPtr, item);
		if (res.has_value())
			return {};
		return std::unexpected(std::format("{}, item name '{}'", m_FieldName));
	}

	INLINE std::expected<const void*, String> IField::GetValue(const void *complexPtr) const noexcept
	{
		if (m_GetValueFn != nullptr)
		{
			return m_GetValueFn(complexPtr);
		}
		return std::unexpected(std::format("Couldn't retrieve the value from the complex field '{}',"
			"null get value function.", m_FieldName));
	}

	INLINE std::expected<void, String> IField::SetValue(void *complexPtr, const void *value) const noexcept
	{
		if (m_SetValueFn != nullptr)
		{
			m_SetValueFn(complexPtr, value);
			return {};
		}
		return std::unexpected(std::format("Couldn't set the value of the complex field '{}',"
			"null set value function.", m_FieldName));
	}

	template <class T>
	TField<T>::TField(StringView fieldName, GetValueFn getValueFn, SetValueFn setValueFn) noexcept
		:IField(fieldName, getValueFn, setValueFn)
	{

	}

	template <class T>
	std::expected<ReflectedSize_t, String> TField<T>::ToStream(const void *complexPtr, IStream &stream) const
	{
		auto res = GetValue(complexPtr);
		if (!res.has_value())
			return std::unexpected(res.error());
		
		return tInfo::Type::ToStream(*(const T*)res.value(), stream);
	}

	template <class T>
	std::expected<ReflectedSize_t, String> TField<T>::FromStream(void *complexPtr, IStream &stream) const
	{
		Type temp;
		auto res = tInfo::Type::FromStream(temp, stream);
		if (!res.has_value())
			return std::unexpected(res.error());
		auto sres = SetValue(complexPtr, &temp);
		if (!sres.has_value())
			return std::unexpected(sres.error());
		return res.value();
	}

	template <class T>
	std::expected<cJSON*, String> TField<T>::ToJSON_Item(const void *complexPtr) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::ToJSON_Item(*(const T*)gres.value());
	}

	template <class T>
	std::expected<void, String> TField<T>::FromJSON_Item(void *complexPtr, cJSON *json) const
	{
		Type temp;
		auto res = tInfo::Type::FromJSON_Item(temp, json);
		if (!res.has_value())
			return std::unexpected(res.error());
		auto sres = SetValue(complexPtr, &temp);
		if (!sres.has_value())
			return std::unexpected(sres.error());
		return {};
	}

	template <class T>
	std::expected<String, String> TField<T>::ToString(const void *complexPtr) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::ToString(*(const T*)gres.value());
	}

	template <class T>
	std::expected<ReflectedSize_t, String> TField<T>::GetDynamicSize(const void *complexPtr) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::GetDynamicSize(*(const T*)gres.value());
	}

	template <class T>
	std::expected<ReflectedSize_t, String> TField<T>::GetStaticSize() const
	{
		return tInfo::Type::StaticSize;
	}

	template <class T>
	std::expected<ReflectedSize_t, String> TField<T>::GetArraySize(const void *complexPtr) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::GetArraySize(*(const T*)gres.value());
	}

	template <class T>
	std::expected<void, String> TField<T>::SetArraySize(void *complexPtr, sizet size) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::SetArraySize(*(T*)gres.value(), size);
	}

	template <class T>
	std::expected<const void *, String> TField<T>::GetArrayValue(const void *complexPtr, sizet index) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::GetArrayValue(*(const T*)gres.value(), index);
	}
	
	template <class T>
	std::expected<void, String> TField<T>::SetArrayValue(void *complexPtr, const void *value, sizet index) const
	{
		auto gres = GetValue(complexPtr);
		if (!gres.has_value())
			return std::unexpected(gres.error());
		return tInfo::Type::SetArrayValue(*(T*)gres.value(), *((const ArrayValueType*)value), index);
	}

	template <class T>
	bool TField<T>::IsArray() const noexcept
	{
		return std::is_same_v<typename tInfo::Type, ContainerType<Type>>;
	}

	template <class T>
	ReflectedTypeID_t TField<T>::GetTypeID() const noexcept
	{
		return tInfo::ID;
	}
}

#endif /* CORE_REFLECTION_I_FIELD_HPP */