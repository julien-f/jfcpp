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

template <typename T>
bool
is_even(const T &x)
{
	return ((x % 2) == T(0));
}

template <>
bool
is_even<unsigned int>(const unsigned int &x)
{
	return ((x & 1u) == 0u);
}

#ifdef __GMP_PLUSPLUS__
template <>
bool
is_even<mpz_class>(const mpz_class &x)
{
	return mpz_even_p(x.get_mpz_t());
}
#endif

template <typename T>
bool
is_odd(const T &x)
{
	return !is_even<T>(x);
}

template <typename T>
T
exp_mod(const T &x, const T &k, const T &n)
{
	const T zero(0);

	requires(n != zero);

	T base(x), exp(k), result(1);

	while (exp != zero)
	{
		if (is_odd<T>(exp))
		{
			result = (result * base) % n;
		}
		exp /= 2;
		base = (base * base) % n;
	}

	return result;
}

template <typename T>
T
gcd_helper(T a, T b)
{
	const T zero(0);

	while (true)
	{
		if (a == zero)
		{
			return b;
		}
		b %= a;

		if (b == zero)
		{
			return a;
		}
		a %= b;
	}
}


template <typename T>
T
gcd(T a, T b)
{
	const T g = gcd_helper<T>(a, b);
	const T zero(0);

	return (g < zero ? -g : g);
}

template <typename T>
T
inverse_mod(const T &x, const T &n)
{
	const T zero(0);

	T
		r(x), rp(n),
		u(1), up(0),
		v(0), vp(1),
		q, rs, us, vs;

	while (rp != zero)
	{
		q = r / rp;
		rs = r;
		us = u;
		vs = v;
		r = rp;
		u = up;
		v = vp;
		rp = rs - q * rp;
		up = us - q * up;
		vp = vs - q * vp;
	}

	if (u < zero)
	{
		u += n;
	}

	return u;
}

template <typename T>
T
lcm(const T &a, const T &b)
{
	const T g = gcd<T>(a, b);
	const T zero(0);

	return (g != zero ? a / g * b : zero);
}

#endif // H_MATH
