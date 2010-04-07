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

#ifndef H_FUNCTIONAL
#define H_FUNCTIONAL

#include <functional>

/**
 * Identity unary function: f(x) = x.
 */
template <typename T>
struct identity_function : public std::unary_function<T, T>
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
class unary_composer : public std::unary_function<typename F2::argument_type,
                                                  typename F1::result_type>
{
private:

	typedef typename F2::argument_type argument_type;
	typedef typename F1::result_type result_type;

public:

	unary_composer(F1 f1, F2 f2) : _f1(f1), _f2(f2)
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
unary_compose(F1 f1, F2 f2)
{
	return unary_composer<F1, F2>(f1, f2);
}

/**
 * Composition of a binary function with two unary functions:
 * k(x) = f(g(x), h(y)).
 */
template <class F1, class F2, class F3>
class binary_composer : public std::binary_function<typename F2::argument_type,
                                                    typename F3::argument_type,
                                                    typename F1::result_type>
{
private:

	typedef typename F2::argument_type first_argument_type;
	typedef typename F3::argument_type second_argument_type;
	typedef typename F1::result_type result_type;

public:

	binary_composer(F1 f1, F2 f2, F3 f3) : _f1(f1), _f2(f2), _f3(f3)
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
template <class F1, class F2, class F3>
binary_composer<F1, F2, F3>
binary_compose(F1 f1, F2 f2, F3 f3)
{
	return binary_composer<F1, F2, F3>(f1, f2, f3);
}

/**
 *
 */
template <typename T1, typename T2 = T1, typename TR = T1>
struct divides : public std::binary_function<T1, T2, TR>
{
	TR operator()(const T1 &x, const T2 &y) const
	{
		return (x / y);
	}
};

/**
 *
 */
template <typename T1, typename T2 = T1, typename TR = T1>
struct minus : public std::binary_function<T1, T2, TR>
{
	TR operator()(const T1 &x, const T2 &y) const
	{
		return (x - y);
	}
};

/**
 *
 */
template <typename T1, typename T2 = T1, typename TR = T1>
struct modulo : public std::binary_function<T1, T2, TR>
{
	TR operator()(const T1 &x, const T2 &y) const
	{
		return (x % y);
	}
};

/**
 *
 */
template <typename T1, typename T2 = T1, typename TR = T1>
struct multiplies : public std::binary_function<T1, T2, TR>
{
	TR operator()(const T1 &x, const T2 &y) const
	{
		return (x * y);
	}
};

/**
 *
 */
template <typename T1, typename T2 = T1, typename TR = T1>
struct plus : public std::binary_function<T1, T2, TR>
{
	TR operator()(const T1 &x, const T2 &y) const
	{
		return (x + y);
	}
};

#endif
