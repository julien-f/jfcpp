#ifndef H_EXPRESSION_BASE
#define H_EXPRESSION_BASE

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

	template <typename Value, typename Param = void_t>
	class base
	{
	public:

		/**
		 *
		 */
		typedef Param param_type;

		/**
		 *
		 */
		typedef Value value_type;
	};
} // namespace expression

#endif // H_EXPRESSION_BASE

