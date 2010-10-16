#include <cstdlib>
#include <iostream>

#include <array_view.hpp>

using jfcpp::array_view;
using jfcpp::make_array_view;

#define PRINT(EXP) (std::cout << #EXP ":  " << (EXP) << std::endl)

int main()
{
	const int a[] = {1, 2, 3, 4};
	int b[] = {1, 2, 3, 4, 5};
	double c[] = {1, 2, 4, 3};

	// arr_a is nessecary an array_view<const int> because a is a const int
	// array.
	//array_view<const int> ar_a = make_array_view(a);

	// make_array_view allows us to directly create an array_view from a static
	// array instead of having to write:
	array_view<const int> ar_a(4, a);

	// For the others, we may choose.
	array_view<const int> ar_b = make_array_view(b);
	array_view<double> ar_c = make_array_view(c);

	// Forbidden because ar_a is a view on an array of constant integers.
	//ar_a = ar_b;

	// Prints ar_a.
	PRINT(ar_a);

	// Copies values of ar_a to ar_c
	ar_c = ar_a;

	// Prints ar_c.
	PRINT(ar_c);

	// Reads values of ar_c from cin.
	std::cin >> ar_c;

	// Reprints ar_c.
	PRINT(ar_c);

	// Are ar_a's values equals to ar_b's?
	PRINT(ar_a == ar_b);

	// Is ar_a lexicographically lesser than ar_b?
	PRINT(ar_a < ar_b);

	// Are ar_a's values equals to ar_c's?
	PRINT(ar_a == ar_c);

	return EXIT_SUCCESS;
}
