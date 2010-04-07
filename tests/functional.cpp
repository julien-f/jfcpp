#include <cstdlib>
#include <iostream>

using namespace std;

#include "functional.hpp"

struct unary1 : std::unary_function<int, int>
{
	int operator()(int x)
	{
		return (x + 1);
	}
};

struct unary2 : std::unary_function<int, int>
{
	int operator()(int x)
	{
		return (x * 2);
	}
};

struct binary1 : std::binary_function<int, int, double>
{
	double operator()(int x, int y)
	{
		return (double(x) / y);
	}
};

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

	test_unary(identity_function<int>(), x);

	test_unary(unary_compose(unary1(), unary2()), x);

	int y = 3;

	test_binary(binary1(), x, y);

	test_binary(binary_compose(binary1(), unary1(), unary2()), x, y);

	return EXIT_SUCCESS;
}
