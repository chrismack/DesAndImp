#pragma once 

#ifndef DYNARRAY_CPP
#define DYNARRAY_CPP

#include "DynArray.h"

/*
 * Default un-constructed, buffer size = 6
 */
template <class ComponentType>
DynArray<ComponentType>::DynArray()
{
	type_ = new ComponentType[6];
	size_ = 0;
	capacity_ = 6;
}

/*
 * Copy constructor
 */
template <class ComponentType>
DynArray<ComponentType>::DynArray(DynArray& copy)
{
	type_ = new ComponentType[copy.size()];
	size_ = copy.size();
	capacity_ = copy.capacity();
	for (unsigned int i = 0; i < size_; ++i)
	{
		type_[i] = copy.get(i);
	}
}

/*
 * Constructor with specific size elements default construced
 */
template <class ComponentType>
DynArray<ComponentType>::DynArray(unsigned int indexSize)
{
	type_ = new ComponentType[indexSize];
	for (int i = 0; i < indexSize; i++)
	{
		type_[i] = ComponentType();
	}
	size_ = 0;
	capacity_ = indexSize;
}

/*
 * Constructor with specific size and element not default constructed
 */
template<class ComponentType>
DynArray<ComponentType>::DynArray(unsigned int indexSize, bool clean)
{
		type_ = new ComponentType[indexSize];
		size_ = 0;
		capacity_ = indexSize;
}

/*
 * Constructor sets all elements to predefined value
 */
template <class ComponentType>
DynArray<ComponentType>::DynArray(ComponentType type)
{
	type_ = new ComponentType[6];
	for (int i = 0; i < 6; i++)
	{
		type_[i] = type;
	}
	size_ = 6;
	capacity_ = 6;
}

/*
 * Deconstructor 
 */
template <class ComponentType>
DynArray<ComponentType>::~DynArray()
{
	delete[] type_;
}

/*
 * Returns number of elements in array
 */
template <class ComponentType>
int DynArray<ComponentType>::size() const
{
	return size_;
}

/*
 * Returns the number of elements the array can hold
 */
template <class ComponentType>
int DynArray<ComponentType>::capacity() const
{
	return capacity_;
}

/*
 * Returns true if the array doesn't contain any elements
 */
template <class ComponentType>
bool DynArray<ComponentType>::empty() const
{
	return size_ == 0;
}

/*
 * Returns true if the element in arrays are the same size and order
 */
template<class ComponentType>
bool DynArray<ComponentType>::equality(DynArray &dynarray) const
{
	if (size_ == dynarray.size())
	{
		for (int i = 0; i < size_; i++)
		{
			if (type_[i] != dynarray[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

/*
 * Adds element to back of array
 * Resizes array if full by * 1.5
 */
template <class ComponentType>
void DynArray<ComponentType>::push_back(ComponentType compType)
{
	// If the buffer is full
	if (size_ == capacity_)
	{
		capacity_ *= 1.5;
		reserve(capacity_);
	}

	type_[size_] = compType;
	size_++;
}

/*
 * Removes the last element in array
 */
template <class ComponentType>
void DynArray<ComponentType>::pop_back()
{
	//Array cannot be empty
	assert(size_ > 0);
	type_[size_ - 1] = ComponentType();
	size_--;

}

/*
 * adds element at front of the array moves all elements back
 */
template<class ComponentType>
void DynArray<ComponentType>::push_front(ComponentType compType)
{
	insert(0, compType);
}

/*
 * Removes first element in the array moves all other elements foward 
 */
template<class ComponentType>
void DynArray<ComponentType>::pop_front()
{
	remove(0);
}

/*
 * Resizes array to specific size
 * Copies all elements to new buffer 
 */
template<class ComponentType>
void DynArray<ComponentType>::reserve(int size)
{
	// Create a temp buffer to save content while new address is set
	ComponentType *tempBuffer = new ComponentType[size];
	// Loop through all elements in existing buffer
	for (int i = 0; i < size_; i++)
	{
		tempBuffer[i] = type_[i];
	}

	// Return old memory location to heap
	delete[] type_;
	type_ = tempBuffer;
	capacity_ = size;
}

/*
 * set array size to equal number of elements in array
 */
template<class ComponentType>
void DynArray<ComponentType>::shrink()
{
	assert(capacity_ > size_)
	reserve(capacity_);
	
}

/*
 * Insert element at specific array
 * moves all elements after array back
 * Add more memery if needed
 */
template<class ComponentType>
void DynArray<ComponentType>::insert(const int index, const ComponentType value)
{
	// Check insert is after last element
	assert(index <= size_);
	// Check if more memory is needed
	if (size_ + 1 > capacity_)
	{
		reserve(capacity_ *= 1.5);
	}

	// Loop backwards through elements starting at last element
	for (int i = size_ - 1; i >= index; i--)
	{
		// Move each element back 
		type_[i + 1] = type_[i];
	}
	// Insert element into specified index
	type_[index] = value;
	size_++;
}

/*
 * Remove element at specific array
 * Move all elements after index forward
 */
template<class ComponentType>
void DynArray<ComponentType>::remove(const int index)
{
	assert(index < size_);
	type_[index] = ComponentType();
	for (int i = index; i < size_ - 1; i++)
	{
		type_[i] = type_[i + 1];
	}
	size_--;
}

/*
 * Add elements onto back of array
 */
template<class ComponentType>
void DynArray<ComponentType>::append(const DynArray &copy)
{
	// Check if more memory is needed
	if (size_ + copy.size() > capacity_)
	{
		reserve(size_ + copy.size());
	}

	// Loop through all elements in array to copy
	for (int i = 0; i < copy.size(); i++)
	{
		// add element to back of array
		type_[size_ + i] = copy.get(i);
	}
	size_ += copy.size();
}

/*
 * Set specific index to specified value
 */
template<class ComponentType>
void DynArray<ComponentType>::set(const int index, const ComponentType compType)
{
	assert(index >= 0 && index <= size_, "Out of bounds");
	if (index == size_)
	{
		size_++;
	}
	type_[index] = compType;	
}

/*
 * Removes all elements in array
 */
template <class ComponentType>
void DynArray<ComponentType>::zap()
{
	for (int i = 0; i < size_; i++)
	{
		type_[i] = ComponentType();
	}
	size_ = 0;
}

/*
 * Makes exact copy of array 
 */
template<class ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator=(const DynArray & copy)
{
	// Delete buffer
	delete[] type_;
	// Recreate buffer with new size
	type_ = new ComponentType[copy.capacity()];
	size_ = copy.size();
	capacity_ = copy.capacity();
	// Loop through all elements
	for (int i = 0; i < size_; i++)
	{
		type_[i] = copy.get(i);
	}
	
	return (*this);
}

/*
 * Append array to back of array
*/
template<class ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator+=(const DynArray &copy)
{
	append(copy);
	return (*this);
}

/*
 * override [] for setting values array[index] = value
 */
template<class ComponentType>
ComponentType& DynArray<ComponentType>::operator[](unsigned int index)
{
	assert(index > 0 && index <= size_, "Out of bounds");
	if (index == size_)
	{
		size_++;
	}
	return type_[index];
}

/*
 * Override [] for getting values value = array[index]
 */
template<class ComponentType>
const ComponentType & DynArray<ComponentType>::operator[](unsigned int index) const
{
	assert(index > 0 && index < size_, "Out of bounds");
	return type_[index];
}

/*
 * override insersion operator for cout
 */
template<class ComponentType>
std::ostream & operator<<(std::ostream &out, const DynArray<ComponentType> &copy)
{
	for (int i = 0; i < copy.size() - 1; i++)
	{
		// Add all but last element to outputstream
		out << copy.get(i) << ", ";
	}
	// Add last element to outputstream
	out << copy.get(copy.size() - 1);
	return out;
}

/*
 * Get the last element in the array
 */
template <class ComponentType>
ComponentType DynArray<ComponentType>::back() const
{
	assert(size_ > 0)
	return type_[size_ - 1];
}

/*
 * Get the first element in the array
 */
template<class ComponentType>
ComponentType DynArray<ComponentType>::front() const
{
	assert(size_ > 0)
	return type_[0];
}

/*
 * get a element at specific index
*/
template<class ComponentType>
ComponentType DynArray<ComponentType>::get(const int index) const
{
	assert(size_ > index);
	return type_[index];
}

#endif