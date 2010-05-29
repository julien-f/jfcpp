#ifndef H_META_ENABLE_IF
#define H_META_ENABLE_IF

namespace meta
{
	/**
	 * This structure allows to switch between overloaded
	 * function using the paradigme SFINAE (Substitution
	 * Failure Is Not An Error).
	 *
	 * Code from: http://www.drdobbs.com/184401659
	 */
	template <bool, class T = void>
	struct enable_if
	{
		typedef T type;
	};
	template <class T>
	struct enable_if<false, T>
	{};
} // namespace meta

#endif // H_META_ENABLE_IF
