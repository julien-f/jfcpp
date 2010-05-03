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

#ifndef H_ALGORITHM
#define H_ALGORITHM

#include <algorithm>

namespace algorithm
{
	using std::for_each;

	/**
	 *
	 */
	template <class InputIterator1, class InputIterator2, class BinaryOperator>
	BinaryOperator
	for_each(InputIterator1 first1, InputIterator1 end1, InputIterator2 first2,
	         BinaryOperator op)
	{
		for (; first1 != end1; ++first1, ++first2)
		{
			op(*first1, *first2);
		}

		return op;
	}

} // namespace algorithm

#endif // H_ALGORITHM
