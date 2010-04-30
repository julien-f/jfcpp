#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#include <math/interpolation.hpp>

using namespace std;
using namespace interpolation;

template <typename Func>
void
trace(const Func f, const double a = 0, const double b = 1,
      const size_t n = 1e2)
{
	const double step = 1.0 / n;

	for (double t = a; t < b; t += step)
	{
		cout << t << ' ' << f(t) << endl;
	}
}

int main(int argc, char **argv)
{
	string arg(argc >= 2 ? argv[1] : "--linear");

	if ((arg == "--hermite") || (arg == "-h"))
	{
		trace(hermite<double>(0, -1, 0, 0));
	}
	else if ((arg == "--linear") || (arg == "-l"))
	{
		trace(linear<double>(1.35, 0, 2.75, 13), 1.35, 2.75);
	}
	else
	{
		cerr << "Invalid argument “" << arg << "”." << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
