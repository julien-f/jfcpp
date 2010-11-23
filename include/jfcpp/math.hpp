/**
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Julien Fontanet <julien.fontanet@isonoe.net>
 */

#ifndef H_JFCPP_MATH
#define H_JFCPP_MATH

#include <contracts.h>

#include "array.hpp"
#include "math/common.hpp"

JFCPP_MATH_NAMESPACE_BEGIN

/**
 *
 *
 * From the GNU C Library.
 */
static const double
	PI_2 = 1.57079632679489661923,
	PI_4 = 0.78539816339744830962,
	PI = 3.14159265358979323846,
	PI_TIMES_2 = 6.28318530717958647692,
	PI_TIMES_4 = 12.56637061435917295384;

/**
 *
 */
static const double
	rad2deg = 180 * 113 / 355.0,
	deg2rad = 355.0 / (180 * 113);

/**
 *
 */
template <typename T>
T
abs(const T &x);

/**
 *
 */
template <typename T>
T
exp_mod(const T &x, const T &k, const T &n);

/**
 *
 */
template <typename T>
T
gcd(const T &a, const T &b);

/**
 *
 */
template <typename T>
T
inverse_mod(const T &x, const T &n);

/**
 *
 */
template <typename T>
bool
is_even(const T &x);

/**
 *
 */
template <typename T>
bool
is_odd(const T &x);

/**
 *
 */
template <typename T>
T
lcm(const T &a, const T &b);

/**
 *
 */
template <typename T, size_t S>
T
norm_1(const array<T, S> &v);

/**
 *
 */
template <typename T, size_t S>
T
norm_2(const array<T, S> &v);

/**
 * Computes numerically the derivativate at 'x' using the values x₋₂, x₋₁, x,
 * x₊₁ and x₊₂.
 *
 * @param dt
 * @param xm2
 * @param xm1
 * @param x
 * @param xp1
 * @param xp2
 *
 * @requires dt != 0
 */
template <typename TD, typename TCD>
TCD
numerical_derivate(TD dt, const TCD &xm2, const TCD &xm1, const TCD &,
                   TCD xp1, const TCD &xp2);

/**
 * Scalar product (or dot product).
 */
template <typename T, size_t S1, size_t S2>
T
sprod(const array<T, S1> &u, const array<T, S2> &v);

/**
 * Square.
 */
template <typename T>
T
square(T a);

/**
 * Vectorial product (or cross product).
 */
template <typename T, size_t S1, size_t S2>
array<T, 3>
vprod(const array<T, S1> &u, const array<T, S2> &v);

JFCPP_MATH_NAMESPACE_END

#include "math/implementation.hpp"

#endif // H_JFCPP_MATH
