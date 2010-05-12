#ifndef H_EXPRESSION_WRAPPER
#define H_EXPRESSION_WRAPPER

#include "base.hpp"

namespace expression
{
	template <typename T>
	class wrapper : base<T>
	{
	public:

		typedef typename base<T>::param_type param_type;

		typedef T value_type;

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

