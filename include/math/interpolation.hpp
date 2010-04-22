#ifndef H_MATH_INTERPOLATION
#define H_MATH_INTERPOLATION

namespace interpolation
{
	/**
	 * Linear interpolation.
	 */
	template <typename T>
	class linear
	{
	public:

		/**
		 *
		 *
		 * @param y0
		 * @param y1
		 */
		linear(T y0, T y1);

		/**
		 *
		 *
		 * @param x0
		 * @param y0
		 * @param x1
		 * @param y1
		 */
		linear(T x0, T y0, const T &x1, T y1);

		/**
		 *
		 *
		 * @param x
		 */
		T operator()(T x);

	private:

		T _a;

		T _b;
	};

	/**
	 * Hermite interpolation.
	 */
	template <typename T>
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
		hermite(T y0, T dy0, T y1, const T &dy1);

		/**
		 *
		 *
		 * @param x
		 */
		T operator()(const T &x);

	private:

		T _a;

		T _b;

		T _c;

		T _d;
	};

#	include "interpolation/implementation.hpp"
} // namespace interpolation

#endif // H_MATH_INTERPOLATION
