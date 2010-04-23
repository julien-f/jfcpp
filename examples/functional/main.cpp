#include <cstdlib>
#include <iostream>

#include <functional.hpp>

using namespace std;
using namespace functional;

int unary1(int x)
{
	return (x + 1);
}

int unary2(int x)
{
	return (x * 2);
}

double binary1(int x, int y)
{
	return (double(x) / y);
}

template <class F, typename T>
void test_unary(F f, const T &x)
{
	cout << f(x) << endl;
}

template <class F, typename T1, typename T2>
void test_binary(F f, const T1 &x, const T2 &y)
{
	cout << f(x, y) << endl;
}

int main()
{
	int x = 11;

	int y = 3;

	test_unary(identity_function<int>(), x);

	test_unary(compose(unary1, compose(unary2, unary1)), x);

	test_binary(binary1, x, y);

	test_binary(compose(binary1, unary1, unary2), x, y);

	return EXIT_SUCCESS;
}
