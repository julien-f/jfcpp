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

#ifndef H_ARRAY_VIEW
#define H_ARRAY_VIEW

#include <algorithm>
#include <cstddef>
#include <istream>
#include <ostream>

#include "contracts.h"

/**
 * This class is a simple wrapper around a C array which provides helper for
 * copying, comparing and accessing elements.
 */
template<typename T>
class array_view
{
public:

	/**
	 *
	 */
	typedef T value_type;

	/**
	 *
	 */
	typedef const value_type *const_iterator;

	/**
	 *
	 */
	typedef const value_type &const_reference;

	/**
	 *
	 */
	typedef const value_type *const_pointer;

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
	typedef value_type *pointer;

	/**
	 *
	 */
	array_view(size_t size, pointer raw)
		: _raw(raw), _size(size)
	{
		requires(raw != NULL);
	}

	/**
	 *
	 */
	iterator begin()
	{
		return this->_raw;
	}
	const_iterator begin() const
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
	const_iterator end() const
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
	const_pointer raw() const
	{
		return this->_raw;
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
	template<typename U>
	bool operator==(const array_view<U> &a) const
	{
		return ((this->_size == a.size()) &&
		        std::equal(this->begin(), this->end(), a.begin()));
	}

	/**
	 *
	 */
	template<typename U>
	bool operator<(const array_view<U> &a) const
	{
		return std::lexicographical_compare(this->begin(), this->end(),
		                                    a.begin(), a .end());
	}

	/**
	 *
	 */
	template<typename U>
	array_view &operator=(const array_view<U> &a)
	{
		requires(this->_size == a.size());

		std::copy(a.begin(), a.end(), this->begin());

		return *this;
	}

	/**
	 *
	 */
	reference operator[](size_t i)
	{
		requires(i < this->_size);

		return this->_raw[i];
	}
	const_reference operator[](size_t i) const
	{
		requires(i < this->_size);

		return this->_raw[i];
	}

private:

	/**
	 *
	 */
	pointer _raw;

	/**
	 *
	 */
	size_t _size;
};

template<typename T>
class array_view<const T>
{
public:

	/**
	 *
	 */
	typedef T value_type;

	/**
	 *
	 */
	typedef const value_type *const_iterator;

	/**
	 *
	 */
	typedef const value_type &const_reference;

	/**
	 *
	 */
	typedef const value_type *const_pointer;

	/**
	 *
	 */
	array_view(size_t size, const_pointer raw)
		: _raw(raw), _size(size)
	{
		requires(raw != NULL);
	}

	/**
	 *
	 */
	const_iterator begin() const
	{
		return this->_raw;
	}

	/**
	 *
	 */
	const_iterator end() const
	{
		return (this->_raw + this->_size);
	}

	/**
	 *
	 */
	const_pointer raw() const
	{
		return this->_raw;
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
	template<typename U>
	bool operator==(const array_view<U> &a) const
	{
		return ((this->_size == a.size()) &&
		        std::equal(this->begin(), this->end(), a.begin()));
	}

	/**
	 *
	 */
	template<typename U>
	bool operator<(const array_view<U> &a) const
	{
		return std::lexicographical_compare(this->begin(), this->end(),
		                                    a.begin(), a .end());
	}

	/**
	 *
	 */
	const_reference operator[](size_t i) const
	{
		requires(i < this->_size);

		return this->_raw[i];
	}

private:

	/**
	 *
	 */
	const_pointer _raw;

	/**
	 *
	 */
	size_t _size;

	/**
	 * No copy for the constant version.
	 */
	array_view<const T> &operator=(const array_view<const T> &)
	{return *this;}
};

/**
 *
 */
template<typename T>
array_view<T>
make_array_view(size_t size, T *raw)
{
	return array_view<T>(size, raw);
}

/**
 *
 */
template<typename T, size_t size>
array_view<T>
make_array_view(T (&raw)[size])
{
	return array_view<T>(size, raw);
}

/**
 *
 */
template<typename T>
std::istream &operator>>(std::istream &s, array_view<T> &a)
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
template<typename T>
std::ostream &operator<<(std::ostream &s, const array_view<T> &a)
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
