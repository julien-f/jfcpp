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
typedef const value_type *const_pointer;

/**
 *
 */
const_reference at(size_t i) const
{
	if (i >= this->size())
	{
		throw std::out_of_range("no such index");
	}

	return (*this)[i];
}

/**
 *
 */
const_iterator begin() const
{
	return this->_raw;
}

/**
 *
 */
const_iterator end() const
{
	return (this->_raw + this->_size);
}

/**
 *
 */
const_pointer raw() const
{
	return this->_raw;
}

/**
 *
 */
const_reverse_iterator rbegin() const
{
	return reverse_iterator(this->end());
}

/**
 *
 */
const_reverse_iterator rend() const
{
	return reverse_iterator(this->begin());
}

/**
 *
 */
void set(const array_view<T> &ar)
{
	this->set(ar._size, ar._raw);
}

/**
 *
 */
size_t size() const
{
	return this->_size;
}

/**
 *
 */
const_reference operator[](size_t i) const
{
	requires(i < this->_size);

	return this->_raw[i];
}

/**
 *
 */
template <typename U>
bool operator==(const array_view<U> &a) const
{
	return ((this->_size == a.size()) &&
	        std::equal(this->begin(), this->end(), a.begin()));
}

/**
 *
 */
template <typename U>
bool operator<(const array_view<U> &a) const
{
	return std::lexicographical_compare(this->begin(), this->end(),
	                                    a.begin(), a .end());
}

private:

/**
 *
 */
size_t _size;
