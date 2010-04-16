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
T
lcm(const T &a, const T &b);

#include "math/implementation.hpp"

#endif // H_MATH
