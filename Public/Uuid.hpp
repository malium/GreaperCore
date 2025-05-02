/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_UUID_HPP
#define CORE_UUID_HPP 1

#include "CorePrerequisites.hpp"
#if PLT_LINUX
#include <uuid/uuid.h>
#endif
#include <exception>
#include "Reflection/BaseType.hpp"

/***********************************************************************************************************************
 *                                                    DEFINITION                                                       *
 **********************************************************************************************************************/

namespace greaper
{
	/**
	 * @brief Is a cross-platform universally unique identifier struct
	 * 
	 * Instead of the typical 8-4-4-4-12 representation it uses 8-8-8-8 representation,
	 * it is used across all interfaces, libraries and resources.
	 * In order to convert from 8-4-4-4-12 to 8-8-8-8:
	 * ED4FE4FA-0800-416F-ABDA-E666DACE6688
	 * ED4FE4FA-0800416F-ABDAE666-DACE6688
	 * There's a code example on greaper::Uuid::GenerateRandom()
	 */
	class Uuid
	{
		uint32 m_Data[4]{ 0, 0, 0, 0 };

	public:
		INLINE constexpr Uuid() noexcept = default;
		INLINE constexpr Uuid(uint32 data0, uint32 data1, uint32 data2, uint32 data3) noexcept;
		INLINE constexpr explicit Uuid(const StringView& view) noexcept;
		INLINE constexpr Uuid(const Uuid& other) noexcept = default;
		INLINE constexpr Uuid(Uuid&& other) noexcept = default;
		INLINE Uuid& operator=(const Uuid& other) noexcept = default;
		INLINE Uuid& operator=(Uuid&& other) noexcept = default;
		~Uuid()noexcept = default;

		Uuid& operator=(const StringView& view) noexcept;
		Uuid& operator=(const String& str) noexcept;

		NODISCARD String ToString()const noexcept;
		void FromString(const String& str) noexcept;

		/**
		 * @brief Requests to the OS a random Uuid
		 * 
		 * @return Uuid The new random Uuid 
		 */
		NODISCARD static Uuid GenerateRandom();

		constexpr bool IsEmpty()const noexcept;
		constexpr const uint32* GetData()const noexcept;
		
		static constexpr Uuid Empty()noexcept;

		friend constexpr bool operator==(const Uuid& left, const Uuid& right)noexcept;
		friend constexpr bool operator<(const Uuid& left, const Uuid& right)noexcept;
		
		friend struct std::hash<greaper::Uuid>;
	};
}

/***********************************************************************************************************************
 *                                                  IMPLEMENTATION                                                     *
 **********************************************************************************************************************/


namespace greaper
{
	namespace Impl
	{
		constexpr achar HEX_TO_LITERAL[16] =
		{
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
		};
		constexpr uint8 LITERAL_TO_HEX[256] =
		{
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			// 0 through 9 translate to 0  though 9
			0x00,  0x01,  0x02,  0x03,  0x04,  0x05,  0x06,  0x07,  0x08,  0x09,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			// A through F translate to 10 though 15
			0xFF,  0x0A,  0x0B,  0x0C,  0x0D,  0x0E,  0x0F,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			// a through f translate to 10 though 15
			0xFF,  0x0A,  0x0B,  0x0C,  0x0D,  0x0E,  0x0F,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,
			0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF
		};

		INLINE constexpr void ViewToUUID(const StringView& view, uint32 data[4]) noexcept
		{
			std::cout << view.size() << std::endl;
			if (view.size() < (8 * 4 + 3))
				return;

			uint32 idx = 0;

			for (int32 i = 7; i >= 0; --i)
			{
				const auto charVal = view[idx++];
				const auto hexVal = (uint32)LITERAL_TO_HEX[static_cast<sizet>(charVal)];
				data[0] |= hexVal << (i * 4);
			}

			++idx;

			for (int32 i = 7; i >= 0; --i)
			{
				const auto charVal = view[idx++];
				const auto hexVal = (uint32)LITERAL_TO_HEX[static_cast<sizet>(charVal)];
				data[1] |= hexVal << (i * 4);
			}

			++idx;

			for (int32 i = 7; i >= 0; --i)
			{
				const auto charVal = view[idx++];
				const auto hexVal = (uint32)LITERAL_TO_HEX[static_cast<sizet>(charVal)];
				data[2] |= hexVal << (i * 4);
			}

			++idx;


			for (int32 i = 7; i >= 0; --i)
			{
				const auto charVal = view[idx++];
				const auto hexVal = (uint32)LITERAL_TO_HEX[static_cast<sizet>(charVal)];
				data[3] |= hexVal << (i * 4);
			}
		}

		INLINE void UUIDToString(const uint32 data[4], String& uuid) noexcept
		{
			uint8 output[36] = {};
			uint32 idx = 0;

			for (int32 i = 7; i >= 0; --i)
			{
				const auto hexVal = (data[0] >> (i * 4)) & 0xF;
				output[idx++] = HEX_TO_LITERAL[hexVal];
			}

			output[idx++] = '-';

			for (int32 i = 7; i >= 0; --i)
			{
				const auto hexVal = (data[1] >> (i * 4)) & 0xF;
				output[idx++] = HEX_TO_LITERAL[hexVal];
			}

			output[idx++] = '-';

			for (int32 i = 7; i >= 0; --i)
			{
				const auto hexVal = (data[2] >> (i * 4)) & 0xF;
				output[idx++] = HEX_TO_LITERAL[hexVal];
			}

			output[idx++] = '-';

			for (int32 i = 7; i >= 0; --i)
			{
				const auto hexVal = (data[3] >> (i * 4)) & 0xF;
				output[idx++] = HEX_TO_LITERAL[hexVal];
			}
			uuid.assign(reinterpret_cast<const achar*>(output), 36);
		}
	}

	INLINE constexpr Uuid::Uuid(const uint32 data0, const uint32 data1, const uint32 data2, const uint32 data3) noexcept
		:m_Data{ data0, data1, data2, data3 }
	{

	}

	INLINE constexpr Uuid::Uuid(const StringView& view) noexcept
		:m_Data{ 0, 0, 0, 0 }
	{
		Impl::ViewToUUID(view, m_Data);
	}

	INLINE Uuid& Uuid::operator=(const StringView& view) noexcept
	{
		Impl::ViewToUUID(view, m_Data);
		return *this;
	}
	INLINE Uuid& Uuid::operator=(const String& str) noexcept
	{
		Impl::ViewToUUID(str, m_Data);
		return *this;
	}

	NODISCARD inline String Uuid::ToString()const noexcept
	{
		String uuid;
		Impl::UUIDToString(m_Data, uuid);
		return uuid;
	}

	INLINE void Uuid::FromString(const String& str) noexcept
	{
		Impl::ViewToUUID(StringView{str.data(), str.size()}, m_Data);
	}

	INLINE Uuid Uuid::GenerateRandom()
	{
#if PLT_WINDOWS
		UUID uuid;
		UuidCreate(&uuid);
		const auto data0 = uuid.Data1;
		const auto data1 = uuid.Data2 | (uuid.Data3 << 16);
		const auto data2 = uuid.Data3 | (uuid.Data4[0] << 16) | (uuid.Data4[1] << 24);
		const auto data3 = uuid.Data4[2] | (uuid.Data4[3] << 8) | (uuid.Data4[4] << 16) | (uuid.Data4[5] << 24);
		return Uuid(data0, data1, data2, data3);
#elif PLT_LINUX
		uuid_t nativeUUID;
		uuid_generate(nativeUUID);

		return Uuid(
			*(uint32*)&nativeUUID[0],
			*(uint32*)&nativeUUID[4],
			*(uint32*)&nativeUUID[8],
			*(uint32*)&nativeUUID[12]);
#endif
		throw std::runtime_error("Unhandled platform!! Not Windows nor Linux");
	}

	INLINE constexpr bool Uuid::IsEmpty()const noexcept
	{
		return m_Data[0] == 0 && m_Data[1] == 0 && m_Data[2] == 0 && m_Data[3] == 0;
	}

	INLINE constexpr const uint32* Uuid::GetData() const noexcept
	{
		return &(m_Data[0]);
	}

	INLINE constexpr Uuid Uuid::Empty()noexcept
	{
		return Uuid{};
	}

	INLINE constexpr bool operator!=(const Uuid& left, const Uuid& right)noexcept
	{
		return !(left == right);
	}

	INLINE constexpr bool operator>(const Uuid& left, const Uuid& right)noexcept
	{
		return right < left;
	}

	INLINE constexpr bool operator<=(const Uuid& left, const Uuid& right)noexcept
	{
		return !(left > right);
	}

	INLINE constexpr bool operator>=(const Uuid& left, const Uuid& right)noexcept
	{
		return !(left < right);
	}

	INLINE constexpr bool operator==(const Uuid& left, const Uuid& right)noexcept
	{
		return left.m_Data[0] == right.m_Data[0] && left.m_Data[1] == right.m_Data[1]
			&& left.m_Data[2] == right.m_Data[2] && left.m_Data[3] == right.m_Data[3];
	}

	INLINE constexpr bool operator<(const Uuid& left, const Uuid& right)noexcept
	{
		if (left.m_Data[0] < right.m_Data[0])
			return true;
		else if (left.m_Data[0] > right.m_Data[0])
			return false;

		if (left.m_Data[1] < right.m_Data[1])
			return true;
		else if (left.m_Data[1] > right.m_Data[1])
			return false;

		if (left.m_Data[2] < right.m_Data[2])
			return true;
		else if (left.m_Data[2] > right.m_Data[2])
			return false;

		if (left.m_Data[3] < right.m_Data[3])
			return true;
		else if (left.m_Data[3] > right.m_Data[3])
			return false;

		return false; // Equal
	}
}

namespace std
{
	template<>
	struct hash<greaper::Uuid>
	{
		size_t operator()(const greaper::Uuid& val)const noexcept
		{
			return ComputeHash(val.m_Data[0], val.m_Data[1], val.m_Data[2], val.m_Data[3]);
		}
	};
}

namespace greaper::refl
{
	template<>
	struct PlainType<Uuid> : public BaseType<Uuid>
	{
		static inline constexpr ReflectedTypeID_t ID = RTI_UUID;
		static inline constexpr ReflectedSize_t StaticSize = sizeof(Uuid);
		static inline constexpr TypeCategory_t Category = TypeCategory_t::Plain;
		REFL_CREATE_METHODS(Uuid);
		static std::expected<ReflectedSize_t, String> ToStream(const Uuid& data, IStream& stream)
		{                      
			const auto size = stream.Write(&data, sizeof(data));                                                        
			if (size == sizeof(data))                                                                                   
				return size;                                                                                            
			return std::unexpected(std::format("[refl::PlainType<Uuid>::ToStream] "                                  
				"Failure while writing to stream, not all data was written, expected:{} obtained:{}.",                  
				sizeof(data), size));
		}                                                                                  
		static std::expected<ReflectedSize_t, String> FromStream(Uuid& data, IStream& stream)
		{                          
			const auto size = stream.Read(&data, sizeof(data));                                                         
			if (size == sizeof(data))                                                                                   
				return size;                                                                                            
			return std::unexpected(std::format("[refl::PlainType<Uuid>::FromStream] "                                
				"Failure while reading from stream, not all data was read, expected:{} obtained:{}.",                   
				sizeof(data), size));
		}                                                                                  
		static std::expected<cJSON*, String> ToJSON(const Uuid& data, cJSON* json, StringView name)
		{
			return cJSON_AddStringToObject(json, name.data(), data.ToString().c_str());
		}                                                                        
		static std::expected<void, String> FromJSON(Uuid& data, cJSON* json, StringView name)
		{                          
			cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.data());             
			if (item == nullptr)                                                                                        
				return std::unexpected(std::format("[refl::PlainType<Uuid>::FromJSON] "                              
				"Couldn't obtain the value from json, the item with name '{}' was not found.", name));                  
			if (cJSON_IsString(item))
			{          
				data.FromString(cJSON_GetStringValue(item));
				return {};
			}                                                                                             
			return std::unexpected(std::format("[refl::PlainType<Uuid>::FromJSON] "                                  
				"Couldn't obtain the value from json, the item with name '{}' was not cJSON_IsString.", name));
		}           
		static std::expected<String, String> ToString(const Uuid& data)
		{
			return data.ToString();
		}                                                                            
		static std::expected<ReflectedSize_t, String> GetDynamicSize(UNUSED const Uuid& data)
		{                          
			return 0ll;
		}                                                                                                
		static std::expected<ReflectedSize_t, String> GetArraySize(UNUSED const Uuid& data)
		{                            
			return std::unexpected("Function 'PlainType<Uuid>::GetArraySize' Trying to use a PlainType as array!");
		} 
		static std::expected<void, String> SetArraySize(UNUSED Uuid& data, UNUSED ReflectedSize_t size)
		{                
			return std::unexpected("Function 'PlainType<Uuid>::SetArraySize' Trying to use a PlainType as array!");
		} 
		static std::expected<const ArrayValueType*, String> GetArrayValue(UNUSED const Uuid& data,                      
			UNUSED ReflectedSize_t index)
		{                                                                              
			return std::unexpected("Function 'PlainType<Uuid>::GetArrayValue' Trying to use a PlainType as array!");
		}
		static std::expected<void, String> SetArrayValue(UNUSED Uuid& data, UNUSED const ArrayValueType& value,         
			UNUSED ReflectedSize_t index)
		{                                                                              
			return std::unexpected("Function 'PlainType<Uuid>::SetArrayValue' Trying to use a PlainType as array!");
		}
	};
}

#endif /* CORE_UUID_HPP */