#include <cstdlib>
#include <iostream>

#include <jfcpp/functional.hpp>

using jfcpp::functional::compose;

// Here are two unary functions.
int unary1(int x)
{
	return (x + 1);
}
int unary2(int x)
{
	return (x * 2);
}

// An one unary function.
double binary1(int x, int y)
{
	return (double(x) / y);
}

// This function applies an unary function 'f'
// to an element 'x' and displays the result.
template <class F, typename T>
void test_unary(F f, const T &x)
{
	std::cout << f(x) << std::endl;
}

// This function applies a binary function 'f'
// to an element 'x' and an elemen 'y' and displays
// the result.
template <class F, typename T1, typename T2>
void test_binary(F f, const T1 &x, const T2 &y)
{
	std::cout << f(x, y) << std::endl;
}

int main()
{
	// Let's declare some variables.
	int x = 11;
	int y = 3;

	// f(x) = unary1(unary2(x))
	test_unary(compose(unary1, unary2), x);

	// f(x) = unary1(unary2(unary1(x)))
	test_unary(compose(unary1, compose(unary2, unary1)), x);

	// f(x, y) = binary1(unary1(x), unary2(y))
	test_binary(compose(binary1, unary1, unary2), x, y);

	return EXIT_SUCCESS;
}
