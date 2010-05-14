#include <cstddef>
#include <cstdlib>
#include <iostream>

#include <ref.hpp>

using namespace std;

template <typename T1, typename T2>
void
test(T1 x, T2 y)
{
	x = y;
}

int main()
{
	int
		x = 2,
		y = 3;


	test(x, y);

	cout << x << ' ' << y << endl;

	test(ref(x), y);

	cout << x << ' ' << y << endl;

	test(ref(x), ref(y));

	cout << x << ' ' << y << endl;

	test(ref(x), cref(y));

	cout << x << ' ' << y << endl;

	double z;

	test(ref(z), ref(x));

	cout << z << ' ' << y << endl;

	return EXIT_SUCCESS;
}
