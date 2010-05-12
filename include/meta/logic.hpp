#ifndef H_META_LOGIC
#define H_META_LOGIC

namespace meta
{
	template <bool B1, bool B2>
	struct and_
	{
		static const bool value = false;
	};
	template <>
	struct and_<true, true>
	{
		static const bool value = true;
	};

	template <bool B1, bool B2>
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

#endif // H_META_LOGIC
