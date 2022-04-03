#pragma once

#include <stdexcept>

/// <summary> A dynamic array of elements, which automatically resizes to fit its content. </summary>
template<typename TItem>
class DynamicVector
{
private:
	TItem* data;
	size_t length;
	size_t capacity;

public:
	// CONSTRUCTOR.

	/// <summary> Initialize an empty vector. </summary>
	DynamicVector();

	// THE RULE OF 5.

	/// <summary> Initialize a vector with all the elements from the given vector. </summary>
	DynamicVector(const DynamicVector<TItem>& other);

	/// <summary> Initialize a vectors that 'steals' the content of the given vector. </summary>
	DynamicVector(DynamicVector<TItem>&& other);

	/// <summary> Destroy the vector and release all its resources. </summary>
	~DynamicVector();

	/// <summary> Copies the given vector to the current one and returns the current one. </summary>
	DynamicVector<TItem>& operator= (const DynamicVector<TItem>& other);

	/// <summary> Moves the given vector into the current one and returns the current one. </summary>
	DynamicVector<TItem>& operator= (DynamicVector<TItem>&& other);

	// PROPERTIES.

	/// <summary> Get the vector's length. </summary>
	size_t getLength() const;

	// METHODS.

private:
	/// <summary> Resizes the container to match the specified new capacity. If capacity is lower than the current length throws exception. </summary>
	void reserve(size_t newCapacity);

public:

	/// <summary> Add an element at the end of the vector. </summary>
	void add(const TItem& item);

	/// <summary> Get the non-const element at the specified index. If index is out of range throws exception. </summary>
	TItem& operator[](size_t index);
	const TItem& operator[](size_t index) const;

	/// <summary> Replaces the element at the specified index with the last one. If index is out of range throws exception. </summary>
	void removeFast(size_t index);

	/// <summary> Removes all the elements in the vector. </summary>
	void clear();

public:
	class Iterator
	{
	private:
		TItem* pointer;

	public:
		Iterator(TItem* pointer);

		TItem& operator*() const;
		Iterator& operator++();
		Iterator operator++(int);
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;
	};

	class ConstIterator
	{
	private:
		const TItem* pointer;

	public:
		ConstIterator(const TItem* pointer);

		const TItem& operator*() const;
		ConstIterator& operator++();
		ConstIterator operator++(int);
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;
	};

	Iterator begin();
	Iterator end();

	ConstIterator begin() const;
	ConstIterator end() const;
};


// Minimum capacity = length.
// Normal capacity = length * 2.
// Maximum capacity = length * 4.
// If capacity is less than minimum or greater than maximum, resize to normal.

// CONSTRUCTOR.

template <typename TItem>
DynamicVector<TItem>::DynamicVector() : data(nullptr), length(0), capacity(0) {}

// THE RULE OF 5.

template<typename TItem>
DynamicVector<TItem>::DynamicVector(const DynamicVector<TItem>& other) : DynamicVector<TItem>()
{
	*this = other;
}

template<typename TItem>
DynamicVector<TItem>::DynamicVector(DynamicVector<TItem>&& other) : DynamicVector<TItem>()
{
	*this = other;
}

template <typename TItem>
DynamicVector<TItem>::~DynamicVector()
{
	this->clear();
}

template <typename TItem>
DynamicVector<TItem>& DynamicVector<TItem>::operator= (const DynamicVector<TItem>& other)
{
	this->clear();

	for (size_t i = 0; i < other.getLength(); ++i)
		this->add(other[i]);

	return *this;
}

template <typename TItem>
DynamicVector<TItem>& DynamicVector<TItem>::operator= (DynamicVector<TItem>&& other)
{
	this->clear();

	this->data = other.data;
	this->length = other.length;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.length = 0;
	other.capacity = 0;

	return *this;
}


// PROPERTIES.

template <typename TItem>
size_t DynamicVector<TItem>::getLength() const
{
	return this->length;
}

// METHODS.

template <typename TItem>
void DynamicVector<TItem>::reserve(size_t newCapacity)
{
	if (newCapacity < this->length)
		throw std::out_of_range("The capacity must be greater or equal to the length.");

	if (newCapacity == this->capacity)
		return;

	TItem* newData = newCapacity > 0 ? new TItem[newCapacity] : nullptr;
	
	// Move all the items into the new container, then delete the old one.
	for (size_t i = 0; i < this->length; ++i)
		newData[i] = std::move(this->data[i]);

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

template <typename TItem>
void DynamicVector<TItem>::add(const TItem& item)
{
	// Handle reallocation.
	if (this->capacity < this->length + 1)
		this->reserve((this->length + 1) * 2);

	// Add the item on the next empty position.
	this->data[this->length++] = item;
}

template <typename TItem>
TItem& DynamicVector<TItem>::operator[](size_t index)
{
	if (index < 0 || index >= this->length)
		throw std::out_of_range("Index is out of range.");

	return this->data[index];
}

template <typename TItem>
const TItem& DynamicVector<TItem>::operator[](size_t index) const
{
	if (index < 0 || index >= this->length)
		throw std::out_of_range("Index is out of range.");

	return this->data[index];
}

template <typename TItem>
void DynamicVector<TItem>::removeFast(size_t index)
{
	if (index < 0 || index >= this->length)
		throw std::out_of_range("Index is out of range.");

	// If removed element is not the last element, replace it with the last one.
	if (index < this->length - 1)
		this->data[index] = std::move(this->data[this->length - 1]);

	--this->length;

	// Handle reallocation.
	if (this->capacity > this->length * 4)
		this->reserve(this->length * 2);
}

template <typename TItem>
void DynamicVector<TItem>::clear()
{
	for (size_t i = this->getLength(); i-- > 0; )
		this->removeFast(i);
}

// ITERATOR.

template <typename TItem>
DynamicVector<TItem>::Iterator::Iterator(TItem* ptr) : pointer(ptr) {}

template <typename TItem>
TItem& DynamicVector<TItem>::Iterator::operator*() const
{
	return *this->pointer;
}

template <typename TItem>
typename DynamicVector<TItem>::Iterator& DynamicVector<TItem>::Iterator::operator++()
{
	++this->pointer;
	return *this;
}

template <typename TItem>
typename DynamicVector<TItem>::Iterator DynamicVector<TItem>::Iterator::operator++(int)
{
	DynamicVector<TItem>::Iterator result(*this);
	++this->pointer;
	return result;
}

template<typename TItem>
bool DynamicVector<TItem>::Iterator::operator==(const Iterator& other) const
{
	return this->pointer == other.pointer;
}

template<typename TItem>
bool DynamicVector<TItem>::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

// CONST ITERATOR.

template <typename TItem>
DynamicVector<TItem>::ConstIterator::ConstIterator(const TItem* ptr) : pointer(ptr) {}

template <typename TItem>
const TItem& DynamicVector<TItem>::ConstIterator::operator*() const
{
	return *this->pointer;
}

template <typename TItem>
typename DynamicVector<TItem>::ConstIterator& DynamicVector<TItem>::ConstIterator::operator++()
{
	++this->pointer;
	return *this;
}

template <typename TItem>
typename DynamicVector<TItem>::ConstIterator DynamicVector<TItem>::ConstIterator::operator++(int)
{
	DynamicVector<TItem>::ConstIterator result(*this);
	++this->pointer;
	return result;
}

template<typename TItem>
bool DynamicVector<TItem>::ConstIterator::operator==(const ConstIterator& other) const
{
	return this->pointer == other.pointer;
}

template<typename TItem>
bool DynamicVector<TItem>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return !(*this == other);
}

// DYNAMIC VECTOR

template <typename TItem>
typename DynamicVector<TItem>::Iterator DynamicVector<TItem>::begin()
{
	return DynamicVector<TItem>::Iterator(this->data);
}

template <typename TItem>
typename DynamicVector<TItem>::Iterator DynamicVector<TItem>::end()
{
	return DynamicVector<TItem>::Iterator(this->data + this->length);
}

template <typename TItem>
typename DynamicVector<TItem>::ConstIterator DynamicVector<TItem>::begin() const
{
	return DynamicVector<TItem>::ConstIterator(this->data);
}

template <typename TItem>
typename DynamicVector<TItem>::ConstIterator DynamicVector<TItem>::end() const
{
	return DynamicVector<TItem>::ConstIterator(this->data + this->length);
}
