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

#ifndef H_MATH
#define H_MATH

#include <contracts.h>

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

#include "math/implementation.hpp"

#endif // H_MATH
