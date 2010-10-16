#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include <expression.hpp>
#include <lambda.hpp>

using namespace jfcpp::expression::operators;

template <typename T>
struct var : public jfcpp::expression::base<T>
{
	typedef typename jfcpp::expression::base<T>::value_type value_type;

	value_type eval(value_type x) const
	{
		return x;
	}

	friend std::ostream &operator<<(std::ostream &s, var)
	{
		s << 'x';
		return s;
	}
};

template <typename Expression>
void
test(Expression e)
{
	test(jfcpp::lambda<Expression>(e));
}

template <typename Expression>
void
test(jfcpp::lambda<Expression> f)
{
	std::cerr << f.expression() << std::endl;

	const double step = 1e-1;
	for (double t = -10; t <= 10; t += step)
	{
		std::cout << t << '\t' << f(t) << std::endl;
	}
}

int main()
{
	var<double> x;

	test(x * (1 + x * (1 + x * (1 + x * (1 + x)))));

	return EXIT_SUCCESS;
}
