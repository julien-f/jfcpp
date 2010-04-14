#ifndef H_RATIONAL
#define H_RATIONAL

#include "contracts.h"

#include "math.hpp"

template <typename T = long int>
class rational
{
public:

	rational(const T &numerator = 0, const T &denominator = 1)
		: _denominator(denominator), _numerator(numerator)
	{
		requires(denominator != T(0));

		this->simplify();
	}

	const T &denominator() const
	{
		return this->_denominator;
	}

	rational<T> inverse() const
	{
		return rational<T>(this->_denominator, this->_numerator);
	}

	const T &numerator() const
	{
		return this->_numerator;
	}

	void simplify()
	{
		if (this->_denominator < T(0))
		{
			this->_denominator = -this->_denominator;
			this->_numerator = -this->_numerator;
		}

		const T g = gcd<T>(this->_numerator, this->_denominator);

		this->_numerator /= g;

		this->_denominator /= g;
	}

	template <typename T2>
	bool operator==(const rational<T2> &f) const
	{
		return ((this->_numerator == f.numerator()) &&
		        (this->_denominator == f.denominator()));
	}

	template <typename T2>
	bool operator!=(const rational<T2> &f) const
	{
		return !(*this == f);
	}

	template <typename T2>
	bool operator==(const T2 &x) const
	{
		return (this->_numerator == (this->_denominator * x));
	}

	template <typename T2>
	bool operator!=(const T2 &x) const
	{
		return !(*this == x);
	}

	rational<T> operator-() const
	{
		return rational<T>(-this->_numerator, this->_denominator);
	}

	template <typename T2>
	rational<T> operator+(const rational<T2> &f) const
	{
		return rational<T>(this->_numerator * f.denominator()
		                   + f.numerator() * this->_denominator,
		                   this->_denominator * f.denominator());
	}

	template <typename T2>
	rational<T> &operator+=(const rational<T2> &f)
	{
		*this = *this + f;
		return *this;
	}

	template <typename T2>
	rational<T> operator-(const rational<T2> &f) const
	{
		return (*this + -f);
	}

	template <typename T2>
	rational<T> &operator-=(const rational<T2> &f)
	{
		*this += - f;
		return *this;
	}

	template <typename T2>
	rational<T> operator*(const rational<T2> &f) const
	{
		return rational<T>(this->_numerator * f.numerator(),
		                   this->_denominator * f.denominator());
	}

	template <typename T2>
	rational<T> &operator*=(const rational<T2> &f)
	{
		*this = *this * f;

		return *this;
	}

	template <typename T2>
	rational<T> operator/(const rational<T2> &f) const
	{
		return (*this * f.inverse());
	}

	template <typename T2>
	rational<T> &operator/=(const rational<T2> &f)
	{
		*this *= f.inverse();
		return *this;
	}

private:

	T _denominator;

	T _numerator;
};

template <typename T>
std::ostream &operator<<(std::ostream &s, const rational<T> &f)
{
	const T &num = f.numerator();
	const T &den = f.denominator();

	s << num;

	if ((num != 0) && (den != 1))
	{
		s << "/" << den;
	}

	return s;
}

#endif // H_RATIONAL
