#ifndef H_MATH
#define H_MATH

template <typename T>
bool
is_even(const T &x)
{
	return ((x % 2) == 0);
}

template <>
bool
is_even<unsigned int>(const unsigned int &x)
{
	return ((x & 1u) == 0);
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
	requires(n != 0);

	T base(x), exp(k), result(1);

	while (exp != 0)
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
	while (true)
	{
		if (a == 0)
		{
			return b;
		}
		b %= a;

		if (b == 0)
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
	T
		r(x), rp(n),
		u(1), up(0),
		v(0), vp(1),
		q, rs, us, vs;

	while (rp != 0)
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

	if (u < 0)
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

	return (g != 0 ? a / g * b : 0);
}

#endif // H_MATH
