#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

#include <jfcpp/math.hpp>
#include <jfcpp/various.hpp>

using jfcpp::from_string;
using jfcpp::math::numerical_derivate;


int main(int argc, char **argv)
{
	if (argc < 7)
	{
		std::cerr
			<< "Usage: " << argv[0] << " DT Y1 Y2 Y3 Y4 Y5" << std::endl
			<< std::endl
			<< "Computes the derivative at (X3, Y3)." << std::endl;
		return EXIT_FAILURE;
	}

	std::cout
		<< "Result: "
		<< numerical_derivate(from_string<double>(argv[1]),
		                      from_string<double>(argv[2]),
		                      from_string<double>(argv[3]),
		                      from_string<double>(argv[4]),
		                      from_string<double>(argv[5]),
		                      from_string<double>(argv[6]))
		<< std::endl;

	return EXIT_SUCCESS;
}
