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

