#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#include <math.hpp>
#include <various.hpp>

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 7)
	{
		cerr
			<< "Usage: " << argv[0] << " DT Y1 Y2 Y3 Y4 Y5" << endl
			<< endl
			<< "Computes the derivative at (X3, Y3)." << endl;
		return EXIT_FAILURE;
	}

	cout
		<< "Result: "
		<< numerical_derivate(from_string<double>(argv[1]),
		                      from_string<double>(argv[2]),
		                      from_string<double>(argv[3]),
		                      from_string<double>(argv[4]),
		                      from_string<double>(argv[5]),
		                      from_string<double>(argv[6]))
		<< endl;

	return EXIT_SUCCESS;
}
