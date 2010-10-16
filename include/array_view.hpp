/**
 * This class is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This class is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this class.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Julien Fontanet <julien.fontanet@isonoe.net>
 */

#ifndef H_JFCPP_ARRAY_VIEW
#define H_JFCPP_ARRAY_VIEW

#include <algorithm>
#include <cstddef>
#include <istream>
#include <iterator>
#include <ostream>

#include <contracts.h>

#include "algorithm.hpp"
#include "common.hpp"
#include "functional.hpp"
#include "operators.hpp"

JFCPP_NAMESPACE_BEGIN

/**
 * This class is a simple wrapper around a C array which provides helper for
 * copying, comparing and accessing elements.
 *
 * Be careful, this class does not own the memory, it only provides a way to
 * manipulates the data in it, consequently, it will not free the memory when
 * destroyed.
 */
template <typename T>
class array_view
	: public operators::addable<array_view<T> >,
	  public operators::equality_comparable<array_view<T> >,
	  public operators::dividable<array_view<T> >,
	  public operators::modable<array_view<T> >,
	  public operators::multipliable<array_view<T> >,
	  public operators::subtractable<array_view<T> >
{
#	include "array_view/common.hpp"

public:

	/**
	 *
	 */
	typedef value_type *iterator;

	/**
	 *
	 */
	typedef value_type &reference;

	/**
	 *
	 */
	typedef std::reverse_iterator<iterator> reverse_iterator;

	/**
	 *
	 */
	typedef value_type *pointer;

	/**
	 *
	 */
	array_view(size_t size, pointer raw)
		: _size(size), _raw(raw)
	{
		requires(raw != NULL);
		requires(size != 0);
	}

	/**
	 *
	 */
	reference at(size_t i)
	{
		if (i >= this->size())
		{
			throw std::out_of_range("no such index");
		}

		return (*this)[i];
	}

	/**
	 *
	 */
	iterator begin()
	{
		return this->_raw;
	}

	/**
	 *
	 */
	iterator end()
	{
		return (this->_raw + this->_size);
	}

	/**
	 *
	 */
	pointer raw()
	{
		return this->_raw;
	}

	/**
	 *
	 */
	reverse_iterator rbegin()
	{
		return reverse_iterator(this->end());
	}

	/**
	 *
	 */
	reverse_iterator rend()
	{
		return reverse_iterator(this->begin());
	}

	/**
	 *
	 */
	void set(size_t size, pointer raw)
	{
		requires(raw != NULL);
		requires(size != 0);

		this->_raw = raw;
		this->_size = size;
	}

	/**
	 *
	 */
	reference operator[](size_t i)
	{
		requires(i < this->_size);

		return this->_raw[i];
	}

	/**
	 *
	 */
	template <typename U>
	array_view &operator=(const array_view<U> &a)
	{
		requires(this->_size == a.size());

		std::copy(a.begin(), a.end(), this->begin());

		return *this;
	}

	/**
	 *
	 */
	template <typename U>
	array_view &operator=(const U &s)
	{
		std::fill(this->begin(), this->end(), s);

		return *this;
	}

#	define ARRAY_VIEW_OPERATION(OP, FUNC_NAME) \
	template <typename T2> \
	array_view &operator OP##=(const array_view<T2> &a) \
	{ \
		requires(this->size() == a.size()); \
 \
		algorithm::apply(this->begin(), this->end(), a.begin(), \
		                 functional::FUNC_NAME##_assign<value_type, T2>()); \
 \
		return *this; \
	} \
	template <typename T2> \
	array_view &operator OP##=(const T2 &s) \
	{ \
		algorithm::apply(this->begin(), this->end(), \
		                 std::bind2nd(functional::FUNC_NAME##_assign<value_type, T2>(), s)); \
 \
		return *this; \
	}

	ARRAY_VIEW_OPERATION(+, plus)
	ARRAY_VIEW_OPERATION(-, minus)
	ARRAY_VIEW_OPERATION(*, multiplies)
	ARRAY_VIEW_OPERATION(/, divides)
	ARRAY_VIEW_OPERATION(%, modulus)

	ARRAY_VIEW_OPERATION(&, bit_and)
	ARRAY_VIEW_OPERATION(|, bit_or)
	ARRAY_VIEW_OPERATION(<<, bit_shift_left)
	ARRAY_VIEW_OPERATION(>>, bit_shift_right)
	ARRAY_VIEW_OPERATION(^, bit_xor)

#	undef ARRAY_VIEW_OPERATION

private:

	/**
	 *
	 */
	pointer _raw;
};

template <typename T>
class array_view<const T>
	: public operators::addable<array_view<const T> >,
	  public operators::equality_comparable<array_view<const T> >,
	  public operators::dividable<array_view<const T> >,
	  public operators::modable<array_view<const T> >,
	  public operators::multipliable<array_view<const T> >,
	  public operators::subtractable<array_view<const T> >

{
#	include "array_view/common.hpp"

public:

	/**
	 * Allows to create an array_view on constant values from one on
	 * non-constant values.
	 */
	array_view(const array_view<T> &a)
		: _size(a.size()), _raw(a.raw())
	{}

	/**
	 *
	 */
	array_view(size_t size, const_pointer raw)
		: _size(size), _raw(raw)
	{
		requires(raw != NULL);
		requires(size != 0);
	}

	/**
	 *
	 */
	void set(size_t size, const_pointer raw)
	{
		requires(raw != NULL);
		requires(size != 0);

		this->_raw = raw;
		this->_size = size;
	}
	void set(const array_view<const T> &ar)
	{
		this->set(ar._size, ar._raw);
	}

private:

	/**
	 *
	 */
	const_pointer _raw;

	/**
	 * No copy for the constant version.
	 */
	array_view<const T> &operator=(const array_view<const T> &)
	{return *this;}
};

/**
 *
 */
template <typename T>
array_view<T>
make_array_view(size_t size, T *raw)
{
	return array_view<T>(size, raw);
}

/**
 *
 */
template <typename T, size_t size>
array_view<T>
make_array_view(T (&raw)[size])
{
	return array_view<T>(size, raw);
}

JFCPP_NAMESPACE_END

/**
 *
 */
template <typename T>
std::istream &operator>>(std::istream &s, JFCPP_NS()array_view<T> a)
{
	for (size_t i = 0, n = a.size(); i < n; ++i)
	{
		s >> a[i];
	}

	return s;
}

/**
 *
 */
template <typename T>
std::ostream &operator<<(std::ostream &s, const JFCPP_NS()array_view<T> &a)
{
	const size_t n = a.size();

	if (n != 0)
	{
		s << a[0];
		for (size_t i = 1; i < n; ++i)
		{
			s << " " << a[i];
		}
	}

	return s;
}

#endif
