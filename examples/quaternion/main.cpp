#include <math/quaternion.hpp>

#include <cstdlib>
#include <iostream>

#include <contracts.h>

#include <math.hpp>

using namespace std;

#define CLOSE_ENOUGH(A, B) (assert(abs((A) - (B)) < 1e-10))

int main()
{
	array<double, 3> axis;
	axis[0] = 1;
	axis[1] = 0;
	axis[2] = 0;

	quaternion<double>
		q = quaternion_from_rotation(axis, 90 * deg2rad),
		qq = quaternion_from_rotation(axis, 172 * deg2rad);

	{
		const quaternion<double> conj(q.conjugate());

		assert((q + conj) == (q.scalar() * 2));

		{
			const quaternion<double> tmp(q - conj);

			assert(tmp.scalar() == 0);
			assert(tmp.vector() == (q.vector() * 2));
		}

		assert(q.norm() == conj.norm());

		CLOSE_ENOUGH((q * qq).norm(), q.norm() * qq.norm());

		{
			quaternion<double> r(q * qq);

			//			assert((r * qq.inverse()) == q);
			//			assert((q.inverse() * r) == qq);
		}
	}

	cout
		<< q << endl
		<< q.inverse().inverse() << endl;

	return EXIT_SUCCESS;
}
