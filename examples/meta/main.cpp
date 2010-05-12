#include <cstdlib>
#include <iostream>

#include <meta/enable_if.hpp>
#include <meta/is_a.hpp>
#include <meta/logic.hpp>
#include <meta/yes_no.hpp>

using namespace std;
using namespace meta;

template <bool B>
typename enable_if<B>::type
test_enable_if()
{
	cout << "Yes" << endl;
}

template <bool B>
typename enable_if<!B>::type
test_enable_if()
{
	cout << "No" << endl;
}

template <class T>
struct has_member
{
	template <class C> static
	yes_t
	_check(int i = sizeof(&C::test));

	template <class C> static
	no_t
	_check(int i);

	static const bool value = sizeof(_check<T>()) == sizeof(yes_t);
};


struct A
{};

struct B : public A
{};

struct C
{};

struct D
{
	void test() {}
};

int main()
{
	test_enable_if<true>(); // Should print
	test_enable_if<false>();

	test_enable_if<is_a<A, A>::value>();
	test_enable_if<is_a<A, B>::value>();

	test_enable_if<is_a<A, C>::value>();
	test_enable_if<is_a<B, A>::value>();

	test_enable_if<has_member<C>::value>();
	test_enable_if<has_member<D>::value>();

	return EXIT_SUCCESS;
}
