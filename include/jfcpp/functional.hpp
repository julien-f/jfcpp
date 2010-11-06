/**
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Julien Fontanet <julien.fontanet@isonoe.net>
 */

#ifndef H_JFCPP_FUNCTIONAL
#define H_JFCPP_FUNCTIONAL

#include <functional>

#include "common.hpp"

JFCPP_NAMESPACE_BEGIN

namespace functional
{
	/**
	 * Identity unary function: f(x) = x.
	 */
	template <typename T>
	struct identity : public std::unary_function<T, T>
	{
		T operator()(const T &x)
		{
			return x;
		}
	};

	/**
	 * Composition of two unary functions: h(x) = f(g(x)).
	 */
	template <class F1, class F2>
	class unary_composer
		: public std::unary_function<typename F2::argument_type,
		                             typename F1::result_type>
	{
	public:

		typedef typename F2::argument_type argument_type;
		typedef typename F1::result_type result_type;

		unary_composer(F1 f1 = F1(), F2 f2 = F2()) : _f1(f1), _f2(f2)
		{}

		result_type operator()(const argument_type &x)
		{
			return this->_f1(this->_f2(x));
		}

	private:

		F1 _f1;
		F2 _f2;
	};

	/**
	 *
	 */
	template <class F1, class F2>
	unary_composer<F1, F2>
	compose(F1 f1, F2 f2) // functor & functor
	{
		return unary_composer<F1, F2>(f1, f2);
	}
	template <class Arg1, class Result1, class F2>
	unary_composer<std::pointer_to_unary_function<Arg1, Result1>, F2>
	compose(Result1 (*f1)(Arg1), F2 f2) // pointer & functor
	{
		return unary_composer<std::pointer_to_unary_function<Arg1, Result1>, F2>(std::ptr_fun(f1), f2);
	}
	template <class F1, class Arg2, class Result2>
	unary_composer<F1, std::pointer_to_unary_function<Arg2, Result2> >
	compose(F1 f1, Result2 (*f2)(Arg2)) // functor & pointer
	{
		return unary_composer<F1, std::pointer_to_unary_function<Arg2, Result2> >(f1, std::ptr_fun(f2));
	}
	template <class Arg1, class Result1, class Arg2, class Result2>
	unary_composer<std::pointer_to_unary_function<Arg1, Result1>, std::pointer_to_unary_function<Arg2, Result2> >
	compose(Result1 (*f1)(Arg1), Result2 (*f2)(Arg2)) // pointer & pointer
	{
		return unary_composer<std::pointer_to_unary_function<Arg1, Result1>, std::pointer_to_unary_function<Arg2, Result2> >(std::ptr_fun(f1), std::ptr_fun(f2));
	}

	/**
	 * Composition of a binary function with two unary functions:
	 * k(x) = f(g(x), h(y)).
	 */
	template <class F1, class F2, class F3>
	class binary_composer
		: public std::binary_function<typename F2::argument_type,
		                              typename F3::argument_type,
		                              typename F1::result_type>
	{
	public:

		typedef typename F2::argument_type first_argument_type;
		typedef typename F3::argument_type second_argument_type;
		typedef typename F1::result_type result_type;

		binary_composer(F1 f1 = F1(), F2 f2 = F2(), F3 f3 = F3())
			: _f1(f1), _f2(f2), _f3(f3)
		{}

		result_type operator()(const first_argument_type &x,
		                       const second_argument_type &y)
		{
			return this->_f1(this->_f2(x), this->_f3(y));
		}

	private:

		F1 _f1;
		F2 _f2;
		F3 _f3;
	};

	/**
	 *
	 */
	// functor & functor & functor
	template <class F1, class F2, class F3>
	binary_composer<F1, F2, F3>
	compose(F1 f1, F2 f2, F3 f3)
	{
		return binary_composer<F1, F2, F3>(f1, f2, f3);
	}

	// functor & functor & pointer
	template <class F1, class F2, class Arg3, class Result3>
	binary_composer<F1, F2, std::pointer_to_unary_function<Arg3, Result3> >
	compose(F1 f1, F2 f2, Result3 (*f3)(Arg3))
	{
		return binary_composer<F1, F2, std::pointer_to_unary_function<Arg3, Result3> >(f1, f2, std::ptr_fun(f3));
	}

	// functor & pointer & functor
	template <class F1, class Arg2, class Result2, class F3>
	binary_composer<F1, std::pointer_to_unary_function<Arg2, Result2>, F3>
	compose(F1 f1, Result2 (*f2)(Arg2), F3 f3)
	{
		return binary_composer<F1, std::pointer_to_unary_function<Arg2, Result2>, F3>(f1, std::ptr_fun(f2), f3);
	}

	// functor & pointer & pointer
	template <class F1, class Arg2, class Result2, class Arg3, class Result3>
	binary_composer<F1, std::pointer_to_unary_function<Arg2, Result2>,
	                std::pointer_to_unary_function<Arg3, Result3> >
	compose(F1 f1, Result2 (*f2)(Arg2), Result3 (*f3)(Arg3))
	{
		return binary_composer<F1, std::pointer_to_unary_function<Arg2, Result2>,
			std::pointer_to_unary_function<Arg3, Result3> >(f1, std::ptr_fun(f2), std::ptr_fun(f3));
	}

	// pointer & functor & functor
	template <class Arg11, class Arg12, class Result1, class F2, class F3>
	binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>, F2, F3>
	compose(Result1 (*f1)(Arg11, Arg12), F2 f2, F3 f3)
	{
		return binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>, F2, F3>(std::ptr_fun(f1), f2, f3);
	}

	// pointer & functor & pointer
	template <class Arg11, class Arg12, class Result1, class F2, class Arg3, class Result3>
	binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>, F2,
	                std::pointer_to_unary_function<Arg3, Result3> >
	compose(Result1 (*f1)(Arg11, Arg12), F2 f2, Result3 (*f3)(Arg3))
	{
		return binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>, F2,
			std::pointer_to_unary_function<Arg3, Result3> >(std::ptr_fun(f1), f2, std::ptr_fun(f3));
	}

	// pointer & pointer & functor
	template <class Arg11, class Arg12, class Result1, class Arg2, class Result2, class F3>
	binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>,
	                std::pointer_to_unary_function<Arg2, Result2>, F3>
	compose(Result1 (*f1)(Arg11, Arg12), Result2 (*f2)(Arg2), F3 f3)
	{
		return binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>,
			std::pointer_to_unary_function<Arg2, Result2>, F3>(std::ptr_fun(f1), std::ptr_fun(f2), f3);
	}

	// pointer & pointer & pointer
	template <class Arg11, class Arg12, class Result1, class Arg2, class Result2, class Arg3, class Result3>
	binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>,
	                std::pointer_to_unary_function<Arg2, Result2>,
	                std::pointer_to_unary_function<Arg3, Result3> >
	compose(Result1 (*f1)(Arg11, Arg12), Result2 (*f2)(Arg2), Result3 (*f3)(Arg3))
	{
		return binary_composer<std::pointer_to_binary_function<Arg11, Arg12, Result1>,
			std::pointer_to_unary_function<Arg2, Result2>,
			std::pointer_to_unary_function<Arg3, Result3> >(std::ptr_fun(f1), std::ptr_fun(f2), std::ptr_fun(f3));
	}

#	define JFCPP_UNARY_OPERATION(NAME, OP) \
	template <typename T, typename TR = T> \
	struct NAME : public std::unary_function<T, TR> \
	{ \
		TR operator()(const T &x) const \
		{ \
			return (OP x); \
		} \
	}

#	define JFCPP_BINARY_OPERATION(NAME, OP) \
	template <typename T1, typename T2 = T1, typename TR = T1> \
	struct NAME : public std::binary_function<T1, T2, TR> \
	{ \
		TR operator()(const T1 &x, const T2 &y) const \
		{ \
			return (x OP y); \
		} \
	}

#	define JFCPP_BINARY_OPERATION_ASSIGN(NAME, OP) \
	template <typename T1, typename T2> \
	struct NAME##_assign : public std::binary_function<T1, T2, void> \
	{ \
		void operator()(T1 &x, const T2 &y) const \
		{ \
			x OP##= y; \
		} \
	}

	/**
	 * Arithmetic operations.
	 */
	JFCPP_UNARY_OPERATION(negate, -);

	JFCPP_BINARY_OPERATION(divides, /);
	JFCPP_BINARY_OPERATION(minus, -);
	JFCPP_BINARY_OPERATION(modulus, %);
	JFCPP_BINARY_OPERATION(multiplies, *);
	JFCPP_BINARY_OPERATION(plus, +);

	JFCPP_BINARY_OPERATION_ASSIGN(divides, /);
	JFCPP_BINARY_OPERATION_ASSIGN(minus, -);
	JFCPP_BINARY_OPERATION_ASSIGN(modulus, %);
	JFCPP_BINARY_OPERATION_ASSIGN(multiplies, *);
	JFCPP_BINARY_OPERATION_ASSIGN(plus, +);

	/**
	 * Bitwise operations.
	 */
	JFCPP_UNARY_OPERATION(bit_not, ~);

	JFCPP_BINARY_OPERATION(bit_and, &);
	JFCPP_BINARY_OPERATION(bit_or, |);
	JFCPP_BINARY_OPERATION(bit_shift_left, <<);
	JFCPP_BINARY_OPERATION(bit_shift_right, >>);
	JFCPP_BINARY_OPERATION(bit_xor, ^);

	JFCPP_BINARY_OPERATION_ASSIGN(bit_and, &);
	JFCPP_BINARY_OPERATION_ASSIGN(bit_or, |);
	JFCPP_BINARY_OPERATION_ASSIGN(bit_shift_left, <<);
	JFCPP_BINARY_OPERATION_ASSIGN(bit_shift_right, >>);
	JFCPP_BINARY_OPERATION_ASSIGN(bit_xor, ^);

	/**
	 * Logical operations.
	 */
	JFCPP_UNARY_OPERATION(logical_not, !);

	JFCPP_BINARY_OPERATION(logical_and, &&);
	JFCPP_BINARY_OPERATION(logical_or, ||);

#	undef JFCPP_UNARY_OPERATION
#	undef JFCPP_BINARY_OPERATION
#	undef JFCPP_BINARY_OPERATION_ASSIGN
} // namespace functional

JFCPP_NAMESPACE_END

#endif
