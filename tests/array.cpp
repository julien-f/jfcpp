// To properly test inclusion, the tested file must be the first included.
#include <jfcpp/array.hpp>

#include <cstdlib>

#include <contracts.h>

#define SIZE 10

using jfcpp::array;

int main()
{
	array<int, SIZE> a;

	assert(a.size() == SIZE);

	a = 1;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 1);
	}

	a += 1;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 2);
	}

	a -= -4;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 6);
	}

	a *= 9;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 54);
	}

	a /= 2;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 27);
	}

	a %= 2;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 1);
	}

	array<int> b(SIZE);

	assert(b.size() == SIZE);

	b = 3;
	for (size_t i = 0; i < b.size(); ++i)
	{
		assert(b[i] == 3);
	}

	assert(a != b);
	assert(b != a);

	a += b;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 4);
	}

	a *= b;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 12);
	}

	a -= b;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 9);
	}

	a /= b;
	for (size_t i = 0; i < a.size(); ++i)
	{
		assert(a[i] == 3);
	}

	assert(a == b);
	assert(b == a);

	array<int, SIZE> c(-a);
	for (size_t i = 0; i < c.size(); ++i)
	{
		assert(c[i] == -a[i]);
	}

	array<int> d(-b);
	for (size_t i = 0; i < d.size(); ++i)
	{
		assert(d[i] == -b[i]);
	}

	return EXIT_SUCCESS;
}
