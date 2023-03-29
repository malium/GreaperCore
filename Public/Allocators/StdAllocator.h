/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#include <vector>
#include <list>
#include <forward_list>
#include <queue>
#include <deque>
#include <stack>
#include <string>
#include <string_view>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std::string_view_literals;

namespace greaper
{
	template<class T, class _Alloc_ = GenericAllocator>
	class StdAlloc
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = sizet;
		using difference_type = ptrint;

		StdAlloc()noexcept = default;
		StdAlloc(StdAlloc&&)noexcept = default;
		StdAlloc(const StdAlloc&)noexcept = default;

		template<class U, class Alloc2> INLINE StdAlloc(const StdAlloc<U, Alloc2>&) {  }
		template<class U, class Alloc2> INLINE constexpr bool operator==(const StdAlloc<U, Alloc2>&) const noexcept { return true; }
		template<class U, class Alloc2> INLINE constexpr bool operator!=(const StdAlloc<U, Alloc2>&) const noexcept { return false; }

		template<class U> class rebind { public: using other = StdAlloc<U, _Alloc_>; };

		NODISCARD INLINE T* allocate(const size_t num)
		{
#if GREAPER_DEBUG_ALLOCATION
			if (num == 0)
				return nullptr;
			if (num > max_size())
				return nullptr;

			void*const p = AllocN<T, _Alloc_>(num);
			if (p == nullptr)
				return nullptr;
			return static_cast<T*>(p);
#else
			return reinterpret_cast<T*>(AllocN<T, _Alloc_>(num));
#endif
		}

		INLINE void deallocate(pointer p, size_type)
		{
			Dealloc<_Alloc_>(p);
		}

		INLINE constexpr size_t max_size() { return std::numeric_limits<size_type>::max() / sizeof(T); }
		INLINE void destroy(pointer p) { (p)->~T(); }

		template<class... Args>
		INLINE void construct(pointer p, Args&&... args)noexcept { new(p)T(std::forward<Args>(args)...); }
	};

	template<class T, sizet alignment, class _Alloc_ = GenericAllocator>
	class StdAlignedAlloc
	{
	public:
		using value_type = T;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = sizet;
		using difference_type = ptrint;

		StdAlignedAlloc()noexcept = default;
		StdAlignedAlloc(StdAlignedAlloc&&)noexcept = default;
		StdAlignedAlloc(const StdAlignedAlloc&)noexcept = default;

		template<class U, sizet Align, class Alloc2> INLINE StdAlignedAlloc(const StdAlignedAlloc<U, Align, Alloc2>&) {  }
		template<class U, sizet Align, class Alloc2> INLINE constexpr bool operator==(const StdAlignedAlloc<U, Align, Alloc2>&) const noexcept { return true; }
		template<class U, sizet Align, class Alloc2> INLINE constexpr bool operator!=(const StdAlignedAlloc<U, Align, Alloc2>&) const noexcept { return false; }

		template<class U> class rebind { public: using other = StdAlignedAlloc<U, alignment, _Alloc_>; };

		INLINE static constexpr sizet Alignment()noexcept { return alignment; }
		NODISCARD INLINE T* allocate(const size_t num)
		{
#if GREAPER_DEBUG_ALLOCATION
			if (num == 0)
				return nullptr;
			if (num > max_size())
				return nullptr;

			void*const p = AllocAlignedN<T, _Alloc_>(num, alignment);
			if (p == nullptr)
				return nullptr;
			return static_cast<T*>(p);
#else
			return reinterpret_cast<T*>(AllocAlignedN<T, _Alloc_>(num, alignment));
#endif
		}

		INLINE void deallocate(pointer p, size_type)
		{
			DeallocAligned<_Alloc_>(p);
		}

		INLINE constexpr size_t max_size() { return std::numeric_limits<size_type>::max() / sizeof(T); }
		INLINE void destroy(pointer p) { (p)->~T(); }

		template<class... Args>
		INLINE void construct(pointer p, Args&&... args)noexcept { new(p)T(std::forward<Args>(args)...); }
	};

	template<typename T, typename A = StdAlloc<T>>
	using BasicString = std::basic_string<T, std::char_traits<T>, A>;
	template<typename T>
	using BasicStringView = std::basic_string_view<T, std::char_traits<T>>;

	template<typename T, typename A = StdAlloc<T>>
	using BasicStringStream = std::basic_stringstream<T, std::char_traits<T>, A>;

	using String = BasicString<achar>;
	using StringView = BasicStringView<achar>;
	using StringStream = BasicStringStream<achar>;
	using WString = BasicString<wchar>;
	using WStringView = BasicStringView<wchar>;
	using WStringStream = BasicStringStream<wchar>;
	using U16String = BasicString<u16char>;
	using U16StringStream = BasicStringStream<u16char>;
	using U32String = BasicString<u32char>;
	using U32StringStream = BasicStringStream<u32char>;

	template<typename T, typename A = StdAlloc<T>>
	using Vector = std::vector<T, A>;
	template<typename T, sizet Alignment, typename A = StdAlignedAlloc<T, Alignment>>
	using VectorAligned = std::vector<T, A>;

	using StringVec = Vector<String>;
	using WStringVec = Vector<WString>;

	template<typename T, typename A = StdAlloc<T>>
	using Queue = std::queue<T, std::deque<T, A>>;

	template<typename T, typename A = StdAlloc<T>>
	using Deque = std::deque<T, A>;

	template<typename T, typename A = StdAlloc<T>>
	using List = std::list<T, A>;

	template<typename T, typename A = StdAlloc<T>>
	using ForwardList = std::forward_list<T, A>;

	template<typename T, typename A = StdAlloc<T>>
	using Stack = std::stack<T, std::deque<T, A>>;

	template<typename K, typename C = std::less<K>, typename A = StdAlloc<K>>
	using Set = std::set<K, C, A>;

	template<typename K, typename V, typename P = std::less<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using Map = std::map<K, V, P, A>;

	template<typename K, typename C = std::less<K>, typename A = StdAlloc<K>>
	using MultiSet = std::multiset<K, C, A>;

	template<typename K, typename V, typename P = std::less<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using MultiMap = std::multimap<K, V, P, A>;

	struct EnumClassHash
	{
		template<typename T>
		INLINE constexpr std::size_t operator()(T t)const
		{
			return static_cast<std::size_t>(t);
		}
	};
	template<typename Key>
	using HashType = typename std::conditional_t<std::is_enum_v<Key>, EnumClassHash, std::hash<Key>>;

	template<typename T, typename H = HashType<T>, typename C = std::equal_to<T>, typename A = StdAlloc<T>>
	using UnorderedSet = std::unordered_set<T, H, C, A>;

	template<typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMap = std::unordered_map<K, V, H, C, A>;

	template<typename K, typename V, typename H = HashType<K>, typename C = std::equal_to<K>, typename A = StdAlloc<std::pair<const K, V>>>
	using UnorderedMultiMap = std::unordered_multimap<K, V, H, C, A>;

	template<typename T, typename H = HashType<T>, typename C = std::equal_to<T>, typename A = StdAlloc<T>>
	using UnorderedMultiSet = std::unordered_multiset<T, H, C, A>;
}