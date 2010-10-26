#ifndef H_JFCPP_MATH_PROJECTION
#define H_JFCPP_MATH_PROJECTION

#include <cstddef>

#include "../array.hpp"
#include "common.hpp"

JFCPP_MATH_NAMESPACE_BEGIN

namespace projection
{
	/**
	 * Computes a oblique projection, a projection along an arbitrary direction.
	 */
	template <typename T, size_t D>
	class oblique
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
		orthogonal(array<value_type, dimension + 1> hyperplan,
		           vector direction);

		/**
		 *
		 */
		vector operator()(const vector &v) const;

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
		orthogonal(array<value_type, dimension + 1> plan);

		/**
		 *
		 */
		vector operator()(const vector &v) const;

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

	/**
	 * Perspective projection: 3D to 2D.
	 */
	template <typename T>
	class perspective
	{
	public:

		/**
		 *
		 */
		typedef T value_type;

		/**
		 *
		 */
		typedef array<value_type, 2> vec2;

		/**
		 *
		 */
		typedef array<value_type, 3> vec3;

		/**
		 *
		 */
		perspective(T e2s);

		/**
		 *
		 */
		vec2 operator()(const vec3 &v) const;

	private:

		/**
		 *
		 */
		const T _e2s;
	};

#	include "projection/implementation.hpp"
} // namespace projection

JFCPP_MATH_NAMESPACE_END

#endif // H_JFCPP_MATH_PROJECTION
