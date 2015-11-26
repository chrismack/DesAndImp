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
 *Copy constructor
 */
template <class ComponentType>
DynArray<ComponentType>::DynArray(DynArray& copy)
{
	type_ = new ComponentType[copy.size()];
	size_ = copy.size();
	for (unsigned int i = 0; i < size_; ++i)
	{
		type_[i] = copy.get(i);
	}
}

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

template<class ComponentType>
DynArray<ComponentType>::DynArray(unsigned int indexSize, bool clean)
{
		type_ = new ComponentType[indexSize];
		size_ = 0;
		capacity_ = indexSize;
}

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


template <class ComponentType>
DynArray<ComponentType>::~DynArray()
{
	delete[] type_;
}

template <class ComponentType>
int DynArray<ComponentType>::size() const
{
	return size_;
}

template <class ComponentType>
int DynArray<ComponentType>::capacity() const
{
	return capacity_;
}

template <class ComponentType>
bool DynArray<ComponentType>::empty() const
{
	return size_ == 0;
}

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

template <class ComponentType>
void DynArray<ComponentType>::pop_back()
{
	//Array cannot be empty
	assert(size_ > 0);
	type_[size_ - 1] = ComponentType();
	size_--;

}

template<class ComponentType>
void DynArray<ComponentType>::push_front(ComponentType compType)
{
	insert(0, compType);
}

template<class ComponentType>
void DynArray<ComponentType>::pop_front()
{
	remove(0);
}

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

template<class ComponentType>
void DynArray<ComponentType>::shrink()
{
	assert(capacity_ > size_)
	reserve(capacity_);
	
}

template<class ComponentType>
void DynArray<ComponentType>::insert(const int index, const ComponentType value)
{
	assert(index < size_);
	if (size_ + 1 > capacity_)
	{
		reserve(capacity_ *= 1.5);
	}

	for (int i = size_ - 1; i >= index; i--)
	{
		type_[i + 1] = type_[i];
	}
	type_[index] = value;
	size_++;
}

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

template<class ComponentType>
void DynArray<ComponentType>::append(const DynArray &copy)
{
	if (size_ + copy.size() > capacity_)
	{
		reserve(size_ + copy.size());
	}

	for (int i = 0; i < copy.size(); i++)
	{
		type_[size_ + i] = copy.get(i);
	}
	size_ += copy.size();
}

template<class ComponentType>
void DynArray<ComponentType>::set(const int index, const ComponentType compType)
{
	assert(index > 0 && index <= size_, "Out of bounds");
	if (index == size_)
	{
		size_++;
	}
	type_[index] = compType;	
}

template <class ComponentType>
void DynArray<ComponentType>::zap()
{
	for (int i = 0; i < size_; i++)
	{
		type_[i] = ComponentType();
	}
	size_ = 0;
}

template<class ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator=(const DynArray & copy)
{
	if (type_ != copy)
	{
		delete[] type_;
		type_ = new ComponentType[copy.size()];
		size_ = copy.size();
		capacity_ = copy.capacity_();
		for (int i = 0; i < size_; i++)
		{
			type_[i] = copy.get(i);
		}
	}
	return (*this);
}

template<class ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator+=(const DynArray &copy)
{
	append(copy);
	return (*this);
}

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

template<class ComponentType>
const ComponentType & DynArray<ComponentType>::operator[](unsigned int index) const
{
	assert(index > 0 && index < size_, "Out of bounds");
	return type_[index];
}


template<class ComponentType>
std::ostream & operator<<(std::ostream &out, const DynArray<ComponentType> &copy)
{
	for (int i = 0; i < copy.size() - 1; i++)
	{
		out << copy.get(i) << ", ";
	}
	out << copy.get(copy.size() - 1);
	return out;
}

template <class ComponentType>
ComponentType DynArray<ComponentType>::back() const
{
	assert(size_ > 0)
	return type_[size_ - 1];
}

template<class ComponentType>
ComponentType DynArray<ComponentType>::front() const
{
	assert(size_ > 0)
	return type_[0];
}

template<class ComponentType>
ComponentType DynArray<ComponentType>::get(const int index) const
{
	assert(size_ > index);
	return type_[index];
}

#endif