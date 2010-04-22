#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "contracts.h"

using namespace std;

#include "array.hpp"

int main()
{
	array<int> a(10);
	array<int, 10> b;
	array<int> c(10);

	b.fill(0);
	c.fill(3);

	cout << a << b;

	a[1] = 35435;

	b = a;

	b = c;

	a = c;

	cout << a << b;

	cout << (a == b) << endl;

	cout << sizeof(a) << " " << sizeof(b) << endl;

	return EXIT_SUCCESS;
}
