#ifndef H_JFCPP_LAMBDA
#define H_JFCPP_LAMBDA

#include "common.hpp"

JFCPP_NAMESPACE_BEGIN

template <typename Expression>
class lambda
{
public:

	typedef typename Expression::value_type value_type;

	lambda(Expression e) : _e(e)
	{}

	const Expression &expression() const
	{
		return _e;
	}

	value_type operator() () const
	{
		return _e.eval();
	}

	template <typename Param>
	value_type operator() (Param p) const
	{
		return _e.eval(p);
	}

private:

	const Expression _e;
};

JFCPP_NAMESPACE_END

#endif // H_JFCPP_LAMBDA
