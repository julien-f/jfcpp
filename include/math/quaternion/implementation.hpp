#include <algorithm>

#include <math.hpp>

template <typename T>
quaternion<T>::quaternion(const_reference a, const_reference b,
                          const_reference c, const_reference d)
{
	_values[0] = a;
	_values[1] = b;
	_values[2] = c;
	_values[3] = d;
}

template <typename T>
quaternion<T>::quaternion(const_reference scalar,
                          const array<value_type, 3> &vector)
{
	_values[0] = scalar;
	_values[1] = vector[0];
	_values[2] = vector[1];
	_values[3] = vector[2];
}

template <typename T>
quaternion<T>
quaternion<T>::conjugate() const
{
	return quaternion(_values[0], -_values[1], -_values[2], -_values[3]);
}

template <typename T>
typename quaternion<T>::value_type
quaternion<T>::dot(const quaternion &q) const
{
	return sprod(_values, q._values);
}

template <typename T>
quaternion<T>
quaternion<T>::inverse() const
{
	quaternion result(conjugate());
	result /= dot(*this);
	return result;
}

template <typename T>
T
quaternion<T>::norm() const
{
	return sqrt(dot(*this));
}

template <typename T>
typename quaternion<T>::value_type
quaternion<T>::scalar() const
{
	return _values[0];
}

template <typename T>
array<typename quaternion<T>::value_type, 3>
quaternion<T>::vector() const
{
	array<value_type, 3> result;
	result[0] = _values[1];
	result[1] = _values[2];
	result[2] = _values[3];
	return result;
}

template <typename T>
bool
quaternion<T>::operator==(const quaternion &q) const
{
	return (_values == q._values);
}

template <typename T>
typename quaternion<T>::reference
quaternion<T>::operator[] (size_t i)
{
	return _values[i];
}

template <typename T>
typename quaternion<T>::const_reference
quaternion<T>::operator[] (size_t i) const
{
	return _values[i];
}

template <typename T>
quaternion<T>
quaternion<T>::operator-() const
{
	return quaternion(-_values);
}

template <typename T>
quaternion<T> &
quaternion<T>::operator+=(const quaternion &q)
{
	_values += q._values;
	return *this;
}

template <typename T>
quaternion<T> &
quaternion<T>::operator-=(const quaternion &q)
{
	_values -= q._values;
	return *this;
}

template <typename T>
quaternion<T>
quaternion<T>::operator*(const quaternion &q) const
{
	const_reference
		a = _values[0],
		b = _values[1],
		c = _values[2],
		d = _values[3],
		aa = q._values[0],
		bb = q._values[1],
		cc = q._values[2],
		dd = q._values[3];

	return quaternion(a * aa - b * bb - c * cc - d * dd,
	                  a * bb + b * aa + c * dd - d * cc,
	                  a * cc + c * aa + d * bb - b * dd,
	                  a * dd + d * aa + b * cc - c * bb);
}

template <typename T>
quaternion<T> &
quaternion<T>::operator*=(const quaternion &q)
{
	*this = *this * q;
	return *this;
}

template <typename T>
quaternion<T> &
quaternion<T>::operator/=(const quaternion &q)
{
	*this *= q.inverse();
	return *this;
}

template <typename T>
bool
quaternion<T>::operator==(const_reference s) const
{
	const value_type zero(0);

	return ((s == _values[0]) && (_values[1] == zero) && (_values[2] == zero)
	        && (_values[3] == zero));
}

template <typename T>
quaternion<T> &
quaternion<T>::operator*=(const_reference s)
{
	_values *= s;
	return *this;
}

template <typename T>
quaternion<T> &
quaternion<T>::operator/=(const_reference s)
{
	_values /= s;
	return *this;
}

template <typename T>
quaternion<T>::quaternion(array<T, 4> values)
	: _values(values)
{}
