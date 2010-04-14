#ifndef H_FRACTION
#define H_FRACTION

#include "contracts.h"

#include "math.hpp"

template <typename T = long int>
class fraction
{
public:

	fraction(const T &numerator = 0, const T &denominator = 1)
		: _denominator(denominator), _numerator(numerator)
	{
		requires(denominator != 0);
		this->simplify();
	}

	const T &denominator() const
	{
		return this->_denominator;
	}

	fraction<T> inverse() const
	{
		return fraction<T>(this->_denominator, this->_numerator);
	}

	const T &numerator() const
	{
		return this->_numerator;
	}

	void simplify()
	{
		const T g = gcd<T>(this->_numerator, this->_denominator);

		this->_numerator /= g;

		this->_denominator /= g;
	}

	template <typename T2>
	bool operator==(const fraction<T2> &f) const
	{
		return ((this->_numerator == f.numerator()) &&
		        (this->_denominator == f.denominator()));
	}

	template <typename T2>
	bool operator!=(const fraction<T2> &f) const
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

	fraction<T> operator-() const
	{
		return fraction<T>(-this->_numerator, this->_denominator);
	}

	template <typename T2>
	fraction<T> operator+(const fraction<T2> &f) const
	{
		return fraction<T>(this->_numerator * f.denominator()
		                   + f.numerator() * this->_denominator,
		                   this->_denominator * f.denominator());
	}

	template <typename T2>
	fraction<T> &operator+=(const fraction<T2> &f)
	{
		*this = *this + f;
		return *this;
	}

	template <typename T2>
	fraction<T> operator-(const fraction<T2> &f) const
	{
		return (*this + -f);
	}

	template <typename T2>
	fraction<T> &operator-=(const fraction<T2> &f)
	{
		*this += - f;
		return *this;
	}

	template <typename T2>
	fraction<T> operator*(const fraction<T2> &f) const
	{
		return fraction<T>(this->_numerator * f.numerator(),
		                   this->_denominator * f.denominator());
	}

	template <typename T2>
	fraction<T> &operator*=(const fraction<T2> &f)
	{
		*this = *this * f;

		return *this;
	}

	template <typename T2>
	fraction<T> operator/(const fraction<T2> &f) const
	{
		return (*this * f.inverse());
	}

	template <typename T2>
	fraction<T> &operator/=(const fraction<T2> &f)
	{
		*this *= f.inverse();
		return *this;
	}

private:

	T _denominator;

	T _numerator;
};

template <typename T>
std::ostream &operator<<(std::ostream &s, const fraction<T> &f)
{
	s << f.numerator() << "/" << f.denominator();

	return s;
}

#endif // H_FRACTION
