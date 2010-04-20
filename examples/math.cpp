#include <cstddef>
#include <cstdlib>
#include <iostream>

#include <math.hpp>

using namespace std;

#define PRINT(EXP) (cout << #EXP ":  " << (EXP) << endl)

int main()
{
	PRINT(gcd(35734216, 125434352));

	PRINT(is_even(3543542));
	PRINT(is_odd(3543542));

	interpolation<double> interp(-1, 0, -1, 0);

	PRINT(interp(0.5));

	PRINT(numerical_derivate<double>(1, 0, -109./24, -265./3, -3717./8, -4472/3));

	cout << "Theorical results of the previous calculus:" << endl;
	PRINT(-365./2);

	return EXIT_SUCCESS;
}
