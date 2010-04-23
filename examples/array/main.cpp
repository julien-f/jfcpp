#include <cstddef>
#include <cstdlib>
#include <iostream>

#include <array.hpp>

using namespace std;

#define PRINT(EXP) (cout << #EXP ":  " << (EXP) << endl)

int main()
{
	array<int> a(10);
	array<int, 10> b;
	array<int> c(10);

	b.fill(0);
	c.fill(3);

	PRINT(a);
	PRINT(b);

	a[1] = 35435;

	b = a;

	b = c;

	a = c;

	PRINT(a);
	PRINT(b);

	PRINT(a == b);
	PRINT(a - c);

	cout << sizeof(a) << " " << sizeof(b) << endl;

	return EXIT_SUCCESS;
}
