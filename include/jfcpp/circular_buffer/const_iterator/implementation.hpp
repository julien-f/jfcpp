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

#include <contracts.h>

#include "../../common.hpp"

JFCPP_NAMESPACE_BEGIN

template<typename T>
circular_buffer<T>::const_iterator::const_iterator(size_type iteration,
                                                   const circular_buffer<T> *cbuffer)
	: _cbuffer(cbuffer), _iteration(iteration)
{
	requires(this->_cbuffer != NULL);
	requires(this->_iteration <= this->_cbuffer->size());
}

template<typename T> inline
typename circular_buffer<T>::const_iterator &
circular_buffer<T>::const_iterator::operator++()
{
	requires(this != this->_cbuffer->end());
	this->_iteration++;
	return this;
}

template<typename T> inline
typename circular_buffer<T>::const_iterator
circular_buffer<T>::const_iterator::operator++(int)
{
	requires(this != this->_cbuffer->end());
	return const_iterator(this->_iteration++, this->_cbuffer);
}

template<typename T> inline
typename circular_buffer<T>::const_reference
circular_buffer<T>::const_iterator::operator*() const
{
	return (*this->_cbuffer)[this->_iteration];
}

template<typename T> inline
bool
circular_buffer<T>::const_iterator::operator==(const const_iterator &iterator) const
{
	return ((this->_iteration == iterator._iteration)
	        && (this->_cbuffer == iterator._cbuffer));
}

template<typename T> inline
bool
circular_buffer<T>::const_iterator::operator!=(const const_iterator &iterator) const
{
	return ((this->_iteration != iterator._iteration)
	        || (this->_cbuffer != iterator._cbuffer));
}

JFCPP_NAMESPACE_END
