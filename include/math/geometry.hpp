/**
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Julien Fontanet <julien.fontanet@isonoe.net>
 */

#ifndef H_JFCPP_MATH_GEOMETRY
#define H_JFCPP_MATH_GEOMETRY

#include <cmath>
#include <cstddef>

#include "../array.hpp"
#include "../common.hpp"
#include "../math.hpp"

JFCPP_NAMESPACE_BEGIN

/**
 *
 *
 * Is this only true for a convex polygon?
 */
template <size_t N, typename Type, size_t Dim>
bool
is_inside_convex_polygon(const array<array<Type, Dim>, N> &vertices,
                         const array<Type, Dim> &point)
{
	const double epsilon = 1e-8;

	double sum = 0;

	for (size_t i = 0; i < N; ++i)
	{
		// i + 1
		size_t ip1 = i + 1;
		if (ip1 == N)
		{
			ip1 = 0;
		}

		const array<Type, Dim>
			a(vertices[i] - point),
			b(vertices[ip1] - point);

		const double norm_product(norm_2(a) * norm_2(b));

		if (norm_product < epsilon) // On a node, consider this inside.
		{
			return true;
		}

		double angle = acos(double(sprod(a, b)) / norm_product);

		sum += angle;
	}

	return (abs(sum - PI_TIMES_2) < epsilon);
}

JFCPP_NAMESPACE_END

#endif // H_JFCPP_MATH_GEOMETRY
