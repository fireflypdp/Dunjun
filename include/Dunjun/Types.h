#ifndef DUNJUN_TYPES_H
#define DUNJUN_TYPES_H

#include <cstdint>
#include <cstddef>

namespace Dunjun
{
	using s08 = std::int8_t;
	using s16 = std::int16_t;
	using s32 = std::int32_t;
	using s64 = std::int64_t;

	using u08 = std::uint8_t;
	using u16 = std::uint16_t;
	using u32 = std::uint32_t;
	using u64 = std::uint64_t;

	using f32 = float;
	using f64 = double;

	using b08 = bool;
	using b32 = s32;

	using intPtr = std::intptr_t;
	using uintPtr = std::uintptr_t;

	using usize = std::size_t;
} // namespace Dunjun

#endif // DUNJUN_TYPES_H