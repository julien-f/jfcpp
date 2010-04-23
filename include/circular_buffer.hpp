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

#ifndef H_CIRCULAR_BUFFER
#define H_CIRCULAR_BUFFER

#include <stdexcept>

#include <contracts.h>

/**
 * This class is an implementation of a circular buffer.
 *
 * A circular buffer is a data structure which has the following properties:
 * - fixed capacity;
 * - accessing any elements in constant time;
 * - adding an element at the beginning or at the end in constant time;
 * - removing an element at the beginning or at the end in constant time.
 */
template<typename T>
class circular_buffer : public CertifiedObject
{
public:

	/**
	 * A reference to a constant element.
	 */
	typedef const T& const_reference;

	/**
	 * A reference to an element.
	 */
	typedef T &reference;

	/**
	 * An unsigned integer large-enough to access to any elements stored in this
	 * class.
	 */
	typedef unsigned int size_type;

	/**
	 * The type of elements stored in this class.
	 */
	typedef T value_type;

	/**
	 * Constructs a new circular buffer.
	 *
	 * @param capacity The number of items the buffer can contain (strictly
	 *                 greater than 0).
	 */
	circular_buffer(size_type capacity);

	/**
	 * Destructs a circular buffer.
	 */
	~circular_buffer();


	/**
	 * A const iterator for the circular buffer.
	 */
	class const_iterator;

	/**
	 * Returns the element at the @index position.
	 *
	 * @throw std::out_of_range If @index is not valid.
	 *
	 * @param index The position of the element.
	 *
	 * @return A reference to the element at the @index position.
	 */
	reference at(size_type index);

	/**
	 * Returns the element at the @index position.
	 *
	 * @throw std::out_of_range If @index is not valid.
	 *
	 * @param index The position of the element.
	 *
	 * @return A constant reference to the element at the @index position.
	 */
	const_reference at(size_type index) const;

	/**
	 * Returns a const iterator to the begin of the circular buffer.
	 */
	const_iterator begin() const;

	/**
	 * Returns the capacity of this circular buffer.
	 *
	 * @return The number of elements which can be stored in this buffer.
	 */
	size_type capacity() const;

	/**
	 * Clears the circular buffer, i.e. reduces its size to zero.
	 *
	 * Due to the implementation, the elements are not really deleted, thus
	 * their destructors are not called.
	 */
	void clear();

	/**
	 * Returns whether this buffer is empty.
	 *
	 * @return true is the buffer is empty, false otherwise.
	 */
	size_type empty() const;

	/**
	 * Returns a const iterator to the end of the circular buffer.
	 */
	const_iterator end() const;

	/**
	 * Returns whether this buffer is full.
	 *
	 * @return true is the buffer is full, false otherwise.
	 */
	size_type full() const;

	/**
	 * Returns whether the state of this object is coherent/valid.
	 *
	 * @return true if the state of this object is valid, false otherwise.
	 */
	bool isValid() const;

	/**
	 * Returns the element at the @index position.
	 *
	 * Contrary to the @at(size_type) method, there is no error checking, @index
	 * must be valid or the behaviour is undefined.
	 *
	 * @param index The position of the element.
	 *
	 * @return A reference to the element at the @index position.
	 */
	reference operator[](size_type index);

	/**
	 * Returns the element at the @index position.
	 *
	 * Contrary to the @at(size_type) method, there is no error checking, @index
	 * must be valid or the behaviour is undefined.
	 *
	 * @param index The position of the element.
	 *
	 * @return A constant reference to the element at the @index position.
	 */
	const_reference operator[](size_type index) const;

	/**
	 * Removes the last element of the circular buffer.
	 *
	 * The buffer must not be empty.
	 *
	 * Due to the implementation, the element is not really deleted, thus its
	 * destructor is not called.
	 */
	void pop_back();

	/**
	 * Removes the first element of the circular buffer.
	 *
	 * The buffer must not be empty.
	 *
	 * Due to the implementation, the element is not really deleted, thus its
	 * destructor is not called.
	 */
	void  pop_front();

	/**
	 * Adds a new element at the end of this buffer.
	 *
	 * If the buffer is full, the first element will be removed.
	 *
	 * @param item The item to be added.
	 */
	void push_back(const_reference item);

	/**
	 * Adds a new element at the beginning of this buffer.
	 *
	 * If the buffer is full, the last element will be removed.
	 *
	 * @param item The item to be added.
	 */
	void push_front(const_reference item);

	/**
	 * Returns the size of this circular buffer.
	 *
	 * @return The number of elements currently stored is this buffer.
	 */
	size_type size() const;

private:

	/**
	 * This array contains the data.
	 */
	T *_buffer;

	/**
	 * The capacity of @_buffer, i.e. the number of items which can be stored.
	 */
	size_type _capacity;

	/**
	 * The number of items currently in @_buffer.
	 */
	size_type _size;

	/**
	 * The index in @_buffer from which the items are placed.
	 */
	size_type _start;

	/**
	 * Returns the real index in @_buffer of an element from the logical index
	 * @index.
	 *
	 * @index must be valid for @_buffer but does not have to correspond to an
	 * element.
	 *
	 * @param index The logical index.
	 *
	 * @return A valid index for @_buffer.
	 */
	size_type real_index(size_type index) const;

	/**
	 *
	 */
	void shift_left(size_type &index, size_type offset) const;

	/**
	 *
	 */
	void shift_right(size_type &index, size_type offset) const;
};

#include "circular_buffer/const_iterator.hpp"

#include "circular_buffer/implementation.hpp"

#endif // H_CIRCULAR_BUFFER

