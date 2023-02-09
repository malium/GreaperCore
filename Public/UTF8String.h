/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#ifndef CORE_UTF8_STRING_H
#define CORE_UTF8_STRING_H 1

#include "CorePrerequisites.h"
#include "../../utf8.h/utf8.h"

namespace greaper
{
	class U8StringIterator
	{
	public:
		using value_type = utf8_int8_t;
		using code_point = utf8_int32_t;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = utf8_int8_t*;
		using const_pointer = const utf8_int8_t*;
		using const_reference = const utf8_int8_t&;

		U8StringIterator(const_pointer ptr, const_pointer containerPtr);
		code_point operator*()const noexcept;
		U8StringIterator& operator++()noexcept;
		U8StringIterator operator++(int)const noexcept;
		U8StringIterator& operator--()noexcept;
		U8StringIterator operator--(int)const noexcept;
		U8StringIterator& operator+=(difference_type n)noexcept;
		U8StringIterator operator+(difference_type n)const noexcept;
		U8StringIterator& operator-=(difference_type n)noexcept;
		U8StringIterator operator-(difference_type n)const noexcept;

		friend bool operator==(const U8StringIterator& left, const U8StringIterator& right)noexcept;
		friend bool operator<(const U8StringIterator& left, const U8StringIterator& right)noexcept;

		const_pointer GetContainer()const noexcept;
	private:
		const_pointer m_Ptr;
		const_pointer m_ContainerPtr;
	};

	class U8StringReverseIterator
	{
	public:
		using value_type = utf8_int8_t;
		using code_point = utf8_int32_t;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = utf8_int8_t*;
		using const_pointer = const utf8_int8_t*;
		using const_reference = const utf8_int8_t&;

		U8StringReverseIterator(const_pointer ptr, const_pointer containerPtr);
		code_point operator*()const noexcept;
		U8StringReverseIterator& operator++()noexcept;
		U8StringReverseIterator operator++(int)const noexcept;
		U8StringReverseIterator& operator--()noexcept;
		U8StringReverseIterator operator--(int)const noexcept;
		U8StringReverseIterator& operator+=(difference_type n)noexcept;
		U8StringReverseIterator operator+(difference_type n)const noexcept;
		U8StringReverseIterator& operator-=(difference_type n)noexcept;
		U8StringReverseIterator operator-(difference_type n)const noexcept;

		friend bool operator==(const U8StringReverseIterator& left, const U8StringReverseIterator& right)noexcept;
		friend bool operator<(const U8StringReverseIterator& left, const U8StringReverseIterator& right)noexcept;

		const_pointer GetContainer()const noexcept;
	private:
		const_pointer m_Ptr;
		const_pointer m_ContainerPtr;
	};

	template<class _Alloc_ = StdAlloc<utf8_int8_t, GenericAllocator>>
	class U8String
	{
	public:
		using allocator_type = _Alloc_;
		using value_type = utf8_int8_t;
		using code_point = utf8_int32_t;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using pointer = utf8_int8_t*;
		using const_pointer = const utf8_int8_t*;
		using refernce = utf8_int8_t&;
		using const_reference = const utf8_int8_t&;

		U8String();
		U8String(const U8String& other);
		U8String(U8String&& other)noexcept;
		explicit U8String(value_type* s);
		U8String(std::initializer_list<code_point> list);
		U8String(size_type n, code_point codepoint);
		U8String(pointer s, size_type n);
		U8String(const U8String& s, size_type pos, size_type n);
		U8String(const U8String& s, size_type pos);
		U8String(U8StringIterator begin, U8StringIterator end);

		U8String& operator=(const U8String&) = delete;
		U8String& operator=(U8String&& other)noexcept;

		code_point operator[](size_type idx)const noexcept;
		~U8String();

		U8StringIterator begin()const noexcept;
		U8StringIterator end()const noexcept;
		
		U8StringReverseIterator rbegin()const noexcept;
		U8StringReverseIterator rend()const noexcept;

		U8StringIterator cbegin()const noexcept;
		U8StringIterator cend()const noexcept;

		U8StringReverseIterator crbegin()const noexcept;
		U8StringReverseIterator crend()const noexcept;

		U8String append(std::initializer_list<code_point> list)const noexcept;

	private:
		pointer m_Value;
	};
}

#endif /* CORE_UTF8_STRING_H */