template <typename T, size_t D>
oblique<T, D>::oblique(array<value_type, dimension + 1> hyperplan,
                       vector direction)
  : _plan(plan)
{
	const value_type zero(0);

	_denominator = 0;

	vector tmp;
	for (size_t i = 0; i < dimension; ++i)
	{
		_denominator += tmp[i] = hyperplan[i] * direction[i];
	}

	for (size_t i = 0; i < dimension; ++i)
	{
		typename vector::reference current = _squares[i];

		current = zero;
		for (size_t j = 0; j < dimension; ++j)
		{
			if (i != j)
			{
				current += tmp[j];
			}
		}
	}
}

template <typename T, size_t D>
typename oblique<T, D>::vector
oblique<T, D>::operator()(const vector &v) const
{
	vector result(_squares * v);

	vector tmp1(v);
	for (size_t i = 0; i < dimension; ++i)
	{
		tmp1[i] *= _plan[i];
	}

	const value_type last(_plan[dimension]);

	vector tmp2;
	for (size_t i = 0; i < dimension; ++i)
	{
		typename vector::reference current = tmp2[i];

		current = last;
		for (size_t j = 0; j < dimension; ++j)
		{
			if (i != j)
			{
				current += tmp1[j];
			}
		}
		current *= _plan[i];
	}

	result -= tmp2;
	result /= _denominator;

	return result;
}

template <typename T, size_t D>
orthogonal<T, D>::orthogonal(array<value_type, dimension + 1> plan)
  : _plan(plan)
{
	const value_type zero(0);

	_denominator = 0;

	vector tmp;
	for (size_t i = 0; i < dimension; ++i)
	{
		typename array<value_type, dimension + 1>::const_reference
			current = _plan[i];

		_denominator += tmp[i] = current * current;
	}

	for (size_t i = 0; i < dimension; ++i)
	{
		typename vector::reference current = _squares[i];

		current = zero;
		for (size_t j = 0; j < dimension; ++j)
		{
			if (i != j)
			{
				current += tmp[j];
			}
		}
	}
}

template <typename T, size_t D>
typename orthogonal<T, D>::vector
orthogonal<T, D>::operator()(const vector &v) const
{
	vector result(_squares * v);

	vector tmp1(v);
	for (size_t i = 0; i < dimension; ++i)
	{
		tmp1[i] *= _plan[i];
	}

	const value_type last(_plan[dimension]);

	vector tmp2;
	for (size_t i = 0; i < dimension; ++i)
	{
		typename vector::reference current = tmp2[i];

		current = last;
		for (size_t j = 0; j < dimension; ++j)
		{
			if (i != j)
			{
				current += tmp1[j];
			}
		}
		current *= _plan[i];
	}

	result -= tmp2;
	result /= _denominator;

	return result;
}

template <typename T>
perspective<T>::perspective(T e2s) : _e2s(e2s)
{}

template <typename T>
typename perspective<T>::vec2
perspective<T>::operator()(const vec3 &v) const
{
	T ratio(v[2]);
	ratio /= _e2s;

	vec2 result;
	result[0] = v[0];
	result[0] /= ratio;
	result[1] = v[1];
	result[1] /= ratio;

	return result;
}
