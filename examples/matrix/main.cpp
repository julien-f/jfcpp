#include <algorithm> // std::generate
#include <cstdlib>   // EXIT_SUCCESS
#include <iostream>  // std::cout & std::endl

#include <matrix.hpp>
#include <rational.hpp>

using jfcpp::matrix;
using jfcpp::rational;

struct RandomGenerator
{
	template<typename T> static
	void
	fill(matrix<T> &m)
	{
		std::generate(m.begin(), m.end(), RandomGenerator());
	}

	/**
	 * Generates a random integer between 2 and 100.
	 */
	rational<long>
	operator()()
	{
		return rational<long>((rand() % 10), 1);
	}
};

int main()
{
	matrix<rational<long> > m(3);

	RandomGenerator::fill(m);

	std::cout << m;

	rational<long> tr = m.trace();

	std::cout << tr << std::endl;

	std::cout << m.det() << std::endl;

	std::cout << m.inverse_perf();

	return EXIT_SUCCESS;
}
