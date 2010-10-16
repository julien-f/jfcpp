#ifndef H_JFCPP_EXPRESSION_BASE
#define H_JFCPP_EXPRESSION_BASE

#include "../common.hpp"

JFCPP_NAMESPACE_BEGIN

namespace expression
{
	struct void_t
	{
		/**
		 * This type can be constructed without any parameter.
		 */
		void_t() {}

		/**
		 * If there is a parameter, it will be ignored.
		 */
		template <typename T>
		void_t(T) {}
	};

	template <typename Value>
	class base
	{
	public:

		/**
		 *
		 */
		typedef Value value_type;
	};
} // namespace expression

JFCPP_NAMESPACE_END

#endif // H_JFCPP_EXPRESSION_BASE
