#ifndef H_META_YES_NO
#define H_META_YES_NO

namespace meta
{
	struct yes_t {char _a[2];}; // sizeof(yes_t) > 1

	typedef char no_t; // sizeof(no_t) == 1
} // namespace meta

#endif // H_META_YES_NO
