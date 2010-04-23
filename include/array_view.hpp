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
#include <iterator>
#include <ostream>

#include <contracts.h>

/**
 * This class is a simple wrapper around a C array which provides helper for
 * copying, comparing and accessing elements.
 *
 * Be careful, this class does not own the memory, it only provides a way to
 * manipulates the data in it, consequently, it will not free the memory when
 * destroyed.
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
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
	typedef std::reverse_iterator<iterator> reverse_iterator;

	/**
	 *
	 */
	typedef value_type *pointer;

	/**
	 *
	 */
	inline array_view(size_t size, pointer raw)
		: _raw(raw), _size(size)
	{
		requires(raw != NULL);
		requires(size != 0);
	}

	/**
	 *
	 */
	inline iterator begin()
	{
		return this->_raw;
	}
	inline const_iterator begin() const
	{
		return this->_raw;
	}

	/**
	 *
	 */
	inline iterator end()
	{
		return (this->_raw + this->_size);
	}
	inline const_iterator end() const
	{
		return (this->_raw + this->_size);
	}

	/**
	 *
	 */
	inline pointer raw()
	{
		return this->_raw;
	}
	inline const_pointer raw() const
	{
		return this->_raw;
	}

	/**
	 *
	 */
	inline reverse_iterator rbegin()
	{
		return reverse_iterator(this->end());
	}
	inline const_reverse_iterator rbegin() const
	{
		return reverse_iterator(this->end());
	}

	/**
	 *
	 */
	inline reverse_iterator rend()
	{
		return reverse_iterator(this->begin());
	}
	inline const_reverse_iterator rend() const
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
	void set(const array_view<T> &ar)
	{
		this->set(ar._size, ar._raw);
	}

	/**
	 *
	 */
	inline size_t size() const
	{
		return this->_size;
	}

	/**
	 *
	 */
	template<typename U> inline
	bool operator==(const array_view<U> &a) const
	{
		return ((this->_size == a.size()) &&
		        std::equal(this->begin(), this->end(), a.begin()));
	}

	/**
	 *
	 */
	template<typename U> inline
	bool operator<(const array_view<U> &a) const
	{
		return std::lexicographical_compare(this->begin(), this->end(),
		                                    a.begin(), a .end());
	}

	/**
	 *
	 */
	template<typename U> inline
	array_view &operator=(const array_view<U> &a)
	{
		requires(this->_size == a.size());

		std::copy(a.begin(), a.end(), this->begin());

		return *this;
	}

	/**
	 *
	 */
	inline reference at(size_t i)
	{
		if (i >= this->size())
		{
			throw std::out_of_range("no such index");
		}

		return (*this)[i];
	}
	inline const_reference at(size_t i) const
	{
		return const_cast<array_view<T> *>(this)->at(i);
	}

	/**
	 *
	 */
	inline reference operator[](size_t i)
	{
		requires(i < this->_size);

		return this->_raw[i];
	}
	inline const_reference operator[](size_t i) const
	{
		return const_cast<array_view<T> &>(*this)[i];
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
	 * Allows to create an array_view on constant values from one on
	 * non-constant values.
	 */
	inline array_view(const array_view<T> &a)
		: _raw(a.raw()), _size(a.size())
	{}

	/**
	 *
	 */
	inline array_view(size_t size, const_pointer raw)
		: _raw(raw), _size(size)
	{
		requires(raw != NULL);
		requires(size != 0);
	}

	/**
	 *
	 */
	inline const_iterator begin() const
	{
		return this->_raw;
	}

	/**
	 *
	 */
	inline const_iterator end() const
	{
		return (this->_raw + this->_size);
	}

	/**
	 *
	 */
	inline const_pointer raw() const
	{
		return this->_raw;
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
	void set(const array_view<T> &ar)
	{
		this->set(ar._size, ar._raw);
	}
	void set(const array_view<const T> &ar)
	{
		this->set(ar._size, ar._raw);
	}

	/**
	 *
	 */
	inline size_t size() const
	{
		return this->_size;
	}

	/**
	 *
	 */
	template<typename U> inline
	bool operator==(const array_view<U> &a) const
	{
		return ((this->_size == a.size()) &&
		        std::equal(this->begin(), this->end(), a.begin()));
	}

	/**
	 *
	 */
	template<typename U> inline
	bool operator<(const array_view<U> &a) const
	{
		return std::lexicographical_compare(this->begin(), this->end(),
		                                    a.begin(), a .end());
	}


	/**
	 *
	 */
	inline const_reference at(size_t i) const
	{
		if (i >= this->_size)
		{
			throw std::out_of_range("no such index");
		}

		return (*this)[i];
	}

	/**
	 *
	 */
	inline const_reference operator[](size_t i) const
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
	inline array_view<const T> &operator=(const array_view<const T> &)
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
std::istream &operator>>(std::istream &s, array_view<T> a)
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

	return s;
}

#endif
