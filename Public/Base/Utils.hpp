/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

 #pragma once

/***********************************************************************************************************************
 *                                                 HELPER FUNCTIONS                                                    * 
 **********************************************************************************************************************/

/** Checks if a value is within range [min,max) */
template<typename T>
NODISCARD INLINE constexpr bool IsWithin(const T& value, const T& min, const T& max)
{
	return value >= min && value < max;
}
/** Checks if a value is within range (min,max) */
template<typename T>
NODISCARD INLINE constexpr bool IsWithinExclusive(const T& value, const T& min, const T& max)
{
	return value > min && value < max;
}
/** Checks if a value is within range [min, max] */
template<class T>
NODISCARD INLINE constexpr bool IsWithinInclusive(const T& value, const T& min, const T& max)
{
	return value >= min && value <= max;
}
/** Checks if a number is a power of two */
template<typename T>
NODISCARD INLINE constexpr bool IsPowerOfTwo(const T value)
{
	return value != 0 && !(value & (value - 1));
}
/** Rounds number up/down to the next multiple, multiple must be power of two */
template<typename T>
NODISCARD INLINE constexpr T RoundUp(const T number, const T multiple)
{
	static_assert(!IsPowerOfTwo(multiple), "Multiple must be power of two.");
	const T result = (number + multiple - 1) & ~(multiple - 1);
	static_assert(number <= result && result < number + multiple);
	return result;
}
/** Computes the factor that tells by how much is bigger/smaller */
template<typename T>
NODISCARD INLINE constexpr T DivideAndRoundUp(T n, T d) noexcept
{
	return (n + d - 1) / d;
}
/** Rounds the given number up to the next higher power of two */
template<typename T>
NODISCARD INLINE constexpr T RoundUpToPowerOf2(T val)
{
	--val;
	val |= val >> 1;
	val |= val >> 2;
	val |= val >> 4;
	val |= val >> 8;
	val |= val >> 16;
	++val;
	return val;
}
template<typename T>
NODISCARD INLINE constexpr T Max(T a, T b)
{
	return (a > b) ? a : b;
}
template<typename T, typename... RestOfArgs>
NODISCARD INLINE constexpr T Max(T a, T b, RestOfArgs... args)
{
	return Max(Max(a,b), args...);
}
template<typename T>
NODISCARD INLINE constexpr T Min(T a, T b)
{
	return (a < b) ? a : b;
}
template<typename T, typename... RestOfArgs>
NODISCARD INLINE constexpr T Min(T a, T b, RestOfArgs... args)
{
	return Min(Min(a,b), args...);
}
template<typename T>
NODISCARD INLINE constexpr T Clamp(const T a, const T min, const T max)noexcept
{
	return Max(min, Min(max, a));
}
template<typename T>
NODISCARD INLINE constexpr T ClampZeroToOne(const T a)noexcept
{
	return Clamp(a, T(0), T(1));
}
template<typename T>
NODISCARD INLINE constexpr T ClampNegOneToOne(const T a)noexcept
{
	return Clamp(a, T(-1), T(1));
}
template<typename T>
NODISCARD INLINE constexpr T LerpUnclamped(const T begin, const T end, float pct)noexcept
{
	return begin * (1.f - pct) + end * pct;
}
template<typename T>
NODISCARD INLINE constexpr T LerpUnclamped(const T begin, const T end, double pct)noexcept
{
	return begin * (1.0 - pct) + end * pct;
}
template<typename T>
NODISCARD INLINE constexpr T Lerp(const T begin, const T end, float pct)noexcept
{
	return LerpUnclamped(begin, end, ClampZeroToOne(pct));
}
template<typename T>
NODISCARD INLINE constexpr T Lerp(const T begin, const T end, double pct)noexcept
{
	return LerpUnclamped(begin, end, ClampZeroToOne(pct));
}
template<typename Rtn, typename T>
NODISCARD INLINE constexpr Rtn LerpInverseUnsafe(const T begin, const T end, const T value)noexcept
{
	return Rtn(value - begin) / Rtn(end - begin);
}
template<typename Rtn, typename T>
NODISCARD INLINE constexpr Rtn LerpInverse(const T begin, const T end, const T value)noexcept
{
	return LerpInverseUnsafe<Rtn>(begin, end, Clamp(value, begin, end));
}
/** Computes the absolute value */
template<class T> 
NODISCARD INLINE constexpr T Abs(T a)noexcept
{
	return (a >= T(0)) ? a : -a;
}
NODISCARD INLINE constexpr bool IsNearlyEqual(float a, float b, float tolerance = MATH_TOLERANCE)noexcept
{
	return Abs(a - b) <= tolerance;
}
NODISCARD INLINE constexpr bool IsNearlyEqual(double a, double b, double tolerance = MATH_TOLERANCE)noexcept
{
	return Abs(a - b) <= tolerance;
}
/** Returns 1, 0 or -1 depending on relation of T to 0 */
template<class T>
NODISCARD INLINE constexpr T Sign(const T a)noexcept
{
	return ((a > (T)0) ? (T)1 : ((a) < (T)0) ? (T)-1 : (T)0);
}
/** Clamps an int32 into the int8 range. */
NODISCARD INLINE constexpr int8 ClampChar(const int32 i)
{
	return static_cast<int8>(Clamp(i, -128, 127));
}
/** Clamps an int32 into the int16 range. */
NODISCARD INLINE constexpr int16 ClampShort(const int32 i)
{
	return static_cast<int16>(Clamp(i, -32768, 32767));
}
/** Retruns true if value is NaN */
NODISCARD INLINE bool IsNaN(const float f) noexcept
{
	return (*reinterpret_cast<const uint32*>(&f) & 0x7FFFFFFF) > 0x7F800000;
}
/** Returns true if a value is finite */
NODISCARD INLINE bool IsFinite(const float f)
{
	return (*reinterpret_cast<const uint32*>(&f) & 0x7F800000) != 0x7F800000;
}
/** Returns true if a value is infinite */
NODISCARD INLINE bool IsInfinite(const float f)
{
	return !IsFinite(f);
}
/** Get the boolean value from a flag */
NODISCARD INLINE bool GetBitValue(const uint8* ptr, const uint32 index)noexcept
{
	const auto* const bytePtr = ptr + index / 8;
	const auto mask = static_cast<uint8>(1u << (index & 0x7u));
	return (*bytePtr & mask) != 0;
}
/** Set the boolean value to a flag */
INLINE void SetBitValue(uint8* ptr, const uint32 index, const bool set)noexcept
{
	const auto bytePtr = ptr + index / 8;
	const auto mask = static_cast<uint8>(1u << (index & 0x7u));
	if (set)
		*bytePtr |= mask;
	else
		*bytePtr &= (uint8)~mask;
}

/***********************************************************************************************************************
 *                                                  HASH FUNCTIONS                                                     * 
 **********************************************************************************************************************/

 namespace std { template<class T> struct hash; }
/**
*	Computes the hash of a type given the seed.
*/
INLINE void HashCombineHash(sizet& seed, sizet hash)
{
	seed ^= hash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template<typename T>
INLINE void HashCombine(sizet& seed, const T& val)
{
	HashCombineHash(seed, (sizet)std::hash<T>()(val));
}
/**
*	Computes the hash of the concatenated types given the seed.
*/
template<typename FirstArgType, typename... RestArgsType>
INLINE void HashCombine(sizet& seed, const FirstArgType& firstArg, const RestArgsType&... restArgs)
{
	HashCombine(seed, firstArg);
	HashCombine(seed, restArgs...);
}
/**
*	Computes the hash of the concatenated types.
*/
template<typename... ArgsType>
NODISCARD INLINE sizet ComputeHash(const ArgsType&... args)
{
	sizet seed = 0;
	HashCombine(seed, args...);
	return seed;
}

/***********************************************************************************************************************
 *                                                 MEMORY FUNCTIONS                                                    * 
 **********************************************************************************************************************/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

template<class T, sizet N>
INLINE constexpr sizet ArraySize(T(&)[N]) noexcept { return N; }

template<class T>
INLINE void ClearMemory(T& obj, sizet count = 1) noexcept
{
	memset(&obj, 0, sizeof(T) * count);
}
template<class T, size_t N>
INLINE void ClearMemory(T(&arr)[N]) noexcept
{
	memset(&arr[0], 0, sizeof(std::remove_extent<T>::type) * N);
}
template<class T>
INLINE void DuplicateMemory(const T& source, T& dst) noexcept
{
	memcpy(&dst, &source, sizeof(T));
}
template<class T>
INLINE bool CompareMemory(const T& left, const T& right)noexcept
{
	return memcmp(&left, &right, sizeof(T)) == 0;
}
template<class T>
NODISCARD INLINE bool IsMemoryCleared(const T& data) noexcept
{
	static const uint8 zeros[sizeof(T)]  = {};
	return ::memcmp(&data, &zeros, sizeof(T)) == 0;
}
