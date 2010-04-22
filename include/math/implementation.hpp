// Specializations for mpz_class.
#ifdef __GMP_PLUSPLUS__
#include "math/gmp.hpp"
#endif

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
gcd(const T &a, const T &b)
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

template <typename T>
bool
is_odd(const T &x)
{
	return !is_even<T>(x);
}

template <typename T>
T
lcm(const T &a, const T &b)
{
	const T g = gcd<T>(a, b);
	const T zero(0);

	return (g != zero ? a / g * b : zero);
}

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
