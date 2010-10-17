/**
 * This class is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This class is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this class.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author:
 *   Julien Fontanet <julien.fontanet@isonoe.net>
 */

#ifndef H_JFCPP_MATRIX_CONST_COLUMN_ITERATOR
#define H_JFCPP_MATRIX_CONST_COLUMN_ITERATOR

#include <cstddef>
#include <iterator>

#include "../common.hpp"
#include "column_iterator.hpp"

JFCPP_NAMESPACE_BEGIN

namespace matrix_details
{
	template<typename T>
	class const_column_iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:

		/**
		 *
		 */
		const_column_iterator();

		/**
		 *
		 */
		const_column_iterator(const column_iterator<T> &it);

		/**
		 *
		 */
		const_column_iterator(const const_column_iterator &it);

		/**
		 *
		 */
		const_column_iterator(const matrix<T> &m, size_t i, size_t j);

		/**
		 *
		 */
		bool operator==(const const_column_iterator &it) const;

		/**
		 *
		 */
		bool operator!=(const const_column_iterator &it) const;

		/**
		 *
		 */
		const T &operator*() const;

		/**
		 *
		 */
		const_column_iterator &operator++();

		/**
		 *
		 */
		const_column_iterator operator++(int);

		/**
		 *
		 */
		const T *operator->() const;

	private:

		/**
		 *
		 */
		const matrix<T> *_matrix;

		/**
		 *
		 */
		size_t _i;

		/**
		 *
		 */
		size_t _j;
	};

#	include "const_column_iterator/implementation.hpp"
}

JFCPP_NAMESPACE_END

#endif // H_JFCPP_MATRIX_CONST_COLUMN_ITERATOR
