/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#include "../CorePrerequisites.hpp"

namespace greaper
{
	class IStream
	{
		public:
		enum AccessMode
		{
			READ = 1,
			WRITE
		};

	protected:
		static constexpr uint32 StreamTempSize = 128;
		String m_Name;
		ssizet m_Size;
		uint16 m_Access;

	public:
		explicit IStream(uint16 accessMode = READ)noexcept;
		explicit IStream(StringView name, uint16 accessMode = READ)noexcept;

		virtual ~IStream()noexcept = default;

		NODISCARD const String& GetName()const noexcept { return m_Name; }

		NODISCARD uint16 GetAccessMode()const noexcept { return m_Access; }

		NODISCARD virtual bool IsReadable()const noexcept { return (m_Access & READ) != 0; }

		NODISCARD virtual bool IsWritable()const noexcept { return (m_Access & WRITE) != 0; }

		NODISCARD virtual bool IsFile()const noexcept = 0;

		template<typename T>
		const IStream& operator>>(T& val)const noexcept;

		template<typename T>
		IStream& operator>>(T& val)noexcept;

		template<typename T>
		IStream& operator<<(const T& val)noexcept;

		virtual ssizet Read(void* buff, ssizet count)const noexcept = 0;
		
		virtual ssizet Write(const void* buff, ssizet count)noexcept = 0;
		
		virtual void Skip(ssizet count)noexcept = 0;

		virtual void Seek(ssizet pos)noexcept = 0;

		NODISCARD virtual ssizet Tell()const noexcept = 0;

		virtual void Align(uint32 count = 1)noexcept;

		NODISCARD virtual bool Eof()const noexcept = 0;

		NODISCARD ssizet Size()const noexcept { return m_Size; }

		NODISCARD virtual IStream Clone(bool copyData = true)const noexcept = 0;

		virtual void Close()noexcept = 0;
	};



	template<typename T>
	INLINE const IStream& IStream::operator>>(T& val)const noexcept
	{
		const auto read = Read((void*)&val, sizeof(val));
		VerifyEqual(read, sizeof(val), std::format("Couldn't read the whole value from the stream, Size:{} Read:{}.",  \
			sizeof(val), read))
		return *this;
	}

	template<typename T>
	INLINE IStream& IStream::operator>>(T& val)noexcept
	{
		const auto read = Read((void*)&val, sizeof(val));
		VerifyEqual(read, sizeof(val), std::format("Couldn't read the whole value from the stream, Size:{} Read:{}.",  \
			sizeof(val), read));
		return *this;
	}

	template<typename T>
	INLINE IStream& IStream::operator<<(const T& val)noexcept
	{
		const auto written = Write(&val, sizeof(val));
		VerifyEqual(written, sizeof(val),                                                                              \
			std::format("Couldn't write the whole value to the stream, Size:{} Written:{}.", sizeof(val), written));
		return *this;
	}

	INLINE IStream::IStream(const uint16 accessMode)noexcept
		:m_Size(0)
		,m_Access(accessMode)
	{

	}

	INLINE IStream::IStream(StringView name, const uint16 accessMode)noexcept
		:m_Name(name)
		,m_Size(0)
		,m_Access(accessMode)
	{

	}

	INLINE void IStream::Align(uint32 count)noexcept
	{
		if (count <= 1)
			return;

		const auto alignOffset = (count - (Tell() & (count - 1))) & (count - 1);
		Skip(alignOffset);
	}
}