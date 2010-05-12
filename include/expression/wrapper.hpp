#ifndef H_EXPRESSION_WRAPPER
#define H_EXPRESSION_WRAPPER

#include <ostream>

#include "base.hpp"

namespace expression
{
	template <typename Value, typename Param = void_t>
	class wrapper : public base<Value, Param>
	{
	public:

		typedef Param param_type;

		typedef Value value_type;

		wrapper(value_type value) : _value(value)
		{}

		/**
		 * If there is an argument, ignore it.
		 */
		const value_type &eval(param_type) const
		{
			return eval();
		}

		const value_type &eval() const
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

	template <typename T>
	wrapper<T>
	wrap(T value)
	{
		return wrapper<T>(value);
	}

} // namespace expression

#endif // H_EXPRESSION_WRAPPER

