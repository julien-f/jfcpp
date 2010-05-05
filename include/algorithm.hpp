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

#include <iterator>

namespace algorithm
{
	namespace details
	{
		template <class InputIterator, class UnaryFunction, class IteratorCategory>
		void
		apply(InputIterator first, InputIterator end, UnaryFunction f, IteratorCategory)
		{
			for (; first != end; ++first)
			{
				f(*first);
			}
		}

		template <class InputIterator1, class InputIterator2,
		          class BinaryFunction, class IteratorCategory1,
		          class IteratorCategory2>
		void
		apply(InputIterator1 first1, InputIterator1 end1, InputIterator2 first2,
		      BinaryFunction f, IteratorCategory1, IteratorCategory2)
		{
			for (; first1 != end1; ++first1, ++first2)
			{
				f(*first1, *first2);
			}
		}

#		if defined(_OPENMP) && (_OPENMP == 200805)
		template <class InputIterator, class UnaryFunction>
		void
		apply(InputIterator first, InputIterator end, UnaryFunction f,
		      std::random_access_iterator_tag)
		{
#			pragma omp parallel for
			for (InputIterator it = first; it != end; ++it)
			{
				f(*it);
			}
		}

		template <class InputIterator1, class InputIterator2,
		          class BinaryFunction>
		void
		apply(InputIterator1 first1, InputIterator1 end1, InputIterator2 first2,
		      BinaryFunction f, std::random_access_iterator_tag,
		      std::random_access_iterator_tag)
		{
#			pragma omp parallel for
			for (InputIterator1 it = first1; it != end1; ++it)
			{
				f(*it, *first2);
				++first2;
			}
		}
#		endif
	} // namespace details


	/**
	 * Applies an unary function to a range.
	 *
	 * There is no defined order and the implementation might parallelize the
	 * execution with OpenMP if possible (the iterator is a random access
	 * iterator, OpenMP 3.0 is available and enabled).
	 */
	template <class InputIterator, class UnaryFunction>
	void
	apply(InputIterator first, InputIterator end, UnaryFunction f)
	{
		typedef std::iterator_traits<InputIterator> iterator_traits;
		typedef typename iterator_traits::iterator_category iterator_category;

		details::apply(first, end, f, iterator_category());
	}

	/**
	 * Binary version of the above function.
	 */
	template <class InputIterator1, class InputIterator2, class BinaryFunction>
	void
	apply(InputIterator1 first1, InputIterator1 end1, InputIterator2 first2,
	         BinaryFunction f)
	{
		typedef std::iterator_traits<InputIterator1> iterator_traits1;
		typedef typename iterator_traits1::iterator_category iterator_category1;

		typedef std::iterator_traits<InputIterator2> iterator_traits2;
		typedef typename iterator_traits2::iterator_category iterator_category2;

		details::apply(first1, end1, first2, f, iterator_category1(),
		               iterator_category2());
	}

} // namespace algorithm

#endif // H_ALGORITHM
