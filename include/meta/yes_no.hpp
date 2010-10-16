#ifndef H_JFCPP_META_YES_NO
#define H_JFCPP_META_YES_NO

#include "../common.hpp"

JFCPP_NAMESPACE_BEGIN

namespace meta
{
	struct yes_t {char _a[2];}; // sizeof(yes_t) > 1

	typedef char no_t; // sizeof(no_t) == 1
} // namespace meta

JFCPP_NAMESPACE_END

#endif // H_JFCPP_META_YES_NO
