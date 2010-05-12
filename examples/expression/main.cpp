#include <cstdlib>
#include <iostream>
#include <ostream>

#include <expression.hpp>

using namespace std;
using namespace expression;
using namespace expression::operators;

struct var : public base<double, double>
{
	double eval(double x) const
	{
		return x;
	}
};

ostream &operator << (ostream &s, var)
{
	s << 'x';
	return s;
}

template <typename EXP>
void
test(EXP e)
{
	cout << e << endl;

	for (int i = 0; i < 10; ++i)
	{
		cout << "x = " << i << ": " << e.eval(i) << endl;
	}
}

int main()
{
	var x;

	test(2 * -x + 4);

	return EXIT_SUCCESS;
}
