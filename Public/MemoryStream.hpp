/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_MEMORY_STREAM_HPP
#define CORE_MEMORY_STREAM_HPP 1

#include "Base/IStream.hpp"

/***********************************************************************************************************************
 *                                                    DEFINITION                                                       *
 **********************************************************************************************************************/

namespace greaper
{
	class MemoryStream : public IStream
	{
	public:
		MemoryStream()noexcept;

		explicit MemoryStream(sizet capacity);

		MemoryStream(void* memory, sizet size)noexcept;

		MemoryStream(const MemoryStream& other);
		MemoryStream& operator=(const MemoryStream& other);
		MemoryStream(MemoryStream&& other) noexcept;
		MemoryStream& operator=(MemoryStream&& other) noexcept;

		~MemoryStream()noexcept override;

		INLINE bool IsFile()const noexcept override { return false; }

		INLINE uint8* GetData()const noexcept { return m_Data; }

		INLINE uint8* GetCursor()const noexcept { return m_Cursor; }

		ssizet Read(void* buf, ssizet count)const noexcept override;

		ssizet Write(const void* buf, ssizet count) override;

		void Skip(ssizet count)override;

		void Seek(ssizet pos)override;

		INLINE ssizet Tell()const noexcept override { return m_Cursor - m_Data; }

		INLINE bool Eof()const noexcept override { return m_Cursor >= m_End; }

		std::shared_ptr<IStream> Clone(bool copyData = true)const noexcept override;

		void Close()noexcept override;

		uint8* DisownMemory()noexcept;
	
	protected:
		uint8* m_Data;
		mutable uint8* m_Cursor;
		uint8* m_End;
		bool m_OwnsMemory;

		void Realloc(sizet bytes);
	};
}

/***********************************************************************************************************************
 *                                                  IMPLEMENTATION                                                     *
 **********************************************************************************************************************/

namespace greaper
{
	INLINE MemoryStream::MemoryStream() noexcept
		:IStream(READ | WRITE)
		,m_Data(nullptr)
		,m_Cursor(nullptr)
		,m_End(nullptr)
		,m_OwnsMemory(true)
	{

	}

	INLINE MemoryStream::MemoryStream(sizet capacity)
		:IStream(READ | WRITE)
		,m_Data(nullptr)
		,m_Cursor(nullptr)
		,m_End(nullptr)
		,m_OwnsMemory(true)
	{
		Realloc(capacity);
	}

	INLINE MemoryStream::MemoryStream(void *memory, sizet size) noexcept
		:IStream(READ | WRITE)
		,m_Data((uint8*)memory)
		,m_Cursor((uint8*)memory)
		,m_End((uint8*)memory + size)
		,m_OwnsMemory(false)
	{
		m_Size = size;
	}

	INLINE MemoryStream::MemoryStream(const MemoryStream &other)
		:IStream(READ | WRITE)
		,m_Data(nullptr)
		,m_Cursor(nullptr)
		,m_End(nullptr)
		,m_OwnsMemory(other.m_OwnsMemory)
	{
		m_Name = other.m_Name;
		m_Access = other.m_Access;
		if (m_OwnsMemory)
		{
			Realloc(other.m_Size);
			if(m_Size > 0)
				memcpy(m_Data, other.m_Data, m_Size);
		}
		else
		{
			m_Size = other.m_Size;
			m_Data = other.m_Data;
			m_Cursor = other.m_Cursor;
			m_End = other.m_End;
		}
	}
	
	INLINE MemoryStream &MemoryStream::operator=(const MemoryStream &other)
	{
		if (this != &other)
		{
			m_Name = other.m_Name;
			m_Access = other.m_Access;
			if (m_OwnsMemory && m_Data != nullptr)
				PlatformDealloc(m_Data);
			
			m_OwnsMemory = other.m_OwnsMemory;
			if (m_OwnsMemory)
			{
				Realloc(other.m_Size);
				if(m_Size > 0)
					memcpy(m_Data, other.m_Data, m_Size);
			}
			else
			{
				m_Size = other.m_Size;
				m_Data = other.m_Data;
				m_Cursor = other.m_Cursor;
				m_End = other.m_End;
			}
		}
		return *this;
	}
	
	INLINE MemoryStream::MemoryStream(MemoryStream &&other) noexcept
		:IStream(READ | WRITE)
		,m_Data(std::exchange(other.m_Data, nullptr))
		,m_Cursor(std::exchange(other.m_Cursor, nullptr))
		,m_End(std::exchange(other.m_End, nullptr))
		,m_OwnsMemory(std::exchange(other.m_OwnsMemory, false))
	{
		m_Size = std::exchange(other.m_Size, (decltype(m_Size))0);
		m_Name = std::exchange(other.m_Name, "Invalid");
		m_Access = std::exchange(other.m_Access, (decltype(m_Access))0);
	}

	INLINE MemoryStream &MemoryStream::operator=(MemoryStream &&other) noexcept
	{
		if (this != &other)
		{
			if (m_OwnsMemory && m_Data != nullptr)
				PlatformDealloc(m_Data);

			m_Name = std::exchange(other.m_Name, "Invalid");
			m_Size = std::exchange(other.m_Size, (decltype(m_Size))0);
			m_Access = std::exchange(other.m_Access, (decltype(m_Access))0);
			m_Data = std::exchange(other.m_Data, nullptr);
			m_Cursor = std::exchange(other.m_Cursor, nullptr);
			m_End = std::exchange(other.m_End, nullptr);
			m_OwnsMemory = std::exchange(other.m_OwnsMemory, false);
		}
		return *this;
	}

	INLINE MemoryStream::~MemoryStream() noexcept
	{
		Close();
	}

	INLINE ssizet MemoryStream::Read(void *buf, ssizet count) const noexcept
	{
		if(!IsReadable() || count <= 0)
			return 0;
		
		if ((m_Cursor + count) > m_End)
			count = m_End - m_Cursor;
		
		if (count <= 0)
			return 0;

		memcpy(buf, m_Cursor, count);
		m_Cursor += count;

		return count;
	}

	INLINE ssizet MemoryStream::Write(const void *buf, ssizet count)
	{
		if (!IsWritable() || count <= 0)
			return 0;

		const auto currentSize = (m_Cursor - m_Data);
		const auto newSize = currentSize + count;
		if (newSize > m_Size)
		{
			if (m_OwnsMemory)
				Realloc(newSize);
			else
				count = m_Size - currentSize;
		}

		if (count <= 0)
			return 0;

		memcpy(m_Cursor, buf, count);
		m_Cursor += count;
		m_End = Max(m_Cursor, m_End);
		return count;
	}

	INLINE void MemoryStream::Skip(ssizet count) 
	{
		VerifyLessEqual(m_Cursor + count, m_End, "Trying to skip a MemoryStream outside of its bounds.");
		m_Cursor = Min(m_Cursor + count, m_End);
	}

	INLINE void MemoryStream::Seek(ssizet pos)
	{
		VerifyLessEqual(m_Data + pos, m_End, "Trying to seek a MemoryStream outside of its bounds.");
		m_Cursor = Min(m_Data + pos, m_End);
	}

	INLINE std::shared_ptr<IStream> MemoryStream::Clone(bool copyData) const noexcept
	{
		if (!copyData)
			return std::make_shared<MemoryStream>(m_Data, m_Size);
		return std::make_shared<MemoryStream>(*this);
	}

	INLINE void MemoryStream::Close() noexcept
	{
		if (m_Data != nullptr && m_OwnsMemory)
			PlatformDealloc(m_Data);
		m_Data = m_End = m_Cursor = nullptr;
		m_Size = 0;
	}

	INLINE uint8 *MemoryStream::DisownMemory() noexcept
	{
		m_OwnsMemory = false;
		return m_Data;
	}

	INLINE void MemoryStream::Realloc(sizet bytes) 
	{
		if ((ssizet)bytes == m_Size)
			return;

		VerifyGreater((ssizet)bytes, m_Size, "Realloc should always increase the size of the MemoryStream.");

		auto* buffer = (uint8*)PlatformAlloc(bytes);
		if (m_Data != nullptr)
		{
			m_Cursor = buffer + (m_Cursor - m_Data);
			m_End = buffer + (m_End - m_Data);

			memcpy(buffer, m_Data, m_Size);
			PlatformDealloc(m_Data);
		}
		else
		{
			m_Cursor = buffer;
			m_End = buffer;
		}

		m_Data = buffer;
		m_Size = (ssizet)bytes;
	}
}

#endif /* CORE_MEMORY_STREAM_HPP */