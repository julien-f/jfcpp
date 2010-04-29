#include <cstddef>
#include <cstdlib>
#include <iostream>

#include <math.hpp>
#include <math/interpolation.hpp>

using namespace std;

int main()
{
	const interpolation::hermite<double> hermite(0, -1, 0, 0);

	for (double t = 0; t < 1; t += 1e-3)
	{
		cout << t << ' ' << hermite(t) << endl;
	}

	return EXIT_SUCCESS;
}
