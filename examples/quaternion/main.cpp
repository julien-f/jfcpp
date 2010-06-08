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

		assert(q == q.inverse().inverse());

		{
			quaternion<double> r(q * qq);

			//			assert((r * qq.inverse()) == q);
			//			assert((q.inverse() * r) == qq);
		}
	}

	axis[0] = 1;
	axis[1] = 0;
	axis[2] = 0;
	quaternion<double> rx = quaternion_from_rotation(axis, 90 * deg2rad);

	axis[0] = 0;
	axis[1] = 1;
	axis[2] = 0;
	quaternion<double> ry = quaternion_from_rotation(axis, 90 * deg2rad);

	axis[0] = 0;
	axis[1] = 0;
	axis[2] = 1;
	quaternion<double> rz = quaternion_from_rotation(axis, 90 * deg2rad);

	array<double, 3> vector;
	vector[0] = 1;
	vector[1] = 0;
	vector[2] = 0;

	cout
		<< "Orginal vector: " << vector << endl
		<< "Rotated around x: " << rotate_with_quaternion(vector, rx) << endl
		<< "Rotated around y: " << rotate_with_quaternion(vector, ry) << endl
		<< "Rotated around z: " << rotate_with_quaternion(vector, rz) << endl
		<< "Rotated around x and y: " << rotate_with_quaternion(vector, ry * rx) << endl
		<< "Rotated around x, y and z: " << rotate_with_quaternion(vector, rz * ry * rx) << endl;

	return EXIT_SUCCESS;
}
