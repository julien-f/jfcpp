#ifndef H_EXPRESSION_OPERATIONS
#define H_EXPRESSION_OPERATIONS

#include "base.hpp"

namespace expression
{
#	define BINARY_OPERATION(NAME, OP) \
	template <typename T1, typename T2> \
	class NAME : public base<typename T1::value_type, typename T1::param_type> \
	{ \
	public: \
 \
		typedef typename T1::param_type param_type; \
 \
		typedef typename T1::value_type value_type; \
 \
		NAME(T1 lhs, T2 rhs) : _lhs(lhs), _rhs(rhs) \
		{} \
 \
		value_type eval(param_type param = param_type()) const \
		{ \
			return (_lhs.eval(param) OP _rhs.eval(param)); \
		} \
 \
	private: \
 \
		const T1 _lhs; \
 \
		const T2 _rhs; \
	}

#	define UNARY_OPERATION(NAME, OP) \
	template <typename T> \
	class NAME : public base<typename T::value_type, typename T::param_type> \
	{ \
	public: \
 \
		typedef typename T::param_type param_type; \
 \
		typedef typename T::value_type value_type; \
 \
		NAME(T x) : _x(x) \
		{} \
 \
		value_type eval(param_type param = param_type()) const \
		{ \
			return (OP _x.eval(param)); \
		} \
 \
	private: \
 \
		const T _x; \
	}

	/**
	 * Arithmetic operations.
	 */
	UNARY_OPERATION(negate, -);

	BINARY_OPERATION(divides, /);
	BINARY_OPERATION(minus, -);
	BINARY_OPERATION(modulus, %);
	BINARY_OPERATION(multiplies, *);
	BINARY_OPERATION(plus, +);

	/**
	 * Bitwise operations.
	 */
	UNARY_OPERATION(bit_not, ~);

	BINARY_OPERATION(bit_and, &);
	BINARY_OPERATION(bit_or, |);
	BINARY_OPERATION(bit_shift_left, <<);
	BINARY_OPERATION(bit_shift_right, >>);
	BINARY_OPERATION(bit_xor, ^);

	/**
	 * Logical operations.
	 */
	UNARY_OPERATION(logical_not, !);

	BINARY_OPERATION(logical_and, &&);
	BINARY_OPERATION(logical_or, ||);

#	undef BINARY_OPERATION
#	undef UNARY_OPERATION
} // namespace expression

#endif // H_EXPRESSION_OPERATIONS

