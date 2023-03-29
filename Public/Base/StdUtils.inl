/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

namespace std
{
	template<>
	struct hash<greaper::String>
	{
		NODISCARD INLINE size_t operator()(const greaper::String& str)const noexcept
		{
#if COMPILER_MSVC
			return std::_Hash_array_representation(str.data(), str.size());
#else
			return std::_Hash_bytes(str.data(), str.size(), 0);
#endif
		}
	};

	template<>
	struct hash<greaper::WString>
	{
		NODISCARD INLINE size_t operator()(const greaper::WString& str)const noexcept
		{
#if COMPILER_MSVC
			return std::_Hash_array_representation(str.data(), str.size());
#else
			return std::_Hash_bytes(str.data(), str.size(), 0);
#endif
		}
	};

	template<class T, class A>
	struct hash<greaper::Vector<T, A>>
	{
		NODISCARD INLINE size_t operator()(const greaper::Vector<T, A>& v)const noexcept
		{
			size_t seed = 0;
			for (const T& elem : v)
				HashCombine(seed, elem);
			return seed;
		}
	};

	template<class T, std::size_t N>
	struct hash<std::array<T, N>>
	{
		NODISCARD INLINE size_t operator()(const std::array<T, N>& v)const noexcept
		{
			size_t seed = 0;
			for (const T& elem : v)
				HashCombine(seed, elem);
			return seed;
		}
	};

	template<class T>
	struct hash<greaper::UPtr<T>>
	{
		NODISCARD INLINE size_t operator()(const greaper::UPtr<T>& ptr)const noexcept
		{
			return std::hash<T>()(ptr.Get());
		}
	};

	template<class T>
	struct hash<greaper::SharedPointer<T>>
	{
		NODISCARD INLINE size_t operator()(const greaper::SharedPointer<T>& ptr)const noexcept
		{
			return std::hash<T>()(ptr.Get());
		}
	};

	template<class T>
	struct hash<greaper::WeakPointer<T>>
	{
		NODISCARD INLINE size_t operator()(const greaper::WeakPointer<T>& ptr)const noexcept
		{
			if (!ptr.Expired())
				return std::hash<greaper::SharedPointer<T>>()(ptr.Lock());
			return std::hash<ptruint>()(0);
		}
	};
}

/***********************************************************************************
*                            CONTAINER HELPER FUNCITONS                            *
***********************************************************************************/
namespace greaper
{
	template<class T, class _Alloc_>
	NODISCARD INLINE ssizet IndexOf(const Vector<T, _Alloc_>& container, const T& element) noexcept
	{
		for (auto it = container.cbegin(); it != container.cend(); ++it)
		{
			if ((*it) == element)
				return std::distance(container.begin(), it);
		}
		return -1;
	}
	template<class T, class _Alloc_, class CheckFn>
	NODISCARD INLINE ssizet IndexOf(const Vector<T, _Alloc_>& container, CheckFn checkFn)noexcept
	{
		for(auto it = container.begin(); it != container.end(); ++it)
		{
			if(checkFn(*it))
				return std::distance(container.begin(), it);
		}
		return -1;
	}
	template<class T, class _Alloc_>
	NODISCARD INLINE ssizet IndexOf(const Deque<T, _Alloc_>& container, const T& element) noexcept
	{
		for (auto it = container.cbegin(); it != container.cend(); ++it)
		{
			if ((*it) == element)
				return std::distance(container.begin(), it);
		}
		return -1;
	}
	template<class T, class _Alloc_, class CheckFn>
	NODISCARD INLINE ssizet IndexOf(const Deque<T, _Alloc_>& container, CheckFn checkFn)noexcept
	{
		for(auto it = container.begin(); it != container.end(); ++it)
		{
			if(checkFn(*it))
				return std::distance(container.begin(), it);
		}
		return -1;
	}
	template<class T, std::size_t N>
	NODISCARD INLINE ssizet IndexOf(T(&arr)[N], const T& element) noexcept
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if (arr[i] == element)
				return (ssizet)i;
		}
		return -1;
	}
	template<class T, std::size_t N, class CheckFn>
	NODISCARD INLINE ssizet IndexOf(T(&arr)[N], CheckFn checkFn) noexcept
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			if(checkFn(arr[i]))
				return static_cast<ssizet>(i);
		}
		return -1;
	}
	template<class T, class _Alloc_>
	NODISCARD INLINE bool Contains(const Vector<T, _Alloc_>& container, const T& elem) noexcept
	{
		return IndexOf<T, _Alloc_>(container, elem) >= 0;
	}
	template<class T, class _Alloc_, class CheckFn>
	NODISCARD INLINE bool Contains(const Vector<T, _Alloc_>& container, CheckFn checkFn) noexcept
	{
		return IndexOf<T, _Alloc_, CheckFn>(container, checkFn) >= 0;
	}
	template<class T, class _Alloc_>
	NODISCARD INLINE bool Contains(const Deque<T, _Alloc_>& container, const T& elem) noexcept
	{
		return IndexOf<T, _Alloc_>(container, elem) >= 0;
	}
	template<class T, class _Alloc_, class CheckFn>
	NODISCARD INLINE bool Contains(const Deque<T, _Alloc_>& container, CheckFn checkFn) noexcept
	{
		return IndexOf<T, _Alloc_, CheckFn>(container, checkFn) >= 0;
	}
	template<class T, std::size_t N>
	NODISCARD INLINE bool Contains(T(&arr)[N], const T& elem) noexcept
	{
		return IndexOf<T, N>(arr, elem);
	}
	template<class T, std::size_t N, class CheckFn>
	NODISCARD INLINE bool Contains(T(&arr)[N], CheckFn checkFn) noexcept
	{
		return IndexOf<T, N, CheckFn>(arr, checkFn);
	}
}