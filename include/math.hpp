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
template <typename T>
T
numerical_derivate(const T &dt, const T &xm2, const T &xm1, const T &,
                   T xp1, const T &xp2)
{
	// Optimisation: the result is stored in xp1.

	xp1 -= xm1;
	xp1 *= 8;
	xp1 += xm2;
	xp1 -= xp2;
	xp1 /= 12;
	xp1 /= dt;

	return xp1;
}

/**
 * Hermite interpolation.
 */
template <typename T>
class interpolation
{
public:

	interpolation(T da, T a, T db, T b)
		: _a(a), _da(da),
		  _2_amb_p_da_p_db(a), _3_bma_m_2_da_m_db(b)
	{
		_2_amb_p_da_p_db -= b;
		_2_amb_p_da_p_db *= 2;
		_2_amb_p_da_p_db += da;
		_2_amb_p_da_p_db += db;

		_3_bma_m_2_da_m_db -= a;
		_3_bma_m_2_da_m_db *= 3;
		{
			T tmp(da);
			tmp *= 2;
			_3_bma_m_2_da_m_db -= tmp;
		}
		_3_bma_m_2_da_m_db -= db;
	}

	T operator()(const T &t)
	{
		// Base formula:
		// result = (2 * t³ - 3 * t² + 1) * _a
		//          + (t³ - 2 * t² + t) * _da
		//          + (-2 * t³ + 3 * t²) * _b
		//          + (t³ - t²) * _db

		T result(_2_amb_p_da_p_db);
		result *= t;
		result += _3_bma_m_2_da_m_db;
		result *= t;
		result += _da;
		result *= t;
		result += _a;

		return result;
	}

private:

	T _a;

	T _da;

	/**
	 * 2 * (a - b) + da + db
	 */
	T _2_amb_p_da_p_db;

	/**
	 * 3 * (b - a) - 2 * da - db
	 */
	T _3_bma_m_2_da_m_db;
};

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
