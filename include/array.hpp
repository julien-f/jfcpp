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

#ifndef H_ARRAY
#define H_ARRAY

#include <algorithm>
#include <cstddef>
#include <iterator>

/**
 * @template T The type of contained elements.
 * @template S The number of contained elements.
 */
template<typename T, size_t S = 0>
class array
{
#	include "array/common.hpp"

public:

	/**
	 *
	 */
	size_t size() const
	{
		return S;
	}

private:

	/**
	 *
	 */
	value_type _data[S];
};

template <typename T>
class array<T, 0>
{
	static const size_t S = 0;

#	include "array/common.hpp"

public:

	/**
	 *
	 */
	array(size_t size) : _size(size)
	{
		requires(size > 0);
		this->_allocate();
	}

	/**
	 *
	 */
	array(const array<value_type, 0> &a) : _size(size)
	{
		this->_allocate();
		*this = a;
	}

	/**
	 *
	 */
	template<typename T2, size_t S2>
	array(const array<T2, S2> &a) : _size(size)
	{
		this->_allocate();
		*this = a;
	}

	/**
	 *
	 */
	~array()
	{
		delete [] this->_data;
	}

	/**
	 *
	 */
	size_t size() const
	{
		return this->_size;
	}

	/**
	 *
	 */
	array<value_type, 0> &operator=(const array<value_type, 0> &a)
	{
		return this->operator=<value_type, 0>(a);
	}

private:

	/**
	 *
	 */
	pointer _data;

	/**
	 *
	 */
	const size_t _size;

	/**
	 *
	 */
	void _allocate()
	{
		this->_data = new value_type[this->_size];
	}
};

/**
 *
 */
template<typename T, size_t S>
std::istream &operator>>(std::istream &s, array<T, S> a)
{
	for (size_t i = 0, n = a.size(); (i < n) && s.good(); ++i)
	{
		s >> a[i];
	}

	return s;
}

/**
 *
 */
template<typename T, size_t S>
std::ostream &operator<<(std::ostream &s, const array<T, S> &a)
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

	s << std::endl;
	return s;
}

#endif
