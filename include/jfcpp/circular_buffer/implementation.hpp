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
 *   Jérémy Jaussaud <jeremy.jaussaud@free.fr>
 */

#include <stdexcept>

#include <contracts.h>

#include "../common.hpp"

JFCPP_NAMESPACE_BEGIN

template<typename T>
circular_buffer<T>::circular_buffer(size_type capacity)
	: _capacity(capacity), _size(0), _start(0)
{
	requires(capacity > 0);

	this->_buffer = new T[_capacity];

	validate(*this);
}

template<typename T>
circular_buffer<T>::~circular_buffer()
{
	delete [] this->_buffer;
}

template<typename T> inline
typename circular_buffer<T>::reference
circular_buffer<T>::at(size_type index)
{
	// Reuse the implementation of at(size_type) const.
	return const_cast<reference>(const_cast<const circular_buffer<T> *>(this)->at(index));
}

template<typename T> inline
typename circular_buffer<T>::const_reference
circular_buffer<T>::at(size_type index) const
{
	if (index >= this->size())
	{
		throw std::out_of_range("No such index");
	}

	// Reuse the implementation of operator[](size_type) const.
	return (*this)[index];
}

template<typename T> inline
typename circular_buffer<T>::const_iterator
circular_buffer<T>::begin() const
{
	return const_iterator(0, this);
}

template<typename T> inline
typename circular_buffer<T>::size_type
circular_buffer<T>::capacity() const
{
	return this->_capacity;
}

template<typename T> inline
void
circular_buffer<T>::clear()
{
	this->_size = 0;

	// For performance reason it is better to reposition _start at the
	// beginning.
	this->_start = 0;

	validate(*this);
}

template<typename T> inline
typename circular_buffer<T>::size_type
circular_buffer<T>::empty() const
{
	return (this->_size == 0);
}

template<typename T> inline
typename circular_buffer<T>::const_iterator
circular_buffer<T>::end() const
{
	return const_iterator(this->_size, this);
}

template<typename T> inline
typename circular_buffer<T>::size_type
circular_buffer<T>::full() const
{
	return (this->_size == this->_capacity);
}

template<typename T>
bool
circular_buffer<T>::isValid() const
{
	return (
	        (this->_buffer != NULL)

	        && (this->_capacity > 0)
	        && (this->_size <= this->_capacity)

	        && (this->_start < this->_capacity)
	        );
}

template<typename T> inline
typename circular_buffer<T>::reference
circular_buffer<T>::operator[](size_type index)
{
	// Reuse the implementation of operator[](size_type) const.
	return const_cast<reference>((*const_cast<const circular_buffer<T> *>(this))[index]);
}

template<typename T> inline
typename circular_buffer<T>::const_reference
circular_buffer<T>::operator[](size_type index) const
{
	requires(index < this->_size);

	return this->_buffer[this->real_index(index)];
}

template<typename T> inline
void
circular_buffer<T>::pop_back()
{
	requires(!this->empty());

	this->_size--;

	validate(*this);
}

template<typename T>
void
circular_buffer<T>::pop_front()
{
	requires(!this->empty());

	this->_size--;

	this->_start++;
	if (this->_start == this->_capacity)
	{
		this->_start = 0;
	}

	validate(*this);
}

template<typename T> inline
void
circular_buffer<T>::push_back(const_reference item)
{
	if (this->full())
	{
		this->_buffer[this->_start] = item;
		this->shift_right(this->_start, 1);
	}
	else
	{
		this->_buffer[this->real_index(this->_size++)] = item;
	}

	validate(*this);
}

template<typename T> inline
void
circular_buffer<T>::push_front(const_reference item)
{
	this->shift_left(this->_start, 1);
	this->_buffer[this->_start] = item;

	if (!this->full())
	{
		this->_size++;
	}

	validate(*this);
}

template<typename T> inline
typename circular_buffer<T>::size_type
circular_buffer<T>::size() const
{
	return this->_size;
}

template<typename T> inline
typename circular_buffer<T>::size_type
circular_buffer<T>::real_index(size_type index) const
{
	requires(index < this->_capacity);

	this->shift_right(index, this->_start);

	return index;
}

template<typename T> inline
void
circular_buffer<T>::shift_left(size_type &index, size_type offset) const
{
	requires(index < this->_capacity);
	requires(offset <= this->_capacity);

	if (index >= offset)
	{
		ensures((index - offset) < this->_capacity);
		index -= offset;
	}
	else
	{
		ensures((index + this->_capacity - offset) < this->_capacity);
		index += (this->_capacity - offset);
	}
}

template<typename T> inline
void
circular_buffer<T>::shift_right(size_type &index, size_type offset) const
{
	requires(index < this->_capacity);
	requires(offset <= this->_capacity);

	index += offset;
	if (index >= this->_capacity)
	{
		index -= this->_capacity;
	}

	ensures(index < this->_capacity);
}

JFCPP_NAMESPACE_END
