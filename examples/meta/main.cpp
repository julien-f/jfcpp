#include <cstdlib>
#include <iostream>

#include <jfcpp/meta/enable_if.hpp>
#include <jfcpp/meta/is_a.hpp>
#include <jfcpp/meta/logic.hpp>
#include <jfcpp/meta/yes_no.hpp>

using namespace std;

using jfcpp::meta::enable_if;
using jfcpp::meta::is_a;
using jfcpp::meta::no_t;
using jfcpp::meta::yes_t;

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

// template <class T>
// struct has_member
// {
// 	template <class C> static
// 	yes_t
// 	_check(char[sizeof(&C::test)] *p);

// 	template <class C> static
// 	no_t
// 	_check(char *p);

// 	static const bool value = sizeof(_check<T>(0)) == sizeof(yes_t);
// };

// From: http://stackoverflow.com/questions/1005476/how-to-detect-whether-there-is-a-specific-member-variable-in-class
template<typename T>
struct has_member
{
	struct fallback { void test(); }; // introduce the member
	struct derived : T, fallback { };

	template<typename C, C> struct ChT;

	template<typename C> static no_t f(ChT<void (fallback::*)(), &C::test>*);
	template<typename C> static yes_t f(...);

	static const bool value = sizeof(f<derived>(0)) == sizeof(yes_t);
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

	cout << has_member<C>::value << endl;
	cout << has_member<D>::value << endl;

	return EXIT_SUCCESS;
}
