#pragma once

#include <type_traits>
#include <ostream>
#include <bitset>

/** Check if given type is a scoped enum */
template<typename E>
using rs_is_scoped_enum = std::integral_constant< bool,
    std::is_enum<E>::value && !std::is_convertible<E, int>::value >;


#define REGISTER_ENUM_FLAGS_TYPE(eft) \
template<> struct Rs__BitFlagsOps<eft> \
{ \
	static_assert( std::is_enum<eft>::value, \
	               "Are you trying to register a non-enum type as flags?" ); \
	static_assert( rs_is_scoped_enum<eft>::value, \
	               "Are you trying to register an unscoped enum as flags?" ); \
	static constexpr bool enabled = true; \
};

// By defaults types are not valid flags, so bit flags operators are disabled
template<typename> struct Rs__BitFlagsOps
{ static constexpr bool enabled = false; };

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
/*EFT*/ operator &(EFT lhs, EFT rhs)
{
	using u_t = typename std::underlying_type<EFT>::type;
	return static_cast<EFT>(static_cast<u_t>(lhs) & static_cast<u_t>(rhs));
}

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
/*EFT*/ operator &=(EFT& lhs, EFT rhs) { lhs = lhs & rhs; return lhs; }

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
/*EFT*/ operator |(EFT lhs, EFT rhs)
{
	using u_t = typename std::underlying_type<EFT>::type;
	return static_cast<EFT>(static_cast<u_t>(lhs) | static_cast<u_t>(rhs));
}

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
/*EFT*/ operator |=(EFT& lhs, EFT rhs) { lhs = lhs | rhs; return lhs; }


template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
/*EFT*/ operator ^(EFT lhs, EFT rhs)
{
	using u_t = typename std::underlying_type<EFT>::type;
	return static_cast<EFT>(static_cast<u_t>(lhs) ^ static_cast<u_t>(rhs));
}

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
/*EFT*/ operator ^=(EFT& lhs, EFT rhs) { lhs = lhs ^ rhs; return lhs; }

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, EFT>::type
operator ~(EFT val)
{
	using u_t = typename std::underlying_type<EFT>::type;
	return static_cast<EFT>(~static_cast<u_t>(val));
}

template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, bool>::type
operator !(EFT val)
{
	using u_t = typename std::underlying_type<EFT>::type;
	return static_cast<u_t>(val) == 0;
}

/// Nicely print flags bits as 1 and 0
template<typename EFT>
typename std::enable_if<Rs__BitFlagsOps<EFT>::enabled, std::ostream>::type&
operator <<(std::ostream& stream, EFT flags)
{
	using u_t = typename std::underlying_type<EFT>::type;
	return stream << std::bitset<sizeof(u_t)>(static_cast<u_t>(flags));
}


