// To properly test inclusion, the tested file must be the first included.
#include <jfcpp/matrix.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

#include <contracts.h>

using jfcpp::matrix;

struct RandomGenerator
{
	template<typename T> static
	void
	fill(matrix<T> &m)
	{
		std::generate(m.begin(), m.end(), RandomGenerator());
	}

	/**
	 * Generates a random integer between 2 and 100.
	 */
	unsigned int
	operator()()
	{
		return ((rand() % 299) + 2);
	}
};

#include <iostream>

int main()
{
	// Ordinary matrix.
	{
		const size_t rows = 5;
		const size_t columns = 6;

		matrix<int> m(rows, columns);

		assert(!m.is_square());
		assert(m.rows() == rows);
		assert(m.columns() == columns);
		assert(m.size() == (rows * columns));

		// matrix<T>::has_same_dimensions(const matrix<T> &m) const
		{
			// Same dimensions.
			matrix<int> m1(m.rows(), m.columns());
			assert(m1.has_same_dimensions(m));
			assert(m.has_same_dimensions(m1));

			// Same number of rows.
			matrix<int> m2(m.rows(), rand() % 50);
			assert(!m2.has_same_dimensions(m));
			assert(!m.has_same_dimensions(m2));

			// Same number of columns.
			matrix<int> m3(rand() % 50, m.columns());
			assert(!m3.has_same_dimensions(m));
			assert(!m.has_same_dimensions(m3));

			// Same size.
			matrix<int> m4(m.columns(), m.rows());
			assert(!m4.has_same_dimensions(m));
			assert(!m.has_same_dimensions(m4));
		}

		assert(m.is_valid_subscript(0, 0));
		assert(!m.is_valid_subscript(m.rows(), m.columns()));

		assert_exception(m.at(m.rows(), m.columns()), std::out_of_range);
		assert_exception(m(m.rows(), m.columns()), ContractViolated);

		m.at(0, 0) = 1;
		assert(m(0, 0) == 1); // Crossed checking.

		m(1, 0) = 2;
		assert(m.at(1, 0) == 2); // Crossed checking.

		assert_exception(m.trace<unsigned int>(), ContractViolated);

		// Fills the matrix with random values.
		RandomGenerator::fill(m);

		// Iterators
		{
			matrix<int>::const_iterator
				it = m.begin(),
				end = m.end();
			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(it != end);
					assert(m(i, j) == *it);
					++it;
				}
			}
			assert(it == end);
		}
		{
			matrix<int>::const_iterator
				it = m.begin(),
				end = m.end();
			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(it != end);
					assert(m(i, j) == *it);
					++it;
				}
			}
			assert(it == end);
		}
		{
			matrix<int>::column_iterator
				it = m.cbegin(),
				end = m.cend();
			for (size_t j = 0; j < m.columns(); ++j)
			{
				for (size_t i = 0; i < m.rows(); ++i)
				{
					assert(it != end);
					assert(m(i, j) == *it);
					++it;
				}
			}
			assert(it == end);
		}
		{
			matrix<int>::const_column_iterator
				it = m.cbegin(),
				end = m.cend();
			for (size_t j = 0; j < m.columns(); ++j)
			{
				for (size_t i = 0; i < m.rows(); ++i)
				{
					assert(it != end);
					assert(m(i, j) == *it);
					++it;
				}
			}
			assert(it == end);
		}

		// Default constructor + affectation + equality.
		{
			matrix<int> a;

			assert(a.is_square());
			assert(a.rows() == 0);
			assert(a.columns() == 0);
			assert(a.size() == 0);
			assert(!a.is_valid_subscript(0, 0));

			a = m;

			assert(a.rows() == m.rows());
			assert(a.columns() == m.columns());
			assert(a.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(a(i, j) == m(i, j));
				}
			}

			// Equality
			assert(a == m);
			assert(!(a != m));
		}

		// Copy constructor
		{
			matrix<int> c(m);

			assert(c.rows() == m.rows());
			assert(c.columns() == m.columns());
			assert(c.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(c(i, j) == m(i, j));
				}
			}
		}

		// Transpose
		{
			matrix<int> t(m.transpose());

			assert(t.rows() == m.columns());
			assert(t.columns() == m.rows());
			assert(!t.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(t(j, i) == m(i, j));
				}
			}
		}

		// Scalar multiplication
		{
			int value = RandomGenerator()();
			matrix<int> p(m * value);

			assert(p.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(p(i, j) == (m(i, j) * value));
				}
			}

			// Inequality
			assert(p != m);
		}
		// Scalar subtraction
		{
			int value = RandomGenerator()();
			matrix<int> p(m - value);

			assert(p.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(p(i, j) == (m(i, j) - value));
				}
			}
		}
		// Scalar addition
		{
			int value = RandomGenerator()();
			matrix<int> p(m + value);

			assert(p.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(p(i, j) == (m(i, j) + value));
				}
			}
		}
		// Scalar division
		{
			int value = RandomGenerator()();
			matrix<int> p(m / value);

			assert(p.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(p(i, j) == (m(i, j) / value));
				}
			}
		}

		// Unary operations.
		assert(m == +m);
		assert((matrix<int>(m.rows(), m.columns(), 0) - m) == -m);
		{
			matrix<int> m2(m), m3(++m);
			assert((m2 + 1) == m);
			assert(m3 == m);
		}
		{
			matrix<int> m2(m), m3(--m);
			assert((m2 - 1) == m);
			assert(m3 == m);
		}
		{
			matrix<int> m2(m), m3(m++);
			assert((m2 + 1) == m);
			assert(m3 == m2);
		}
		{
			matrix<int> m2(m), m3(m--);
			assert((m2 - 1) == m);
			assert(m3 == m2);
		}

		// Matrix product
		assert_exception(m.mprod(m), ContractViolated);

		// Addition
		{
			matrix<int> s(m + m);

			assert(s.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(s(i, j) == (2 * m(i, j)));
				}
			}
		}
	}

	// Test on a square matrix.
	{
		matrix<int> m(10);

		RandomGenerator::fill(m);

		assert(m.is_square());
		assert(m.rows() == 10);
		assert(m.columns() == 10);
		assert(m.size() == 100);

		// Matrix product
		{
			matrix<int> p(m.mprod(m));

			assert(p.has_same_dimensions(m));
		}

		// Trace
		{
			unsigned int t = 0;

			for (size_t i = 0; i < m.rows(); ++i)
			{
				t += m(i, i);
			}

			assert(t == m.trace<unsigned int>());
		}
	}

	return EXIT_SUCCESS;
}
