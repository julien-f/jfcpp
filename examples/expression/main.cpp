#include <cstdlib>
#include <iostream>

#include <expression.hpp>

using namespace std;
using namespace expression;
using namespace expression::operators;

int main()
{
	cout << (wrap(4.5) + wrap(3.5)).eval() << endl;

	return EXIT_SUCCESS;
}
