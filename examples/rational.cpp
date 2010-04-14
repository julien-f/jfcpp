#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "contracts.h"

using namespace std;

#include "rational.hpp"

#define PRINT(EXP) (cout << #EXP ":  " << (EXP) << endl)

int main()
{
	rational<int> a(-5, 2), b(3, 9);

	PRINT(a);
	PRINT(b);

	a.simplify();
	b.simplify();

	PRINT(a);
	PRINT(b);

	PRINT((a + b));
	PRINT(a - b);
	PRINT(a * b);
	PRINT(a / b);

	return EXIT_SUCCESS;
}
