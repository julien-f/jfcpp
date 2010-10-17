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

#ifndef H_JFCPP_VARIOUS
#define H_JFCPP_VARIOUS

#include <sstream>
#include <stdexcept>
#include <string>

#include "common.hpp"

JFCPP_NAMESPACE_BEGIN

template <typename T>
T
from_string(const std::string &str)
{
	std::istringstream ss(str);

	T result;

	ss >> result;

	if (ss.fail())
	{
		throw std::runtime_error("invalid cast");
	}

	return result;
}

template <typename T>
std::string
to_string(const T &x)
{
	std::ostringstream ss;

	ss << x;

	return ss.str();
}

JFCPP_NAMESPACE_END

#endif
