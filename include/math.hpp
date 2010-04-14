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
	return ((x & 1) == 0);
}

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
		if (is_odd(exp))
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
gcd(T a, T b)
{
	T c;
	while (b != 0)
	{
		c = b;
		b = a % b;
		a = c;
	}
	return a;
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


#endif // H_MATH
