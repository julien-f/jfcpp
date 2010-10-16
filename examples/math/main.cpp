#include <cstdlib>
#include <iostream>

#include <math.hpp>
#include <math/interpolation.hpp>

#define PRINT(EXP) (std::cout << #EXP ":  " << (EXP) << std::endl)

int main()
{
	PRINT(jfcpp::gcd(35734216, 125434352));

	PRINT(jfcpp::is_even(3543542));
	PRINT(jfcpp::is_odd(3543542));

	jfcpp::interpolation::linear<double> linear(0, -1);
	jfcpp::interpolation::hermite<double> hermite(0, -1, 0, -1);

	PRINT(linear(0.5));
	PRINT(hermite(0.5));

	PRINT(jfcpp::numerical_derivate(1, double(0), -109./24, -265./3, -3717./8, -4472./3));

	std::cout << "Theorical results of the previous calculus:" << std::endl;
	PRINT(-365./2);

	return EXIT_SUCCESS;
}
