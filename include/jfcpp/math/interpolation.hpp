#ifndef H_JFCPP_MATH_INTERPOLATION
#define H_JFCPP_MATH_INTERPOLATION

#include "common.hpp"

JFCPP_MATH_NAMESPACE_BEGIN

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
		 * Default constructor.
		 *
		 * /!\: The object is not in a valid state.
		 */
		linear();

		/**
		 *
		 *
		 * @param y0
		 * @param y1
		 */
		linear(const TCD &y0, const TCD &y1);

		/**
		 *
		 *
		 * @param x0
		 * @param y0
		 * @param x1
		 * @param y1
		 */
		linear(const TD &x0, const TCD &y0, const TD &x1, const TCD &y1);

		/**
		 *
		 */
		void
		initialize(const TCD &y0, const TCD &y1);

		/**
		 *
		 */
		void
		initialize(const TD &x0, const TCD &y0, const TD &x1, const TCD &y1);

		/**
		 *
		 */
		linear &
		operator=(const linear &l);

		/**
		 *
		 *
		 * @param x
		 */
		TCD operator()(const TD &x) const;

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
		TCD operator()(const TD &x) const;

	private:

		TCD _a;

		TCD _b;

		TCD _c;

		TCD _d;
	};

	/**
	 * Spherical Linear Interpolation.
	 */
	template <typename Codomain, typename Domain = Codomain,
	          typename Angle = Domain>
	class slerp
	{
	public:

		/**
		 *
		 */
		slerp(Angle angle, Codomain y0, Codomain y1);

		/**
		 *
		 */
		Codomain operator()(const Domain &x) const;

	private:

		/**
		 *
		 */
		Angle _angle;

		/**
		 *
		 */
		Codomain _a;

		/**
		 *
		 */
		Codomain _b;
	};

#	include "interpolation/implementation.hpp"
} // namespace interpolation

JFCPP_MATH_NAMESPACE_END

#endif // H_JFCPP_MATH_INTERPOLATION
