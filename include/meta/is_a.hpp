#ifndef H_META_IS_A
#define H_META_IS_A

#include "yes_no.hpp"

namespace meta
{
	/**
	 * is_a<Base, Derived>?
	 *
	 * Does not work with non-public inheritance.
	 */
	template <class Base, class Derived>
	struct is_a
	{
		static no_t _test(...);

		static yes_t _test(Base *);

		static Derived *_from;

		static const bool value = (sizeof(_test(_from)) == sizeof(yes_t));
	};

	template <class A>
	struct is_a<A, A>
	{
		static const bool value = true;
	};
} // namespace meta

#endif // H_META_IS_A
