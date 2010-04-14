/**
 * This class is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This class is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this class.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Julien Fontanet <julien.fontanet@isonoe.net>
 */

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
