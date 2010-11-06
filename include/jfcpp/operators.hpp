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

#ifndef H_JFCPP_OPERATORS
#define H_JFCPP_OPERATORS

#include "common.hpp"
#include "meta/enable_if.hpp"
#include "meta/is_a.hpp"

JFCPP_NAMESPACE_BEGIN

namespace operators
{
#	define JFCPP_BINARY_OPERATOR(NAME, OP) \
	template <typename T1> \
	struct NAME \
	{ \
		template <typename T2> friend \
		T1 \
		operator OP(T1 lhs, const T2 &rhs) \
		{ \
			return (lhs OP##= rhs); \
		} \
	}

#	define JFCPP_BINARY_OPERATOR_COMMUTATIVE(NAME, OP) \
	template <typename T1> \
	struct NAME \
	{ \
		template <typename T2> friend \
		T1 \
		operator OP(T1 lhs, const T2 &rhs) \
		{ \
			return (lhs OP##= rhs); \
		} \
		template <typename T2> friend \
		typename meta::enable_if<!meta::is_a<NAME<T2>, T2>::value, T1>::type \
		operator OP(const T2 &lhs, T1 rhs) \
		{ \
			return (rhs OP##= lhs); \
		} \
	}


	JFCPP_BINARY_OPERATOR(dividable, /);
	JFCPP_BINARY_OPERATOR(modable, %);
	JFCPP_BINARY_OPERATOR(left_shiftable, <<);
	JFCPP_BINARY_OPERATOR(right_shiftable, >>);
	JFCPP_BINARY_OPERATOR(subtractable, -);

	JFCPP_BINARY_OPERATOR_COMMUTATIVE(addable, +);
	JFCPP_BINARY_OPERATOR_COMMUTATIVE(andable, &);
	JFCPP_BINARY_OPERATOR_COMMUTATIVE(multipliable, *);
	JFCPP_BINARY_OPERATOR_COMMUTATIVE(orable, |);
	JFCPP_BINARY_OPERATOR_COMMUTATIVE(xorable, ^);

	template <typename T1>
	struct equality_comparable
	{
		template <typename T2> friend
		typename meta::enable_if<!meta::is_a<equality_comparable<T2>, T2>::value, bool>::type
		operator ==(const T2 &lhs, const T1 &rhs)
		{
			return rhs.operator ==(lhs);
		}
		template <typename T2> friend
		bool
		operator !=(const T1 &lhs, const T2 &rhs)
		{
			return !static_cast<bool>(lhs == rhs);
		}
		template <typename T2> friend
		typename meta::enable_if<!meta::is_a<equality_comparable<T2>, T2>::value, bool>::type
		operator !=(const T2 &lhs, const T1 &rhs)
		{
			return !static_cast<bool>(lhs == rhs);
		}
	};

#	undef JFCPP_BINARY_OPERATOR
#	undef JFCPP_BINARY_OPERATOR_COMMUTATIVE
} // namespace operators

JFCPP_NAMESPACE_END

#endif
