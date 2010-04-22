#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <utility>

#include "contracts.h"

#include "rational.hpp"
#include "matrix.hpp"

using namespace std;

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
	matrix<rational<long> > m(4);

	RandomGenerator::fill(m);

	cout << m;

	rational<long> tr = m.trace();

	cout << tr << endl;

	cout << m.inverse_perf();

	return EXIT_SUCCESS;
}
