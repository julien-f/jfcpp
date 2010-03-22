#include <stdexcept>

#include "circular_buffer.hpp"
#include "contracts.h"

int main()
{
	assert_exception(circular_buffer<int>(0), ContractViolated);

	{
		circular_buffer<int> buf(1);


		assert(buf.capacity() == 1);

		assert(buf.size() == 0);

		assert(buf.empty());

		assert(!buf.full());

		assert(buf.begin() == buf.end());

		assert_exception(buf[0], ContractViolated);

		assert_exception(buf.at(0), std::out_of_range);


		buf.push_back(10);

		assert(buf.size() == 1);

		assert(!buf.empty());

		assert(buf.full());

		assert(buf.begin() != buf.end());

		assert(*(buf.begin()) == 10);

		assert(buf[0] == 10);

		assert(buf.at(0) == 10);
	}
}
