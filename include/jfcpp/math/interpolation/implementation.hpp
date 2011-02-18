template <typename TCD, typename TD>
linear<TCD, TD>::linear()
{}

template <typename TCD, typename TD>
linear<TCD, TD>::linear(const TCD &y0, const TCD &y1)
{
	initialize(y0, y1);
}

template <typename TCD, typename TD>
linear<TCD, TD>::linear(const TD &x0, const TCD &y0,
                        const TD &x1, const TCD &y1)
{
	initialize(x0, y0, x1, y1);
}

template <typename TCD, typename TD>
void
linear<TCD, TD>::initialize(const TCD &y0, const TCD &y1)
{
	// Simplified formala for x0 = 0 and x1 = 1.
	_a = y1;
	_a -= y0;
	_b = y0;
}

template <typename TCD, typename TD>
void
linear<TCD, TD>::initialize(const TD &x0, const TCD &y0,
                            const TD &x1, const TCD &y1)
{
	// Formula:
	// y = (y1 - y0) / (x1 - x0) * x + (x1 * y0 - x0 * y1) / (x1 - x0)
	//
	// So:
	// _a = (y1 - y0) / (x1 - x0)
	// _b = (x1 * y0 - x0 * y1) / (x1 - x0)

	_a = y1;
	_b = y0;

	TCD tmp(x1);
	tmp -= x0;

	_a -= y0;
	_a /= tmp;

	_b *= x1;

	{
		TCD tmp(y1);
		tmp *= x0;
		_b -= tmp;
	}
	_b /= tmp;
}

template <typename TCD, typename TD>
linear<TCD, TD> &
linear<TCD, TD>::operator=(const linear<TCD, TD> &l)
{
	_a = l._a;
	_b = l._b;
}

template <typename TCD, typename TD>
TCD
linear<TCD, TD>::operator()(const TD &x) const
{
	// y = _a * x + _b

	TCD result(_a);
	result *= x;
	result += _b;

	return result;
}

template <typename TCD, typename TD>
hermite<TCD, TD>::hermite(TCD y0, TCD dy0, TCD y1, const TCD &dy1)
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
		TCD tmp(dy0);
		tmp *= 2;
		_c -= tmp;
	}
	_c -= dy1;

	_d -= y1;
	_d *= 2;
	_d += dy0;
	_d += dy1;
}

template <typename TCD, typename TD>
TCD
hermite<TCD, TD>::operator()(const TD &x) const
{
	TCD result(_d);
	result *= x;
	result += _c;
	result *= x;
	result += _b;
	result *= x;
	result += _a;

	return result;
}

template <typename Codomain, typename Domain, typename Angle>
slerp<Codomain, Domain, Angle>::slerp(Angle angle, Codomain y0, Codomain y1)
	: _angle(angle), _a(y0), _b(y1)
{
	Angle sin_angle = sin(_angle);
	_a /= sin_angle;
	_b /= sin_angle;
}

template <typename Codomain, typename Domain, typename Angle>
Codomain
slerp<Codomain, Domain, Angle>::operator()(const Domain &x) const
{
	Codomain result(_a);
	result *= sin((1 - x) * _angle);

	Codomain tmp(_b);
	tmp *= sin(_angle * x);

	result += tmp;

	return result;
}
