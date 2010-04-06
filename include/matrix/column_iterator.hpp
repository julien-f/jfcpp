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

#include <cstddef>
#include <iterator>

namespace matrix_details
{
	template<typename T>
	class column_iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:

		/**
		 *
		 */
		column_iterator();

		/**
		 *
		 */
		column_iterator(const column_iterator &it);

		/**
		 *
		 */
		column_iterator(matrix<T> &m, size_t i, size_t j);

		/**
		 *
		 */
		bool operator==(const column_iterator &it) const;

		/**
		 *
		 */
		bool operator!=(const column_iterator &it) const;

		/**
		 *
		 */
		T &operator*();

		/**
		 *
		 */
		column_iterator &operator++();

		/**
		 *
		 */
		column_iterator operator++(int);

		/**
		 *
		 */
		T *operator->();

	private:

		/**
		 *
		 */
		matrix<T> *_matrix;

		/**
		 *
		 */
		size_t _i;

		/**
		 *
		 */
		size_t _j;
	};

#	include "column_iterator/implementation.hpp"
}
