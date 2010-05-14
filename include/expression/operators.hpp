#include "../meta/enable_if.hpp"
#include "../meta/is_a.hpp"
#include "../meta/logic.hpp"

namespace operators
{
	using meta::and_;
	using meta::enable_if;
	using meta::is_a;

#	define BINARY_OPERATOR(NAME, OP) \
		template <typename T> \
		NAME<T, wrapper<typename T::value_type> > \
		operator OP(T lhs, typename T::value_type rhs) \
		{ \
			return NAME<T, wrapper<typename T::value_type> >(lhs, rhs); \
		} \
		template <typename T> \
		NAME<wrapper<typename T::value_type>, T> \
		operator OP(typename T::value_type lhs, T rhs) \
		{ \
			return NAME<wrapper<typename T::value_type>, T>(lhs, rhs); \
		} \
		template <typename T1, typename T2> \
		typename enable_if<and_<is_a<base<typename T1::value_type>, T1>::value, \
		                        is_a<base<typename T2::value_type>, T2>::value>::value, \
		                   NAME<T1, T2> >::type \
		operator OP(T1 lhs, T2 rhs) \
		{ \
			return NAME<T1, T2>(lhs, rhs); \
		}

#	define UNARY_OPERATOR(NAME, OP) \
		template <typename T> \
		NAME<T> \
		operator OP(T x) \
		{ \
			return NAME<T>(x); \
		}

	/**
	 * Arithmetic operators.
	 */
	UNARY_OPERATOR(negate, -)

	BINARY_OPERATOR(divides, /)
	BINARY_OPERATOR(minus, -)
	BINARY_OPERATOR(modulus, %)
	BINARY_OPERATOR(multiplies, *)
	BINARY_OPERATOR(plus, +)

	/**
	 * Bitwise operators.
	 */
	UNARY_OPERATOR(bit_not, ~)

	BINARY_OPERATOR(bit_and, &)
	BINARY_OPERATOR(bit_or, |)
	BINARY_OPERATOR(bit_shift_left, <<)
	BINARY_OPERATOR(bit_shift_right, >>)
	BINARY_OPERATOR(bit_xor, ^)

	/**
	 * Logical operators.
	 */
	UNARY_OPERATOR(logical_not, !)

	BINARY_OPERATOR(logical_and, &&)
	BINARY_OPERATOR(logical_or, ||)

#	undef BINARY_OPERATOR
#	undef UNARY_OPERATOR
} // namespace operators
