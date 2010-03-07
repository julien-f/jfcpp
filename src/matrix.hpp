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

#ifndef H_MATRIX
#define H_MATRIX

#include <cstddef>
#include <ostream>
#include <stdexcept>

#include "contracts.h"

/**
 *
 *
 * General requirements:
 * - T must have a default constructor;
 * - the method “T &T::operator=(const T &)” must be defined.
 */
template<typename T>
class matrix : private CertifiedObject
{
public:

	/**
	 * Constructs a square matrix with a given dimension.
	 *
	 * The values inside it are constructed using T's default constructor.
	 *
	 * @param dim The number of rows and columns.
	 */
	matrix(size_t dim = 0);

	/**
	 * Constructs a matrix with given dimensions.
	 *
	 * The values inside it are constructed using T's default constructor.
	 *
	 * @param rows    The number of rows.
	 * @param columns The number of columns.
	 */
	matrix(size_t rows, size_t columns);

	/**
	 * Constructs a matrix with given dimensions and initializes each cell with
	 * a given value.
	 *
	 * @param rows    The number of rows.
	 * @param columns The number of columns.
	 * @param value   The initial value.
	 */
	matrix(size_t rows, size_t columns, const T &value);

	/**
	 * Constructs a matrix from another.
	 *
	 * @param m The matrix.
	 */
	matrix(const matrix<T> &m);

	/**
	 *
	 */
	~matrix();

	/**
	 * Gets the item contained at the specified position.
	 *
	 * @param i The row.
	 * @param j The column.
	 *
	 * @throw std::out_of_range If this subscript is not valid.
	 *
	 * @return The item contained at the specified position.
	 */
	T &at(size_t i, size_t j);

	/**
	 * Gets the item contained at the specified position.
	 *
	 * @param i The row.
	 * @param j The column.
	 *
	 * @throw std::out_of_range If this subscript is not valid.
	 *
	 * @return The item contained at the specified position.
	 */
	const T &at(size_t i, size_t j) const;

	/**
	 * Gets the number of columns of this matrix.
	 *
	 * @return The number of columns of this matrix.
	 */
	size_t columns() const;

	/**
	 * Fills this matrix with “value”.
	 *
	 * @param value
	 */
	void fill(const T &value);

	/**
	 * Tests whether this matrix and “m” have same dimensions (i.e. number of
	 * rows and columns).
	 *
	 * @param m
	 *
	 * @return Whether they have same dimensions.
	 */
	template<typename U>
	bool has_same_dimensions(const matrix<U> &m) const;

	/**
	 * Tests whether this matrix is square (i.e. has the same number of rows
	 * than columns).
	 *
	 * @return Whether this matrix is square.
	 */
	bool is_square() const;

	/**
	 *
	 *
	 * @param i
	 * @param j
	 *
	 * @return Whether this matrix is square.
	 */
	bool is_valid_subscript(size_t i, size_t j) const;

	/**
	 * Gets the number of rows of this matrix.
	 *
	 * @return The number of rows of this matrix.
	 */
	size_t rows() const;

	/**
	 * Gets the size of this matrix, i.e. the number of contained items.
	 *
	 * The returned value equals to columns * rows.
	 *
	 * @return The size of this matrix.
	 */
	size_t size() const;

	/**
	 * Computes the trace of this matrix, i.e. the sum of the elements which are
	 * on the diagonal.
	 *
	 * Requirements:
	 * - this matrix must be square;
	 * - the method “R &R::operator+=(const T &)” must be defined.
	 *
	 * @template R The type of the result.
	 *
	 * @return The trace of this matrix.
	 */
	template<typename R>
	R trace() const;

	/**
	 * Computes the transpose of this matrix.
	 *
	 * @return The transpose.
	 */
	matrix<T> transpose() const;

	/**
	 *
	 */
	matrix<T> &operator=(const matrix<T> &m);

	/**
	 *
	 */
	bool operator==(const matrix<T> &m) const;

	/**
	 *
	 */
	bool operator!=(const matrix<T> &m) const;

	/**
	 *
	 * Requirements:
	 * - the method “T &T::operator+=(const T &)” must be defined;
	 * - the function “T operator*(const T &, const T &)” must be defined.
	 */
	matrix<T> operator*(const matrix<T> &m) const;

	/**
	 *
	 * Requirements:
	 * - the method “T &T::operator+=(const T &)” must be defined;
	 * - the function “T operator*(const T &, const T &)” must be defined.
	 */
	matrix<T> &operator*=(const matrix<T> &m);

	/**
	 * Scalar multiplication: multiplies each elements of this matrix by
	 * “value”.
	 *
	 * Requirement:
	 * - the function “T operator*(const T &, const T &)” must be defined.
	 *
	 * @param value A value by which every elements of this matrix will be
	 *              multiplied.
	 *
	 * @return The result of this operation.
	 */
	matrix<T> operator*(const T &value) const;

	/**
	 * Scalar multiplication: multiplies each elements of this matrix by
	 * “value”.
	 *
	 * Requirement:
	 * - the function “T operator*(const T &, const T &)” must be defined.
	 *
	 * @param value A value by which every elements of this matrix will be
	 *              multiplied.
	 *
	 * @return This matrix.
	 */
	matrix<T> &operator*=(const T &value);

	/**
	 *
	 * Requirement:
	 * - the method “R &R::operator+=(const T &)” must be defined.
	 */
	matrix<T> operator+(const matrix<T> &m) const;

	/**
	 *
	 * Requirement:
	 * - the method “R &R::operator+=(const T &)” must be defined.
	 */
	matrix<T> &operator+=(const matrix<T> &m);

	/**
	 * Gets the item contained at the specified position.
	 *
	 * Contrary to the at(size_t, size_t) method, there is not range checking.
	 *
	 * @param i The row.
	 * @param j The column.
	 *
	 * @return The item contained at the specified position.
	 */
	T &operator()(size_t i, size_t j);

	/**
	 * Gets the item contained at the specified position.
	 *
	 * Contrary to the at(size_t, size_t) method, there is not range checking.
	 *
	 * @param i The row.
	 * @param j The column.
	 *
	 * @return The item contained at the specified position.
	 */
	const T &operator()(size_t i, size_t j) const;

private:

	/**
	 *
	 */
	size_t _rows;

	/**
	 *
	 */
	size_t _columns;

	/**
	 *
	 */
	size_t _size;

	/**
	 *
	 */
	T *values;

	/**
	 *
	 */
	T **values_by_rows;

	/**
	 *
	 */
	void allocate();

	/**
	 * Checks if this matrix's values and m's are equal.
	 *
	 * @param The matrix (must have the same dimension than this matrix).
	 *
	 * @return True if they are, otherwise false.
	 */
	bool compare_values(const matrix<T> &m) const;

	/**
	 * Sets the values of this matrix with the values of 'm'.
	 *
	 * @param The matrix (must have the same dimension than this matrix).
	 */
	void copy_values(const matrix<T> &m);

	/**
	 *
	 *
	 * This method does not garantee a coherent state.
	 */
	void deallocate();

	/**
	 * @see CertifiedObject::isValid() const
	 */
	virtual bool isValid() const;

	/**
	 *
	 */
	void resize(size_t rows, size_t columns);
};

/**
 *
 */
template<typename T>
matrix<T>
operator*(const T &value, const matrix<T> &m);

/**
 *
 */
template<typename T>
std::ostream &
operator<<(std::ostream &os, const matrix<T> &m);


// Implementations.


template<typename T> inline
matrix<T>::matrix(size_t dim)
	: _rows(dim), _columns(dim), _size(dim * dim), values(NULL),
	  values_by_rows(NULL)
{
	this->allocate();

	ensures(this->is_square());
}

template<typename T> inline
matrix<T>::matrix(size_t rows, size_t columns)
	: _rows(rows), _columns(columns), _size(rows * columns), values(NULL),
	  values_by_rows(NULL)
{
	this->allocate();
}

template<typename T> inline
matrix<T>::matrix(size_t rows, size_t columns, const T &value)
	: _rows(rows), _columns(columns), _size(rows * columns), values(NULL),
	  values_by_rows(NULL)
{
	this->allocate();

	this->fill(value);
}

template<typename T> inline
matrix<T>::matrix(const matrix<T> &m)
	: _rows(m._rows), _columns(m._columns), _size(m._size), values(NULL),
	  values_by_rows(NULL)
{
	this->allocate();

	this->copy_values(m);
}

template<typename T>
matrix<T>::~matrix()
{
	this->deallocate();
}

template<typename T> inline
T &
matrix<T>::at(size_t i, size_t j)
{
	if (!this->is_valid_subscript(i, j))
	{
		throw std::out_of_range("No such index");
	}

	return (*this)(i, j);
}

template<typename T> inline
const T &
matrix<T>::at(size_t i, size_t j) const
{
	// Reuse the implementation of at(size_t, size_t).
	return const_cast<matrix<T> *>(this)->at(i, j);
}

template<typename T> inline
size_t
matrix<T>::columns() const
{
	return this->_columns;
}

template<typename T> inline
void
matrix<T>::fill(const T &value)
{
	std::fill(this->values, this->values + this->_size, value);
}

template<typename T>
template<typename U> inline
bool
matrix<T>::has_same_dimensions(const matrix<U> &m) const
{
	return ((this->_rows == m._rows) && (this->_columns == m._columns));
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
	return (this->has_same_dimensions(m) && this->compare_values(m));
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
matrix<T>::operator*(const T &value) const
{
	matrix<T> result(*this);

	result *= value;

	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator*=(const T &value)
{
	for (size_t i = 0; i < this->_size; ++i)
	{
		this->values[i] *= value;
	}

	return *this;
}

template<typename T> inline
matrix<T>
matrix<T>::operator+(const matrix<T> &m) const
{
	matrix<T> result(*this);

	result += m;

	return result;
}

template<typename T> inline
matrix<T> &
matrix<T>::operator+=(const matrix<T> &m)
{
	requires(this->has_same_dimensions(m));

	for (size_t i = 0; i < this->_size; ++i)
	{
		this->values[i] += m.values[i];
	}

	return *this;
}

template<typename T> inline
T &
matrix<T>::operator()(size_t i, size_t j)
{
	requires(this->is_valid_subscript(i, j));

	return this->values_by_rows[i][j];
}

template<typename T> inline
const T &
matrix<T>::operator()(size_t i, size_t j) const
{
	// Reuse the implementation of operator()(size_t, size_t).
	return (*const_cast<matrix<T> *>(this))(i, j);
}

template<typename T> inline
void
matrix<T>::allocate()
{
	requires(this->values == NULL);

	assert(this->_size == (this->_rows * this->_columns));
	assert(this->values_by_rows == NULL);

	this->values = new T[this->_size];
	this->values_by_rows = new T*[this->_rows];

	T *p = this->values;
	for (size_t i = 0; i < this->_rows; ++i, p += this->_columns)
	{
		this->values_by_rows[i] = p;
	}

	validate(*this);
}

template<typename T> inline
bool
matrix<T>::compare_values(const matrix<T> &m) const
{
	requires(this->has_same_dimensions(m));

	for (size_t i = 0; i < this->_rows; ++i)
	{
		for (size_t j = 0; j < this->_columns; ++j)
		{
			if ((*this)(i, j) != m(i, j))
			{
				return false;
			}
		}
	}

	return true;
}

template<typename T> inline
void
matrix<T>::copy_values(const matrix<T> &m)
{
	requires(this->has_same_dimensions(m));

	std::copy(m.values, m.values + m._size, this->values);

	ensures(*this == m);
}

template<typename T> inline
void
matrix<T>::deallocate()
{
	delete[] this->values_by_rows;
	this->values_by_rows = NULL;

	delete[] this->values;
	this->values = NULL;
}

template<typename T> inline
bool
matrix<T>::isValid() const
{
	return ((this->_size == (this->_rows * this->_columns))
	        && ((this->values != NULL) || (this->_size == 0))
	        && (((this->values == NULL) && (this->values_by_rows == NULL))
	            || ((this->values_by_rows != NULL))));
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

template<typename T> inline
matrix<T>
operator*(const T &value, const matrix<T> &m)
{
	return (m * value);
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

#endif
