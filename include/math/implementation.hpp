#include <cmath> // for sqrt
#include <numeric> // for inner_product

// Specializations for mpz_class.
#ifdef __GMP_PLUSPLUS__
#include "math/gmp.hpp"
#endif

template <typename T>
T
abs(const T &x)
{
	const T zero(0);

	return (x < zero ? -x : x);
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
gcd(const T &a, const T &b)
{
	return abs(gcd_helper<T>(a, b));
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

#define IS_EVEN_SPECIALIZATION(TYPE) \
	template <> inline \
	bool \
	is_even<unsigned TYPE>(const unsigned TYPE &x) \
	{ \
		return ((x & 1u) == 0u); \
	}

IS_EVEN_SPECIALIZATION(char)
IS_EVEN_SPECIALIZATION(int)
IS_EVEN_SPECIALIZATION(long int)

#undef IS_EVEN_SPECIALIZATION

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

template <typename T, size_t S>
T
norm_1(const array<T, S> &v)
{
	T sum(0);

	for (typename array<T, S>::const_iterator
		     it = v.begin(),
		     end = v.end();
	     it != end;
	     ++it)
	{
		sum += abs(*it);
	}

	return sum;
}

template <typename T, size_t S>
T
norm_2(const array<T, S> &v)
{
	T sum(0);

	for (typename array<T, S>::const_iterator
		     it = v.begin(),
		     end = v.end();
	     it != end;
	     ++it)
	{
		typename array<T, S>::const_reference x = *it;
		sum += x * x;
	}

	return sqrt(sum);
}

template <typename TD, typename TCD>
TCD
numerical_derivate(TD dt, const TCD &xm2, const TCD &xm1, const TCD &,
                   TCD xp1, const TCD &xp2)
{
	// Base formula:
	// result = (8 * (xp1 - xm1) + xm2 - xp2) / (12 * dt)

	xp1 -= xm1;
	xp1 *= 8;
	xp1 += xm2;
	xp1 -= xp2;

	dt *= 12;

	xp1 /= dt;

	return xp1;
}

template <typename T, size_t S1, size_t S2>
T
sprod(const array<T, S1> &u, const array<T, S2> &v)
{
	requires(u.size() == v.size());

	return std::inner_product(u.begin(), u.end(), v.begin(), T(0));
}

template <typename T, size_t S1, size_t S2>
array<T, 3>
vprod(const array<T, S1> &u, const array<T, S2> &v)
{
	requires(u.size() == 3);
	requires(v.size() == 3);

	array<T, 3> result;

	result[0] = u[1] * v[2] - u[2] * v[1];
	result[1] = u[2] * v[0] - u[0] * v[2];
	result[2] = u[0] * v[1] - u[1] * v[0];

	return result;
}
