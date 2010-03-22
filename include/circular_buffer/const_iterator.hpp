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

#include "contracts.h"

/**
 * This class is an implementation of a const iterator for class circular_ buffer.
 */
template<typename T>
class circular_buffer<T>::const_iterator
{
public :

	/**
	 * Construct a const iterator for the circular buffer.
	 *
	 * @param iteration is the index of the element that will be accessible through
	 *        the constructed iterator. It mustn't be greater than cbuffer->size().
	 * @param cbuffer is a pointer to the circular buffer the const iterator is
	 *        constructed for.
	 */
	const_iterator(size_type iteration, const circular_buffer<T> *cbuffer);

	/**
	 * Increments a const iterator which doesn't indicate the end of the buffer.
	 *
	 * @return a reference to the const iterator.
	 */
	const_iterator &operator++();

	/**
	 * Increments a const iterator which doesn't indicate the end of the buffer.
	 *
	 * @return the value of the const iterator before its incrementation.
	 */
	const_iterator operator++(int);

	/**
	 * Enables to get access to the element indicated by the const iterator.
	 *
	 * @return a reference to the element indicated by the const iterator.
	 */
	const_reference operator*() const;

	/**
	 * Compares two iterators.
	 *
	 * @return true if the tow iterators indicate the same element of the same
	 *         circular buffer, and false otherwise.
	 */
	bool operator==(const const_iterator &iterator) const;

	/**
	 * Compares two iterators.
	 *
	 * @return false if the tow iterators indicate the same element of the same
	 *         circular buffer, and true otherwise.
	 */
	bool operator!=(const const_iterator &iterator) const;

private :

	/**
	 *
	 */
	const circular_buffer *_cbuffer;

	/**
	 *
	 */
	size_type _iteration;
};

#include "const_iterator/implementation.hpp"
