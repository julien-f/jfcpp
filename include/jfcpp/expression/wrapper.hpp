#ifndef H_JFCPP_EXPRESSION_WRAPPER
#define H_JFCPP_EXPRESSION_WRAPPER

#include <ostream>

#include "../common.hpp"

JFCPP_NAMESPACE_BEGIN

namespace expression
{
	template <typename Value>
	class wrapper : public base<Value>
	{
	public:

		typedef typename base<Value>::value_type value_type;

		wrapper(value_type value) : _value(value)
		{}

		/**
		 * If there is an argument, ignore it.
		 */
		template <typename T>
		const value_type &
		eval(T) const
		{
			return eval();
		}

		const value_type &
		eval() const
		{
			return _value;
		}

		friend
		std::ostream &
		operator << (std::ostream &s, const wrapper &w)
		{
			s << w._value;
			return s;
		}

	private:

		const value_type _value;
	};
} // namespace expression

JFCPP_NAMESPACE_END

#endif // H_JFCPP_EXPRESSION_WRAPPER
