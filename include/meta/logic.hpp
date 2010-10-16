#ifndef H_JFCPP_META_LOGIC
#define H_JFCPP_META_LOGIC

#include "../common.hpp"

JFCPP_NAMESPACE_BEGIN

namespace meta
{
	template <bool, bool>
	struct and_
	{
		static const bool value = false;
	};
	template <>
	struct and_<true, true>
	{
		static const bool value = true;
	};

	template <bool, bool>
	struct or_
	{
		static const bool value = true;
	};
	template <>
	struct or_<false, false>
	{
		static const bool value = false;
	};
} // namespace meta

JFCPP_NAMESPACE_END

#endif // H_JFCPP_META_LOGIC
