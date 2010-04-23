#ifndef H_MATH_INTERPOLATION
#define H_MATH_INTERPOLATION

namespace interpolation
{
	/**
	 * Linear interpolation.
	 *
	 * @template TCD The type of the function's codomain.
	 * @template TD  The type of the function's domain.
	 */
	template <typename TCD, typename TD = TCD>
	class linear
	{
	public:

		/**
		 *
		 *
		 * @param y0
		 * @param y1
		 */
		linear(TCD y0, TCD y1);

		/**
		 *
		 *
		 * @param x0
		 * @param y0
		 * @param x1
		 * @param y1
		 */
		linear(TCD x0, TCD y0, const TCD &x1, TCD y1);

		/**
		 *
		 *
		 * @param x
		 */
		TCD operator()(const TD &x);

	private:

		TCD _a;

		TCD _b;
	};

	/**
	 * Hermite interpolation.
	 *
	 * @template TCD The type of the function's codomain.
	 * @template TD  The type of the function's domain.
	 */
	template <typename TCD, typename TD = TCD>
	class hermite
	{
	public:

		/**
		 *
		 *
		 * @param y0
		 * @param dy0
		 * @param y1
		 * @param dy1
		 */
		hermite(TCD y0, TCD dy0, TCD y1, const TCD &dy1);

		/**
		 *
		 *
		 * @param x
		 */
		TCD operator()(const TD &x);

	private:

		TCD _a;

		TCD _b;

		TCD _c;

		TCD _d;
	};

#	include "interpolation/implementation.hpp"
} // namespace interpolation

#endif // H_MATH_INTERPOLATION
