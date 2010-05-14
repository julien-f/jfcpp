#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include <expression.hpp>
#include <lambda.hpp>

using namespace std;
using namespace expression;
using namespace expression::operators;

template <typename T>
struct var : public base<T>
{
	typedef typename base<T>::value_type value_type;

	value_type eval(value_type x) const
	{
		return x;
	}

	friend ostream &operator<<(ostream &s, var)
	{
		s << 'x';
		return s;
	}
};

template <typename Expression>
void
test(Expression e)
{
	test(lambda<Expression>(e));
}

template <typename Expression>
void
test(lambda<Expression> f)
{
	cerr << f.expression() << endl;

	const double step = 1e-1;
	for (double t = -10; t <= 10; t += step)
	{
		cout << t << '\t' << f(t) << endl;
	}
}

int main()
{
	var<double> x;

	test(x * (1 + x * (1 + x * (1 + x * (1 + x)))));

	return EXIT_SUCCESS;
}
