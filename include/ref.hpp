#ifndef H_REF
#define H_REF

template <typename T>
class const_referencer;

template <typename T>
class referencer
{
public:

	explicit referencer(T &x) : _x(x)
	{}

	operator T &() const
	{
		return _x;
	}

	referencer &
	operator=(const referencer &r)
	{
		return operator= <T>(r);
	}
	const referencer &
	operator=(const referencer &r) const
	{
		return operator= <T>(r);
	}

	/**
	 * A “refencer” may be assigned even if it is “const”.
	 */
#	define ASSIGNMENT(PARAM_TYPE) \
	template <typename T2> \
	referencer & \
	operator=(const PARAM_TYPE &x) \
	{ \
		_x = x; \
		return *this; \
	} \
	template <typename T2> \
	const referencer & \
	operator=(const PARAM_TYPE &x) const \
	{ \
		_x = x; \
		return *this; \
	}

	ASSIGNMENT(T2)
	ASSIGNMENT(referencer<T2>)
	ASSIGNMENT(const_referencer<T2>)

#	undef ASSIGNMENT

private:

	T &_x;
};

template <typename T>
class const_referencer
{
public:

	explicit const_referencer(const T &x) : _x(x)
	{}

	const_referencer(referencer<T> r) : _x(r)
	{}

	operator const T &() const
	{
		return _x;
	}

private:

	const T &_x;
};

template <typename T>
referencer<T>
ref(T &x)
{
	return referencer<T>(x);
}

template <typename T>
const_referencer<T>
cref(const T &x)
{
	return const_referencer<T>(x);
}

#endif // H_REF
