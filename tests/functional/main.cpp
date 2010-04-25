// To properly test inclusion, the tested file must be the first included.
#include <functional.hpp>

#include <cstdlib>

#include <contracts.h>

/**
 * Comparing two expressions directly does not always work, so w use this
 * function.
 */
template <typename T>
void cmp(const T &a, const T &b)
{
	assert(a == b);
}

double unary1(double x)
{
	return ((3 * x * x + 6) / 127);
}

double unary2(double x)
{
	return (x * x + 3.25 * x - 3);
}

double binary1(double x, double y)
{
	return ((1.658 * x - 8.256 * y) * (y - 2.25));
}

int main()
{
	using namespace functional;

	const double
		x = 5.65,
		y = 968754.215;

	// Identity function.
	cmp(identity<double>()(x), x);

	// Unary function composition.
	cmp(compose(unary1, identity<double>())(x), unary1(x));
	cmp(compose(identity<double>(), unary1)(x), unary1(x));
	cmp(compose(unary1, unary2)(x), unary1(unary2(x)));

	// Binary function composition.
	cmp(compose(binary1, identity<double>(), identity<double>())(x, y), binary1(x, y));
	cmp(compose(binary1, unary1, identity<double>())(x, y), binary1(unary1(x), y));
	cmp(compose(binary1, identity<double>(), unary2)(x, y), binary1(x, unary2(y)));
	cmp(compose(binary1, unary1, unary2)(x, y), binary1(unary1(x), unary2(y)));

	// + - * / %
	cmp(plus<double>()(x, y), x + y);
	cmp(minus<double>()(x, y), x - y);
	cmp(multiplies<double>()(x, y), x * y);
	cmp(divides<double>()(x, y), x / y);
	cmp(modulus<int>()(9, 4), 9 % 4); // Does not work with double type.

	return EXIT_SUCCESS;
}
