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

#include <algorithm>
#include <functional>
#include <ostream>
#include <stdexcept>

#include "contracts.h"

template<typename T>
matrix<T>
matrix<T>::identity(size_t dim, const_reference zero, const_reference one)
{
	matrix<T> id(dim, dim, zero);

	for (size_t i = 0; i < id._rows; ++i)
	{
		id(i, i) = one;
	}

	return id;
}


template<typename T> inline
matrix<T>::matrix(size_t dim)
	: _rows(dim), _columns(dim), _size(dim * dim), _values(NULL),
	  _values_by_rows(NULL)
{
	this->allocate();

	ensures(this->is_square());
}

template<typename T> inline
matrix<T>::matrix(size_t rows, size_t columns)
	: _rows(rows), _columns(columns), _size(rows * columns), _values(NULL),
	  _values_by_rows(NULL)
{
	this->allocate();
}

template<typename T> inline
matrix<T>::matrix(size_t rows, size_t columns, const_reference value)
	: _rows(rows), _columns(columns), _size(rows * columns), _values(NULL),
	  _values_by_rows(NULL)
{
	this->allocate();

	std::fill(this->begin(), this->end(), value);
}

template<typename T> inline
matrix<T>::matrix(const matrix<T> &m)
	: _rows(m._rows), _columns(m._columns), _size(m._size), _values(NULL),
	  _values_by_rows(NULL)
{
	this->allocate();

	this->copy_values(m);

	ensures(*this == m);
}

template<typename T>
matrix<T>::~matrix()
{
	this->deallocate();
}

template<typename T> inline
typename matrix<T>::reference
matrix<T>::at(size_t i, size_t j)
{
	if (!this->is_valid_subscript(i, j))
	{
		throw std::out_of_range("No such index");
	}

	return (*this)(i, j);
}

template<typename T> inline
typename matrix<T>::const_reference
matrix<T>::at(size_t i, size_t j) const
{
	// Reuse the implementation of at(size_t, size_t).
	return const_cast<matrix<T> *>(this)->at(i, j);
}

template<typename T> inline
typename matrix<T>::iterator
matrix<T>::begin()
{
	return this->_values;
}

template<typename T> inline
typename matrix<T>::const_iterator
matrix<T>::begin() const
{
	return const_cast<matrix<T> *>(this)->begin();
}

template<typename T> inline
size_t
matrix<T>::columns() const
{
	return this->_columns;
}

template<typename T> inline
typename matrix<T>::iterator
matrix<T>::end()
{
	return this->_values + this->_size;
}

template<typename T> inline
typename matrix<T>::const_iterator
matrix<T>::end() const
{
	return const_cast<matrix<T> *>(this)->end();
}

template<typename T>
template<typename U> inline
bool
matrix<T>::has_same_dimensions(const matrix<U> &m) const
{
	return ((this->_rows == m._rows) && (this->_columns == m._columns));
}

template<typename T> inline
matrix<T>
matrix<T>::inverse() const
{
	return matrix<T>(*this).inverse_perf();
}

template<typename T> inline
matrix<T>
matrix<T>::inverse_perf()
{
	requires(this->is_square());

	return this->solve_perf(matrix<T>::identity(this->_rows));
}

template<typename T> inline
bool
matrix<T>::is_valid_subscript(size_t i, size_t j) const
{
	return ((i < this->_rows) && (j < this->_columns));
}

template<typename T> inline
bool
matrix<T>::is_square() const
{
	return (this->_rows == this->_columns);
}

template<typename T> inline
std::pair<matrix<T>, matrix<T> >
matrix<T>::lu() const
{
	requires(this->is_square());

	matrix<T> u(*this);
	matrix<T> l(this->_rows, this->_columns);

	for (size_t i = 0; i < this->_rows; ++i)
	{
		for (size_t j = i + 1; j < this->_columns; ++j)
		{
		}
	}
}

template<typename T>
template<class UnaryOperator>
void
matrix<T>::op_column(size_t i, size_t j, UnaryOperator op)
{
	requires(i < this->_columns);
	requires(j < this->_columns);

	for (size_t k = 0; k < this->_rows; ++k)
	{
		(*this)(k, j) = op((*this)(k, i));
	}
}

template<typename T>
template<class BinaryOperator>
void
matrix<T>::op_column(size_t i, size_t j, size_t k, BinaryOperator op)
{
	requires(i < this->_columns);
	requires(j < this->_columns);
	requires(k < this->_columns);

	for (size_t l = 0; l < this->_rows; ++l)
	{
		(*this)(l, k) = op((*this)(l, i), (*this)(l, j));
	}
}

template<typename T>
template<class UnaryOperator> inline
void
matrix<T>::op_row(size_t i, size_t j, UnaryOperator op)
{
	requires(i < this->_rows);
	requires(j < this->_rows);

	iterator it = this->_values + this->_columns * i;

	std::transform(it, it + this->_columns, this->_values + this->_columns * j,
	               op);
}

template<typename T>
template<class BinaryOperator> inline
void
matrix<T>::op_row(size_t i, size_t j, size_t k, BinaryOperator op)
{
	requires(i < this->_rows);
	requires(j < this->_rows);
	requires(k < this->_rows);

	iterator it = this->_values + this->_columns * i;

	std::transform(it, it + this->_columns, this->_values + this->_columns * j,
	               this->_values + this->_columns * k, op);
}

template<typename T> inline
size_t
matrix<T>::rows() const
{
	return this->_rows;
}

template<typename T> inline
size_t
matrix<T>::size() const
{
	return this->_size;
}

template<typename T> inline
matrix<T>
matrix<T>::solve(const matrix<T> &B) const
{
	return matrix<T>(*this).solve_perf(B);
}

template<typename T>
matrix<T>
matrix<T>::solve_perf(matrix<T> B)
{
	requires(this->is_square());
	requires(this->_columns == B._rows);

	// Row echelon form.
	for (size_t i = 0; i < this->_rows; ++i)
	{
		T pivot = (*this)(i, i);

		for (size_t j = i + 1; j < this->_rows; ++j)
		{
			my_op op((*this)(j, i) / pivot);

			this->op_row(j, i, j, op);
			B.op_row(j, i, j, op);
		}
	}

	// Gauss-Jordan elimination.
	for (size_t i = this->_rows; i > 0;)
	{
		--i;
		for (size_t j = this->_columns - 1; j > i; --j)
		{
			if ((*this)(i, j) != 0)
			{
				B.op_row(i, j, i, my_op((*this)(i, j)));
			}
		}
		B.op_row(i, i, std::bind2nd(std::divides<T>(), (*this)(i, i)));
	}

	return B;
}

template<typename T> inline
void
matrix<T>::swap(matrix<T> &m)
{
	std::swap(this->_rows, m._rows);
	std::swap(this->_columns, m._columns);
	std::swap(this->_size, m._size);
	std::swap(this->_values, m._values);
	std::swap(this->_values_by_rows, m._values_by_rows);
}

template<typename T> inline
void
matrix<T>::swap_columns(size_t i, size_t j)
{
	requires(i != j);
	requires(i < this->_columns);
	requires(j < this->_columns);

	for (size_t k = 0; k < this->_rows; ++k)
	{
		std::swap((*this)(k, i), (*this)(k, j));
	}
}

template<typename T> inline
void
matrix<T>::swap_rows(size_t i, size_t j)
{
	requires(i != j);
	requires(i < this->_rows);
	requires(j < this->_rows);

	std::swap_ranges(this->_values_by_rows[i],
	                 this->_values_by_rows[i] + this->_columns,
	                 this->_values_by_rows[j]);
}

template<typename T> inline
T
matrix<T>::trace() const
{
	return this->trace<T>();
}

template<typename T>
template<typename R>
R
matrix<T>::trace() const
{
	requires(this->is_square());

	R result = R(); // To correctly initialize simple types.

	for (size_t i = 0; i < this->_rows; ++i)
	{
		result += (*this)(i, i);
	}

	return result;
}

template<typename T>
matrix<T>
matrix<T>::transpose() const
{
	matrix<T> result(this->_columns, this->_rows);

	for (size_t i = 0; i < this->_rows; ++i)
	{
		for (size_t j = 0; j < this->_columns; ++j)
		{
			result(j, i) = (*this)(i, j);
		}
	}

	return result;
}

template<typename T>
matrix<T> &
matrix<T>::operator=(const matrix<T> &m)
{
	this->resize(m._rows, m._columns);

	this->copy_values(m);

	return *this;
}

template<typename T> inline
bool
matrix<T>::operator==(const matrix<T> &m) const
{
	return (this->has_same_dimensions(m) && this->has_same_values(m));
}

template<typename T> inline
bool
matrix<T>::operator!=(const matrix<T> &m) const
{
	return !(*this == m);
}

template<typename T>
matrix<T>
matrix<T>::operator*(const matrix<T> &m) const
{
	requires(this->_columns == m._rows);

	matrix<T> result(this->_rows, m._columns);
	for (size_t i = 0; i < result._rows; ++i)
	{
		for (size_t j = 0; j < result._columns; ++j)
		{
			T tmp = 0;
			for (size_t k = 0; k < this->_columns; ++k)
			{
				tmp += (*this)(i, k) * m(k, j);
			}
			result(i, j) = tmp;
		}
	}
	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator*=(const matrix<T> &m)
{
	return (*this = *this * m);
}

template<typename T> inline
matrix<T>
matrix<T>::operator*(const_reference value) const
{
	matrix<T> result(this->_rows, this->_columns);

	std::transform(this->begin(), this->end(), result.begin(),
	               std::bind1st(std::multiplies<T>(), value));

	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator*=(const_reference value)
{
	std::transform(this->begin(), this->end(), this->begin(),
	               std::bind1st(std::multiplies<T>(), value));

	return *this;
}

template<typename T> inline
matrix<T>
matrix<T>::operator/(const_reference value) const
{
	matrix<T> result(this->_rows, this->_columns);

	std::transform(this->begin(), this->end(), result.begin(),
	               std::bind2nd(std::divides<T>(), value));

	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator/=(const_reference value)
{
	std::transform(this->begin(), this->end(), this->begin(),
	               std::bind2nd(std::divides<T>(), value));

	return *this;
}

template<typename T> inline
matrix<T>
matrix<T>::operator+(const matrix<T> &m) const
{
	matrix<T> result(this->_rows, this->_columns);

	std::transform(this->begin(), this->end(), m.begin(), result.begin(),
	               std::plus<T>());

	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator+=(const matrix<T> &m)
{
	requires(this->has_same_dimensions(m));

	std::transform(this->begin(), this->end(), m.begin(), this->begin(),
	               std::plus<T>());

	return *this;
}

template<typename T> inline
matrix<T>
matrix<T>::operator+(const_reference value) const
{
	matrix<T> result(this->_rows, this->_columns);

	std::transform(this->begin(), this->end(), result.begin(),
	               std::bind1st(std::plus<T>(), value));

	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator+=(const_reference value)
{
	std::transform(this->begin(), this->end(), this->begin(),
	               std::bind1st(std::plus<T>(), value));

	return *this;
}

template<typename T> inline
typename matrix<T>::reference
matrix<T>::operator()(size_t i, size_t j)
{
	requires(this->is_valid_subscript(i, j));

	return this->_values_by_rows[i][j];
}

template<typename T> inline
typename matrix<T>::const_reference
matrix<T>::operator()(size_t i, size_t j) const
{
	// Reuse the implementation of operator()(size_t, size_t).
	return (*const_cast<matrix<T> *>(this))(i, j);
}

template<typename T>
void
matrix<T>::allocate()
{
	requires(this->_values == NULL);

	assert(this->_size == (this->_rows * this->_columns));
	assert(this->_values_by_rows == NULL);

	this->_values = new T[this->_size];
	this->_values_by_rows = new T*[this->_rows];

	T *p = this->_values;
	for (size_t i = 0; i < this->_rows; ++i, p += this->_columns)
	{
		this->_values_by_rows[i] = p;
	}

	validate(*this);
}

template<typename T> inline
void
matrix<T>::copy_values(const matrix<T> &m)
{
	requires(this->has_same_dimensions(m));

	std::copy(m.begin(), m.end(), this->begin());

	ensures(this->has_same_values(m));
}

template<typename T> inline
void
matrix<T>::deallocate()
{
	delete[] this->_values_by_rows;
	this->_values_by_rows = NULL;

	delete[] this->_values;
	this->_values = NULL;
}

template<typename T> inline
bool
matrix<T>::has_same_values(const matrix<T> &m) const
{
	requires(this->has_same_dimensions(m));

	return std::equal(this->begin(), this->end(), m.begin());
}

template<typename T>
bool
matrix<T>::isValid() const
{
	return ((this->_size == (this->_rows * this->_columns))
	        && ((this->_values != NULL) || (this->_size == 0))
	        && (((this->_values == NULL) && (this->_values_by_rows == NULL))
	            || ((this->_values_by_rows != NULL))));
}

template<typename T> inline
void
matrix<T>::resize(size_t rows, size_t columns)
{
	this->deallocate();

	this->_rows = rows;
	this->_columns = columns;

	this->_size = this->_rows * this->_columns;

	this->allocate();

	validate(*this);
}

template<typename T>
std::ostream &
operator<<(std::ostream &os, const matrix<T> &m)
{
	if ((m.rows() == 0) || (m.columns() == 0))
	{
		return os;
	}

	for (size_t i = 0; i < m.rows(); ++i)
	{
		size_t j = 0;
		for (size_t n = m.columns() - 1; j < n; ++j)
		{
			os << m(i, j) << '\t';
		}
		os << m(i, j) << std::endl;
	}

	return os;
}
