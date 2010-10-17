#include "../common.hpp"

// No need to include “gmpxx.h” because this file is only used if
//__GMP_PLUSPLUS__ is defined.

JFCPP_NAMESPACE_BEGIN

template <>
bool
is_even<mpz_class>(const mpz_class &x)
{
	return mpz_even_p(x.get_mpz_t());
}

template <>
bool
is_odd<mpz_class>(const mpz_class &x)
{
	return mpz_odd_p(x.get_mpz_t());
}

template <>
mpz_class
exp_mod<mpz_class>(const mpz_class &x, const mpz_class &k, const mpz_class &n)
{
	mpz_class result;

	mpz_powm(result.get_mpz_t(), x.get_mpz_t(), k.get_mpz_t(), n.get_mpz_t());

	return result;
}

template <>
mpz_class
gcd<mpz_class>(const mpz_class &a, const mpz_class &b)
{
	mpz_class result;

	mpz_gcd(result.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());

	return result;
}

template <>
mpz_class
inverse_mod<mpz_class>(const mpz_class &x, const mpz_class &n)
{
	mpz_class result;

	mpz_invert(result.get_mpz_t(), x.get_mpz_t(), n.get_mpz_t());

	return result;
}

template <>
mpz_class
lcm<mpz_class>(const mpz_class &a, const mpz_class &b)
{
	mpz_class result;

	mpz_lcm(result.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());

	return result;
}

JFCPP_NAMESPACE_END
