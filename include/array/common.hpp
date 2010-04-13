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
inline reference at(size_t i)
{
	if (i >= this->size())
	{
		throw std::out_of_range("no such index");
	}

	return (*this)[i];
}
inline const_reference at(size_t i) const
{
	return const_cast<array<value_type, S> *>(this)->at(i);
}

/**
 *
 */
inline iterator begin()
{
	return this->_data;
}
inline const_iterator begin() const
{
	return this->_data;
}

/**
 *
 */
inline iterator end()
{
	return (this->_data + this->size());
}
inline const_iterator end() const
{
	return (this->_data + this->size());
}

/**
 *
 */
inline void fill(const_reference value)
{
	std::fill(this->begin(), this->end(), value);
}

/**
 *
 */
inline reverse_iterator rbegin()
{
	return reverse_iterator(this->end());
}
inline const_reverse_iterator rbegin() const
{
	return reverse_iterator(this->end());
}

/**
 *
 */
inline reverse_iterator rend()
{
	return reverse_iterator(this->begin());
}
inline const_reverse_iterator rend() const
{
	return reverse_iterator(this->begin());
}

/**
 *
 */
inline reference operator[](size_t i)
{
	requires(i < this->size());

	return this->_data[i];
}
inline const_reference operator[](size_t i) const
{
	return const_cast<array<value_type, S> &>(*this)[i];
}

/**
 *
 */
template<typename T2, size_t S2> inline
bool operator==(const array<T2, S2> &a) const
{
	return ((this->size() == a.size()) &&
	        std::equal(this->begin(), this->end(), a.begin()));
}

/**
 *
 */
template<typename T2, size_t S2> inline
bool operator<(const array<T2, S2> &a) const
{
	return std::lexicographical_compare(this->begin(), this->end(),
	                                    a.begin(), a .end());
}

/**
 *
 */
template<typename T2, size_t S2> inline
array<value_type, S> &operator=(const array<T2, S2> &a)
{
	requires(this->size() == a.size());

	std::copy(a.begin(), a.end(), this->begin());

	return *this;
}

private:
