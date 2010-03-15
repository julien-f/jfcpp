#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <stdexcept>

#include "contracts.h"
#include "matrix.hpp"

struct RandomGenerator
{
	RandomGenerator() : seed(1)
	{}

	unsigned short operator()()
	{
		return rand_r(&(this->seed)) % 100;
	}

 private:

	unsigned int seed;
};

int main(void)
{
	// Ordinary matrix.
	{
		matrix<unsigned short> m(10, 5);

		// Fills the matrix with random values.
		std::generate(m.begin(), m.end(), RandomGenerator());

		assert(!m.is_square());
		assert(m.rows() == 10);
		assert(m.columns() == 5);
		assert(m.size() == 50);

		assert(m.is_valid_subscript(0, 0));
		assert(!m.is_valid_subscript(10, 5));

		assert_exception(m.at(10, 5), std::out_of_range);
		assert_exception(m(10, 5), ContractViolated);

		m.at(0, 0) = 1;
		assert(m(0, 0) == 1); // Crossed checking.

		m(1, 0) = 2;
		assert(m.at(1, 0) == 2); // Crossed checking.

		assert_exception(m.trace<unsigned int>(), ContractViolated);

		// Copy constructor
		{
			matrix<unsigned short> c(m);

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

			// Equality
			assert(c == m);
		}

		// Transpose
		{
			matrix<unsigned short> t(m.transpose());

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

		// Multiplication
		assert_exception(m * m, ContractViolated);

		// Scalar multiplication
		{
			matrix<unsigned short> p(m * 2);

			assert(p.has_same_dimensions(m));

			for (size_t i = 0; i < m.rows(); ++i)
			{
				for (size_t j = 0; j < m.columns(); ++j)
				{
					assert(p(i, j) == (2 * m(i, j)));
				}
			}

			// Inequality
			assert(p != m);
		}

		// Addition
		{
			matrix<unsigned short> s(m + m);

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
		matrix<unsigned short> m(10);

		assert(m.is_square());
		assert(m.rows() == 10);
		assert(m.columns() == 10);
		assert(m.size() == 100);

		// Multiplication
		{
			matrix<unsigned short> p(m * m);

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

	return 0;
}
