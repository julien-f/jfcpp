#ifndef H_JFCPP_EXPRESSION_OPERATIONS
#define H_JFCPP_EXPRESSION_OPERATIONS

#include <ostream>

#include "../common.hpp"
#include "base.hpp"

JFCPP_NAMESPACE_BEGIN

namespace expression
{
#	define BINARY_OPERATION(NAME, OP) \
		template <typename T1, typename T2> \
		class NAME : public base<typename T1::value_type> \
		{ \
		public: \
 \
			typedef typename T1::value_type value_type; \
 \
			NAME(T1 lhs, T2 rhs) : _lhs(lhs), _rhs(rhs) \
			{} \
 \
			value_type \
			eval() const \
			{ \
				return (_lhs.eval() OP _rhs.eval()); \
			} \
 \
			template <typename Param> \
			value_type \
			eval(Param param) const \
			{ \
				return (_lhs.eval(param) OP _rhs.eval(param)); \
			} \
 \
			friend std::ostream &operator << (std::ostream &s, const NAME &op) \
			{ \
				s << '(' << op._lhs << ' ' << #OP << ' ' << op._rhs << ')'; \
				return s; \
			} \
 \
		private: \
 \
			const T1 _lhs; \
 \
			const T2 _rhs; \
		}

#	define BINARY_OPERATION_ASSIGN(NAME, OP) BINARY_OPERATION(NAME##_assign, OP##=)

#	define UNARY_OPERATION(NAME, OP) \
		template <typename T> \
		class NAME : public base<typename T::value_type> \
		{ \
		public: \
 \
			typedef typename T::value_type value_type; \
 \
			NAME(T x) : _x(x) \
			{} \
 \
			value_type \
			eval() const \
			{ \
				return (OP _x.eval()); \
			} \
 \
			template <typename Param> \
			value_type \
			eval(Param param) const \
			{ \
				return (OP _x.eval(param)); \
			} \
 \
			friend std::ostream &operator << (std::ostream &s, const NAME &op) \
			{ \
				s << #OP << op._x; \
				return s; \
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

	/**
	 * Assignment operations.
	 */
	BINARY_OPERATION(assign, =);

	BINARY_OPERATION_ASSIGN(divides, /);
	BINARY_OPERATION_ASSIGN(minus, -);
	BINARY_OPERATION_ASSIGN(modulus, %);
	BINARY_OPERATION_ASSIGN(multiplies, *);
	BINARY_OPERATION_ASSIGN(plus, +);

	BINARY_OPERATION_ASSIGN(bit_and, &);
	BINARY_OPERATION_ASSIGN(bit_or, |);
	BINARY_OPERATION_ASSIGN(bit_shift_left, <<);
	BINARY_OPERATION_ASSIGN(bit_shift_right, >>);
	BINARY_OPERATION_ASSIGN(bit_xor, ^);

	#undef BINARY_OPERATION
	#undef BINARY_OPERATION_ASSIGN
	#undef UNARY_OPERATION
} // namespace expression

JFCPP_NAMESPACE_END

#endif // H_JFCPP_EXPRESSION_OPERATIONS
