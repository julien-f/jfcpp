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
#include <iterator>
#include <utility>

#include <contracts.h>

#include "operators.hpp"

namespace matrix_details
{
	template <typename T>
	class column_iterator;

	template <typename T>
	class const_column_iterator;
}

/**
 *
 *
 * General requirements:
 * - T must have a default constructor;
 * - the method “T &T::operator=(const T &)” must be defined.
 */
template <typename T = double>
class matrix : public operators::addable<matrix<T> >,
               public operators::dividable<matrix<T> >,
               public operators::equality_comparable<matrix<T> >,
               public operators::modable<matrix<T> >,
               public operators::multipliable<matrix<T> >,
               public operators::subtractable<matrix<T> >
{
public:

	/**
	 *
	 */
	typedef const T *const_iterator;

	/**
	 *
	 */
	typedef const T &const_reference;

	/**
	 *
	 */
	typedef T *iterator;

	/**
	 *
	 */
	typedef T &reference;

	/**
	 *
	 */
	typedef std::reverse_iterator<iterator> reverse_iterator;

	/**
	 *
	 */
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	/**
	 *
	 */
	typedef T value_type;

	/**
	 *
	 */
	typedef matrix_details::column_iterator<T> column_iterator;

	/**
	 *
	 */
	typedef matrix_details::const_column_iterator<T> const_column_iterator;

	/**
	 * Constructs the identity matrix for a given dimension.
	 *
	 * Requirement:
	 * - The constructor “T::T(int)” must exists and accepts 0 and 1.
	 *
	 * Calculus complexity: O(dim²).
	 *
	 * @param dim  The number of rows and columns.
	 * @param zero The value which will be used to fill the matrix.
	 * @param one  The value which will be used to fill the matrix's diagonal.
	 */
	static matrix identity(size_t dim, const_reference zero = T(0),
	                       const_reference one = T(1));

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
	matrix(size_t rows, size_t columns, const_reference value);

	/**
	 * Constructs a matrix from another.
	 *
	 * @param m The matrix.
	 *
	 * @ensures *this == m
	 */
	matrix(const matrix &m);

	/**
	 * Constructs a matrix from another.
	 *
	 * @param m The matrix.
	 */
	template <typename T2>
	matrix(const matrix<T2> &m);

	/**
	 *
	 */
	~matrix();

	reference at(size_t i);
	const_reference at(size_t i) const;

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
	reference at(size_t i, size_t j);
	const_reference at(size_t i, size_t j) const;

	/**
	 * Gets an iterator referring to the first element in this matrix.
	 *
	 * This iterator iterates line by line.
	 *
	 * @return A random access iterator positioned on the first element.
	 */
	iterator begin();
	const_iterator begin() const;

	/**
	 * Clears the matrix, setting its size to (0, 0).
	 */
	void clear();

	/**
	 * Gets the number of columns of this matrix.
	 *
	 * @return The number of columns of this matrix.
	 */
	size_t columns() const;

	/**
	 * Computes the deteminant of this matrix.
	 *
	 * Requirements:
	 * - This matrix must be square.
	 * - This matrix must not be empty (size = 0).
	 *
	 * /!\ : Currently only works when the dimension is less than 4.
	 */
	T det() const;


	/**
	 * Gets an iterator referring to the past-the-end element in this matrix.
	 *
	 * This iterator iterates line by line.
	 *
	 * @return A random access iterator positioned on the past-the-end element.
	 */
	iterator end();
	const_iterator end() const;

	/**
	 * Tests whether this matrix and “m” have same dimensions (i.e. number of
	 * rows and columns).
	 *
	 * @param m
	 *
	 * @return Whether they have same dimensions.
	 */
	template <typename T2>
	bool has_same_dimensions(const matrix<T2> &m) const;

	/**
	 * Computes the inverse of this matrix.
	 *
	 * To prevent this matrix from being modified, a copy is created, if you
	 * want to avoid this, use the method “inverse_perf()”.
	 *
	 * Requirement:
	 * - This matrix must be square.
	 *
	 * @throw std::runtime_error If this matrix is not invertible.
	 *
	 * @return The inverse.
	 */
	matrix inverse() const;

	/**
	 * Computes the inverse of this matrix.
	 *
	 * Contrary to the method “inverse() const”, this method does not create a
	 * copy of this matrix.
	 *
	 * Requirement:
	 * - This matrix must be square.
	 *
	 * @throw std::runtime_error If this matrix is not invertible.
	 *
	 * @return The inverse.
	 */
	matrix inverse_perf();

	/**
	 * Tests whether this matrix is square (i.e. has the same number of rows
	 * than columns).
	 *
	 * @return Whether this matrix is square.
	 */
	bool is_square() const;

	/**
	 *
	 */
	bool is_valid_column(size_t j) const;

	/**
	 *
	 */
	bool is_valid_row(size_t i) const;

	/**
	 * Checks if (i, j) is a valid subscript for this matrix.
	 *
	 * @param i The row's index.
	 * @param j The column's index.
	 *
	 * @return Whether this subscript (row/column indexes) are valid.
	 */
	bool is_valid_subscript(size_t i, size_t j) const;

	/**
	 * Matrix product.
	 *
	 * Requirements:
	 * - the method “T &T::operator+=(const T &)” must be defined;
	 * - the function “T operator*(const T &, const T &)” must be defined.
	 */
	template <typename T2>
	matrix mprod(const matrix<T2> &m) const;

	/**
	 * Applies an operation to the column i and store it in the column j.
	 *
	 * @param i  The input column's index (must be less than the number of
	 *           columns).
	 * @param j  The output column's index (must be less than the number of
	 *           columns).
	 * @param op The operation to apply.
	 */
	template<class UnaryOperator>
	void op_column(size_t i, size_t j, UnaryOperator op);

	/**
	 * Applies a binary operation to the columns i and j and store it in the
	 * column k.
	 *
	 * @param i  The first input column's index (must be less than the number of
	 *           columns).
	 * @param j  The second input column's index (must be less than the number
	 *           of columns).
	 * @param k  The output column's index (must be less than the number of
	 *           columns).
	 * @param op The operation to apply.
	 */
	template<class BinaryOperator>
	void op_column(size_t i, size_t j, size_t k, BinaryOperator op);


	/**
	 * Applies an operation to the row i and store it in the row j.
	 *
	 * @param i  The input row's index (must be less than the number of rows).
	 * @param j  The output row's index (must be less than the number of rows).
	 * @param op The operation to apply.
	 */
	template<class UnaryOperator>
	void op_row(size_t i, size_t j, UnaryOperator op);

	/**
	 * Applies a binary operation to the rows i and j and store it in the row k.
	 *
	 * @param i  The first input row's index (must be less than the number of
	 *           rows).
	 * @param j  The second input row's index (must be less than the number of
	 *           rows).
	 * @param k  The output row's index (must be less than the number of rows).
	 * @param op The operation to apply.
	 */
	template<class BinaryOperator>
	void op_row(size_t i, size_t j, size_t k, BinaryOperator op);

	/**
	 *
	 */
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;

	/**
	 *
	 */
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	/**
	 * Resizes the matrix (the previous content is discarded !).
	 */
	void resize(size_t rows, size_t columns);

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
	 * Solves the following equations where A is this matrix and X the solution:
	 * A * X = B.
	 *
	 * To prevent this matrix from being modified, a copy is created, if you
	 * want to avoid this, use the method “solve_perf(matrix)”.
	 *
	 * @throw std::runtime_error If there is no solutions.
	 *
	 * @param B
	 *
	 * @return The matrix X.
	 */
	void solve(matrix &B) const;

	/**
	 * Solves the following equations where A is this matrix and X the solution:
	 * A * X = B.
	 *
	 * Contrary to the method “solve(matrix) const”, this method does not create a
	 * copy of this matrix.
	 *
	 * @throw std::runtime_error If there is no solutions.
	 *
	 * @param B
	 *
	 * @return The matrix X.
	 */
	void solve_perf(matrix &B);

	/**
	 * Swaps the content between this matrix and another.
	 *
	 * Calculus complexity: O(1)
	 *
	 * @return m The other matrix.
	 */
	void swap(matrix &m);

	/**
	 * Swaps two columns of this matrix.
	 *
	 * Calculus complexity: O(number of rows).
	 *
	 * @param i The first column's index.
	 * @param j The second column's index.
	 */
	void swap_columns(size_t i, size_t j);

	/**
	 * Swaps two rows of this matrix.
	 *
	 * Calculus complexity: O(number of columns).
	 *
	 * @param i The first row's index.
	 * @param j The second row's index.
	 */
	void swap_rows(size_t i, size_t j);

	/**
	 * Computes the trace of this matrix, i.e. the sum of the elements which are
	 * on the diagonal.
	 *
	 * Requirements:
	 * - this matrix must be square;
	 * - the method “T2 &T2::operator+=(const T &)” must be defined.
	 *
	 * @template T2 The type of the result.
	 *
	 * @return The trace of this matrix.
	 */
	template <typename T2>
	T2 trace() const;

	/**
	 * @see trace<T2>() const
	 */
	T trace() const;

	/**
	 * Computes the transpose of this matrix.
	 *
	 * @return The transpose.
	 */
	matrix transpose() const;

	/**
	 *
	 */
	template <typename T2>
	bool operator==(const matrix<T2> &m) const;

	/**
	 *
	 *
	 * @param m
	 *
	 * @ensures *this == m
	 */
	matrix &operator=(const matrix &m);

	/**
	 *
	 */
	template <typename T2>
	matrix &operator=(const matrix<T2> &m);

	/**
	 * Element-wise arithmetics operations.
	 */
	template <typename T2>
	matrix &operator+=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator-=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator*=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator/=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator%=(const matrix<T2> &m);

	/**
	 * Element-wise bitwise operations.
	 */
	template <typename T2>
	matrix &operator&=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator|=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator<<=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator>>=(const matrix<T2> &m);
	template <typename T2>
	matrix &operator^=(const matrix<T2> &m);

	/**
	 * Fills the matrix with a scalar value.
	 */
	template <typename T2>
	matrix &operator=(const T2 &s);

	/**
	 * Scalar arithmetics operations.
	 */
	template <typename T2>
	matrix &operator+=(const T2 &value);
	template <typename T2>
	matrix &operator-=(const T2 &value);
	template <typename T2>
	matrix &operator*=(const T2 &value);
	template <typename T2>
	matrix &operator/=(const T2 &value);
	template <typename T2>
	matrix &operator%=(const T2 &value);

	/**
	 * Scalar bitwise operations.
	 */
	template <typename T2>
	matrix &operator&=(const T2 &value);
	template <typename T2>
	matrix &operator|=(const T2 &value);
	template <typename T2>
	matrix &operator<<=(const T2 &value);
	template <typename T2>
	matrix &operator>>=(const T2 &value);
	template <typename T2>
	matrix &operator^=(const T2 &value);

	reference operator()(size_t i);
	const_reference operator()(size_t i) const;

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
	reference operator()(size_t i, size_t j);

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
	const_reference operator()(size_t i, size_t j) const;

private:

	/**
	 * Used in “solve_perf(matrix B)”.
	 */
	class my_op : std::binary_function<const T &, const T &, T>
	{
	public:

		my_op(const T &coeff) : _coeff(coeff)
		{}

		T operator()(const T &a, const T &b)
		{
			return (a - this->_coeff * b);
		}

	private:

		T _coeff;
	};


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
	T *_values;

	/**
	 *
	 */
	T **_values_by_rows;

	/**
	 *
	 */
	void allocate();

	/**
	 * Sets the values of this matrix with the values of 'm'.
	 *
	 * @param The matrix (must have the same dimension than this matrix).
	 *
	 * @ensures *this == m
	 */
	void copy_values(const matrix &m);

	/**
	 * Sets the values of this matrix with the values of 'm'.
	 *
	 * @param The matrix (must have the same dimension than this matrix).
	 */
	template <typename T2>
	void copy_values(const matrix<T2> &m);

	/**
	 *
	 *
	 * This method does not guarantee a coherent state.
	 */
	void deallocate();

	/**
	 * Checks if this matrix's values and m's are equal.
	 *
	 * @param The matrix (must have the same dimension than this matrix).
	 *
	 * @return True if they are, otherwise false.
	 */
	template <typename T2>
	bool has_same_values(const matrix<T2> &m) const;

	/**
	 * Returns whether the current matrix is in a coherent state.
	 *
	 * @returns True if yes, otherwise false.
	 */
	bool isValid() const;
};

/**
 *
 */
template <typename T>
std::ostream &
operator<<(std::ostream &os, const matrix<T> &m);

#include "matrix/column_iterator.hpp"

#include "matrix/const_column_iterator.hpp"

#include "matrix/implementation.hpp"

#endif
