#include <cstdlib>
#include <iostream>

#include <jfcpp/math/rational.hpp>

using jfcpp::math::rational;

#define PRINT(EXP) (std::cout << #EXP ":  " << (EXP) << std::endl)

int main()
{
	rational<int> a(5, -2), b(3, 9), c(3);

	PRINT(a == -2.5);
	PRINT(c == 3);
	PRINT(3 == c);
	PRINT(3 != c);
	PRINT(a == c);

	PRINT(a);
	PRINT(b);

	PRINT((a + b));
	PRINT(a - b);
	PRINT(a * b);
	PRINT(a / b);

	return EXIT_SUCCESS;
}
