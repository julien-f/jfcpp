#include <cstdlib>
#include <iostream>

#include <jfcpp/math.hpp>
#include <jfcpp/math/interpolation.hpp>

using namespace jfcpp::math;

#define PRINT(EXP) (std::cout << #EXP ":  " << (EXP) << std::endl)

int main()
{
	PRINT(gcd(35734216, 125434352));

	PRINT(is_even(3543542));
	PRINT(is_odd(3543542));

	interpolation::linear<double> linear(0, -1);
	interpolation::hermite<double> hermite(0, -1, 0, -1);

	PRINT(linear(0.5));
	PRINT(hermite(0.5));

	PRINT(numerical_derivate(1, double(0), -109./24, -265./3, -3717./8, -4472./3));

	std::cout << "Theorical results of the previous calculus:" << std::endl;
	PRINT(-365./2);

	return EXIT_SUCCESS;
}
