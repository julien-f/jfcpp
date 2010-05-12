// To properly test inclusion, the tested file must be the first included.
#include <meta/enable_if.hpp>
#include <meta/is_a.hpp>
#include <meta/logic.hpp>

#include <cstdlib>

#include <contracts.h>

using namespace meta;

template <bool B>
typename enable_if<B, bool>::type
enable_if_tester()
{
	return true;
}

template <bool B>
typename enable_if<!B, bool>::type
enable_if_tester()
{
	return false;
}

struct A
{};

struct B : public A
{};

struct C
{};

/**
 * This function must be used because assert is a macro, and,
 * consequently has problems dealing with multiple template
 * parameters.
 */
template <typename T>
void
cmp(T lhs, T rhs)
{
	assert(lhs == rhs);
}

int main()
{
	assert(enable_if_tester<true>() == true);
	assert(enable_if_tester<false>() == false);

	cmp(and_<true, true>::value, true);
	cmp(and_<true, false>::value, false);
	cmp(and_<false, true>::value, false);
	cmp(and_<false, false>::value, false);

	cmp(or_<true, true>::value, true);
	cmp(or_<true, false>::value, true);
	cmp(or_<false, true>::value, true);
	cmp(or_<false, false>::value, false);

	cmp(is_a<A, A>::value, true);
	cmp(is_a<A, B>::value, true);
	cmp(is_a<B, A>::value, false);
	cmp(is_a<A, C>::value, false);
	cmp(is_a<C, A>::value, false);

	return EXIT_SUCCESS;
}
