template <typename T>
linear<T>::linear(T y0, T y1) : _a(y1), _b(y0)
{
	// Simplified formala for x0 = 0 and x1 = 1.

	_a -= y0;
}

template <typename T>
linear<T>::linear(T x0, T y0, const T &x1, T y1) : _a(y1), _b(y0)
{
	// Formula:
	// y = (y1 - y0) / (x1 - x0) * x + (x1 * y0 - x0 * y1) / (x1 - x0)
	//
	// So:
	// _a = (y1 - y0) / (x1 - x0)
	// _b = (x1 * y0 - x0 * y1) / (x1 - x0)

	T tmp(x1);
	tmp -= x0;

	_a -= y0;
	_a /= tmp;

	_b *= x1;
	x0 *= y1;
	_b -= x0;
	_b /= tmp;
}

template <typename T>
T
linear<T>::operator()(T x)
{
	// y = _a * x + _b

	x *= _a;
	x += _b;

	return x;
}

template <typename T>
hermite<T>::hermite(T y0, T dy0, T y1, const T &dy1)
	: _a(y0), _b(dy0), _c(y1), _d(y0)
{
	// Base formula:
	// result = (2 * x³ - 3 * x² + 1) * y0
	//          + (x³ - 2 * x² + x) * dy0
	//          + (-2 * x³ + 3 * x²) * y1
	//          + (x³ - x²) * dy1
	//
	// After decomposition:
	// result = y0 + x * (
	//           dy0 + x * (
	//            3 * (y1 - y0) - 2 * dy0 - dy1 + x * (
	//             2 * (y0 - y1) + dy0 + dy1
	//            )
	//           )
	//          )
	//
	//
	// Identification:
	// result = _a + x * (_b + x * (_c + x * _d))
	// _a = y0
	// _b = dy0
	// _c = 3 * (y1 - y0) - 2 * dy0 - dy1
	// _d = 2 * (y0 - y1) + dy0 + dy1

	_c -= y0;
	_c *= 3;
	{
		T tmp(dy0);
		tmp *= 2;
		_c -= tmp;
	}
	_c -= dy1;

	_d -= y1;
	_d *= 2;
	_d += dy0;
	_d += dy1;
}

template <typename T>
T
hermite<T>::operator()(const T &x)
{
	T result(_d);
	result *= x;
	result += _c;
	result *= x;
	result += _b;
	result *= x;
	result += _a;

	return result;
}

