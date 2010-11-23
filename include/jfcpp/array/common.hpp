public:

/**
 *
 */
typedef T value_type;

/**
 *
 */
typedef const value_type *const_iterator;

/**
 *
 */
typedef const value_type &const_reference;

/**
 *
 */
typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

/**
 *
 */
typedef value_type *iterator;

/**
 *
 */
typedef value_type &reference;

/**
 *
 */
typedef std::reverse_iterator<iterator> reverse_iterator;

/**
 *
 */
typedef value_type *pointer;

/**
 *
 */
reference
at(size_t i)
{
	if (i >= this->size())
	{
		throw std::out_of_range("no such index");
	}

	return (*this)[i];
}
const_reference
at(size_t i) const
{
	return const_cast<array *>(this)->at(i);
}

/**
 *
 */
iterator
begin()
{
	return this->_data;
}
const_iterator
begin() const
{
	return this->_data;
}

/**
 *
 */
iterator
end()
{
	return (this->_data + this->size());
}
const_iterator
end() const
{
	return (this->_data + this->size());
}

/**
 *
 */
bool
is_valid_index(size_t i) const
{
	return (i < this->size());
}

/**
 *
 */
void
print(std::ostream &s) const
{
	this->print(s, ' ');
}
template <typename Separator>
void
print(std::ostream &s, const Separator &separator) const
{
	// More convenient than *this.
	const array &self = *this;

	const size_t n = self.size();

	if (n != 0)
	{
		s << self[0];
		for (size_t i = 1; i < n; ++i)
		{
			s << separator << self[i];
		}
	}
}

/**
 *
 */
reverse_iterator
rbegin()
{
	return reverse_iterator(this->end());
}
const_reverse_iterator
rbegin() const
{
	return reverse_iterator(this->end());
}

/**
 *
 */
reverse_iterator
rend()
{
	return reverse_iterator(this->begin());
}
const_reverse_iterator
rend() const
{
	return reverse_iterator(this->begin());
}

/**
 *
 */
reference
operator[](size_t i)
{
	requires(i < this->size());

	return this->_data[i];
}
const_reference
operator[](size_t i) const
{
	return const_cast<array &>(*this)[i];
}

/**
 *
 */
template <typename T2, size_t S2>
bool
operator==(const array<T2, S2> &a) const
{
	return ((this->size() == a.size()) &&
	        std::equal(this->begin(), this->end(), a.begin()));
}

/**
 *
 */
template <typename T2>
bool
operator<(const T2 &val) const
{
	const array &self = *this;

	for (size_t i = 0; i < this->size(); ++i)
	{
		if (!(self[i] < val))
		{
			return false;
		}
	}

	return true;
}

/**
 *
 */
template <typename T2>
bool
operator<=(const T2 &val) const
{
	const array &self = *this;

	for (size_t i = 0; i < this->size(); ++i)
	{
		if (!(self[i] <= val))
		{
			return false;
		}
	}

	return true;
}

/**
 *
 */
template <typename T2, size_t S2>
bool
operator<(const array<T2, S2> &a) const
{
	requires(this->size() == a.size());

	const array &self = *this;

	for (size_t i = 0; i < this->size(); ++i)
	{
		if (!(self[i] < a[i]))
		{
			return false;
		}
	}

	return true;
}

/**
 *
 */
template <typename T2, size_t S2>
bool
operator<=(const array<T2, S2> &a) const
{
	requires(this->size() == a.size());

	const array &self = *this;

	for (size_t i = 0; i < this->size(); ++i)
	{
		if (!(self[i] <= a[i]))
		{
			return false;
		}
	}

	return true;
}

/**
 *
 */
array &
operator=(const array &a)
{
	return this->operator= <value_type, S>(a);
}
template <typename T2, size_t S2>
array &
operator=(const array<T2, S2> &a)
{
	requires(this->size() == a.size());

	std::copy(a.begin(), a.end(), this->begin());

	return *this;
}

#define ARRAY_OPERATION(OP, FUNC_NAME) \
template <typename T2, size_t S2> \
array & \
operator OP##=(const array<T2, S2> &a) \
{ \
	requires(this->size() == a.size()); \
 \
	algorithm::apply(this->begin(), this->end(), a.begin(), \
	                 functional::FUNC_NAME##_assign<value_type, T2>()); \
 \
	return *this; \
} \
template <typename T2> \
array & \
operator OP##=(const T2 &s) \
{ \
	algorithm::apply(this->begin(), this->end(), \
	                 std::bind2nd(functional::FUNC_NAME##_assign<value_type, T2>(), s)); \
 \
	return *this; \
}

ARRAY_OPERATION(+, plus)
ARRAY_OPERATION(-, minus)
ARRAY_OPERATION(*, multiplies)
ARRAY_OPERATION(/, divides)
ARRAY_OPERATION(%, modulus)

ARRAY_OPERATION(&, bit_and)
ARRAY_OPERATION(|, bit_or)
ARRAY_OPERATION(<<, bit_shift_left)
ARRAY_OPERATION(>>, bit_shift_right)
ARRAY_OPERATION(^, bit_xor)

#undef ARRAY_OPERATION

/**
 *
 */
template <typename T2>
array &
operator=(const T2 &s)
{
	std::fill(this->begin(), this->end(), s);

	return *this;
}

private:
