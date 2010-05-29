#ifndef H_QUATERNION
#define H_QUATERNION

#include <cstddef>
#include <cmath>
#include <ostream>

#include <array.hpp>
#include <math.hpp>
#include <operators.hpp>

template <typename T>
class quaternion : public operators::addable<quaternion<T> >,
                   public operators::dividable<quaternion<T> >,
                   public operators::equality_comparable<quaternion<T> >,
                   public operators::subtractable<quaternion<T> >
{
public:

	/**
	 *
	 */
	typedef const T &const_reference;

	/**
	 *
	 */
	typedef T &reference;

	/**
	 *
	 */
	typedef T value_type;

	/**
	 * a + b*i + c*j + d*k
	 */
	quaternion(const_reference a = value_type(1),
	           const_reference b = value_type(0),
	           const_reference c = value_type(0),
	           const_reference d = value_type(0));

	/**
	 *
	 */
	quaternion(const_reference scalar, const array<value_type, 3> &vector);

	/**
	 *
	 */
	quaternion conjugate() const;

	/**
	 *
	 */
	quaternion inverse() const;

	/**
	 *
	 */
	value_type norm() const;

	/**
	 * Gets the scalar part of this quaternion (its real part).
	 */
	value_type scalar() const;

	/**
	 * Gets the vectorial part of this quaternion (its unreal part).
	 */
	array<value_type, 3> vector() const;

	/**
	 *
	 */
	bool operator==(const quaternion &q) const;

	/**
	 *
	 */
	reference operator[] (size_t i);
	const_reference operator[] (size_t i) const;

	/**
	 *
	 */
	quaternion operator-() const;

	/**
	 *
	 */
	quaternion &operator+=(const quaternion &q);

	/**
	 *
	 */
	quaternion &operator-=(const quaternion &q);

	/**
	 *
	 */
	quaternion operator*(const quaternion &q) const;

	/**
	 *
	 */
	quaternion &operator*=(const quaternion &q);

	/**
	 *
	 */
	quaternion &operator/=(const quaternion &q);

	/**
	 *
	 */
	bool operator==(const_reference s) const;

	/**
	 *
	 */
	quaternion &operator*=(const_reference s);

	/**
	 *
	 */
	quaternion &operator/=(const_reference s);

	friend std::ostream &operator<< (std::ostream &s, const quaternion &q)
	{
		s << q._values;
		return s;
	}

private:

	array<T, 4> _values;

	quaternion(array<T, 4> values);
};

template <typename T>
quaternion<T>
quaternion_from_rotation(const array<T, 3> &axis, T angle)
{
	angle /= 2;

	const T tmp(sin(angle) / norm_2(axis));

	return quaternion<T>(cos(angle), axis[0] * tmp, axis[1] * tmp, axis[2] * tmp);
}

template <typename T>
array<T, 3>
rotate_with_quaternion(const array<T, 3> &v, const quaternion<T> &q)
{
	return (q * quaternion<T>(0, v) * q.inverse()).vector();
}

#include "quaternion/implementation.hpp"

#endif // H_QUATERNION
