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

template<typename T> inline
const_column_iterator<T>::const_column_iterator()
	: _matrix(NULL)
{}

template<typename T> inline
const_column_iterator<T>::const_column_iterator(const column_iterator<T> &it)
	: _matrix(it._matrix), _i(it._i), _j(it._j)
{}

template<typename T> inline
const_column_iterator<T>::const_column_iterator(const const_column_iterator &it)
	: _matrix(it._matrix), _i(it._i), _j(it._j)
{}

template<typename T> inline
const_column_iterator<T>::const_column_iterator(const matrix<T> &m, size_t i,
                                                size_t j)
	: _matrix(&m), _i(i), _j(j)
{}

template<typename T> inline
bool
const_column_iterator<T>::operator==(const const_column_iterator &it) const
{
	return ((_matrix == it._matrix)
	        && (_i == it._i)
	        && (_j == it._j));
}

template<typename T> inline
bool
const_column_iterator<T>::operator!=(const const_column_iterator &it) const
{
	return !(*this == it);
}

template<typename T> inline
const T &
const_column_iterator<T>::operator*() const
{
	return (*(this->_matrix))(this->_i, this->_j);
}

template<typename T> inline
const_column_iterator<T> &
const_column_iterator<T>::operator++()
{
	++(this->_i);
	if (this->_i >= this->_matrix->rows())
	{
		this->_i = 0;
		++(this->_j);
	}

	return *this;
}

template<typename T> inline
const_column_iterator<T>
const_column_iterator<T>::operator++(int)
{
	const_column_iterator it(*this);
	++(*this);
	return it;
}

template<typename T> inline
const T *
const_column_iterator<T>::operator->() const
{
	return &(*(this->_matrix))(this->_i, this->_j);
}
