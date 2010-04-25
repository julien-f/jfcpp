#include <cstddef>
#include <cstdlib>
#include <iostream>

#include <array.hpp>

using namespace std;

#define PRINT(EXP) (cout << #EXP ":  " << (EXP) << endl)

int main()
{
	// Let's create a static array of integers
	// with a size known at compile time.
	array<int, 5> a;

	// Let's create a static array of integers with
	// a size not (necessary) known at compile time.
	array<int> b(5);

	// Now fill them with a value.
	a = 6;
	b = 2;

	// Print them.
	PRINT(a);
	PRINT(b);

	// Change manually some values.
	a[4] = 468;
	b[1] += 2;

	// Reprint them.
	PRINT(a);
	PRINT(b);

	// All operations are element-wise.

	// Let's try some arithmetic operations.
	PRINT(a + b);
	PRINT(a - b);
	PRINT(a * b);
	PRINT(a / b);
	PRINT(a % b);

	// Some bitwise operations.
	PRINT(a & b);
	PRINT(a | b);
	PRINT(a << b);
	PRINT(a >> b);
	PRINT(a ^ b);

	PRINT(a * 3);
	//PRINT(3 * a); // Does not currently work.

	PRINT(a == b);
	PRINT(b == a);

	PRINT(a != b);
	PRINT(b != a);

	PRINT(a == a);
	PRINT(b == b);

	PRINT(a != a);
	PRINT(b != b);

	cout << sizeof(a) << " " << sizeof(b) << endl;

	return EXIT_SUCCESS;
}
