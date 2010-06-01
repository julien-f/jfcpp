#ifndef H_MATH_PROJECTION
#define H_MATH_PROJECTION

#include <cstddef>

#include <array.hpp>

namespace projection
{
	/**
	 * Computes a orthogonal projection.
	 */
	template <typename T, size_t D>
	class orthogonal
	{
	public:

		/**
		 *
		 */
		typedef T value_type;

		/**
		 *
		 */
		typedef array<value_type, D> vector;

		/**
		 *
		 */
		static const size_t dimension = D;

		/**
		 *
		 */
		orthogonal(array<value_type, dimension + 1> plan) : _plan(plan)
		{
			const value_type zero(0);

			_denominator = 0;

			vector tmp;
			for (size_t i = 0; i < dimension; ++i)
			{
				typename array<value_type, dimension + 1>::const_reference
					current = _plan[i];

				_denominator += tmp[i] = current * current;
			}

			for (size_t i = 0; i < dimension; ++i)
			{
				typename vector::reference current = _squares[i];

				current = zero;
				for (size_t j = 0; j < dimension; ++j)
				{
					if (i != j)
					{
						current += tmp[j];
					}
				}
			}
		}

		/**
		 *
		 */
		vector operator()(const vector &v) const
		{
			vector result(_squares * v);

			vector tmp1(v);
			for (size_t i = 0; i < dimension; ++i)
			{
				tmp1[i] *= _plan[i];
			}

			const value_type last(_plan[dimension]);

			vector tmp2;
			for (size_t i = 0; i < dimension; ++i)
			{
				typename vector::reference current = tmp2[i];

				current = last;
				for (size_t j = 0; j < dimension; ++j)
				{
					if (i != j)
					{
						current += tmp1[j];
					}
				}
				current *= _plan[i];
			}

			result -= tmp2;
			result /= _denominator;

			return result;
		}

	private:

		/**
		 *
		 */
		value_type _denominator;

		/**
		 *
		 */
		const array<value_type, dimension + 1> _plan;

		/**
		 *
		 */
		vector _squares;
	};
} // namespace projection

#endif // H_MATH_PROJECTION
