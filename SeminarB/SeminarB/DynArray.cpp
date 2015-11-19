#include "stdafx.h"
#include "DynArray.h"
#include <assert.h>
#include <stdarg.h>

#include <iostream>

template <typename ComponentType>
DynArray<ComponentType>::DynArray()
{
	type_ = new ComponentType[6];
	size_ = 0;
	capacity_ = 6;
}

template <typename ComponentType>
DynArray<ComponentType>::DynArray(DynArray& copy)
{
}

template <typename ComponentType>
DynArray<ComponentType>::DynArray(unsigned int value)
{
	type_ = new ComponentType[value];
	for (int i = 0; i < value; i++)
	{
		type_[i] = ComponentType();
	}
	size_ = 0;
	capacity_ = indexSize;
}

template <typename ComponentType>
DynArray<ComponentType>::DynArray(ComponentType type)
{
	type_ = new ComponentType[6];
	for (int i = 0; i < 6; i++)
	{
		type_[i] = type;
	}
	size_ = 6;
	capacity = 6;
}


template <typename ComponentType>
DynArray<ComponentType>::~DynArray()
{
	delete[] type_;
}

template <typename ComponentType>
int DynArray<ComponentType>::size() const
{
	return size_;
}

template <typename ComponentType>
int DynArray<ComponentType>::capacity() const
{
	return capacity_;
}

template <typename ComponentType>
bool DynArray<ComponentType>::empty() const
{
	return size_ == 0;
}

template<typename ComponentType>
bool DynArray<ComponentType>::equality(DynArray &dynarray)
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

template <typename ComponentType>
void DynArray<ComponentType>::push_back(ComponentType compType)
{
	// If the buffer is full
	if (size_ == capacity_)
	{
		capacity_ *= 1.5;
		reallocate(capacity_);
	}

	type_[size_] = compType;
	size_++;
}

template <typename ComponentType>
void DynArray<ComponentType>::pop_back()
{
	//Array cannot be empty
	assert(size_ > 0);
	type_[size_ - 1] = ComponentType();
	size_--;

}

template<typename ComponentType>
void DynArray<ComponentType>::shrink()
{
	if (capacity_ > size_)
	{
		capacity_ = size_;
		reallocate(capacity_);
	}
}

template<typename ComponentType>
void DynArray<ComponentType>::insert(int index, ComponentType value)
{
	assert(index < size_);
	if (size_ + 1 > capacity_)
	{
		capacity_ *= 1.5;
		reallocate(capacity_);
	}

	for (int i = size_; i > index; i--)
	{
		type_[i + 1] = type_[i];
	}
	type_[index] = value;
	size_++;
}

template<typename ComponentType>
void DynArray<ComponentType>::remove(int index)
{
	assert(index < size_);
	type_[index] = ComponentType();
	for (int i = index; i < size_ - 1; i++)
	{
		type_[i] = type_[i + 1];
	}
	size_--;
}

template<typename ComponentType>
void DynArray<ComponentType>::append(const DynArray &rhs)
{
	if (size_ + rhs.size() > capacity_)
	{
		reallocate(size_ + rhs.size());
	}

	for (int i = 0; i < rhs.size(); i++)
	{
		type_[size_ + i] = rhs.get(i);
	}
	size_ += rhs.size();
}

template<typename ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator=(const DynArray & rhs)
{
	if (type_ != rhs)
	{
		delete[] type_;
		type_ = new ComponentType[rhs.size()];
		size_ = rhs.size();
		capacity_ = rhs.capacity_();
		for (int i = 0; i < size_; i++)
		{
			type_[i] = rhs.get(i);
		}
	}
	return (*this);
}

template<typename ComponentType>
ComponentType& DynArray<ComponentType>::operator[](unsigned int i)
{
	return type_[i];
}

template<typename ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator+=(const DynArray &rhs)
{
	append(rhs);
	return (*this);
}

template<typename ComponentType>
std::ostream & operator<<(std::ostream &out, const DynArray<ComponentType> &rhs)
{
	for (int i = 0; i < rhs.size(); i++)
	{
		out << rhs.get(i) << ", ";
	}
	return out;
}

template<typename ComponentType>
void DynArray<ComponentType>::reallocate(int size)
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
		
}

template <typename ComponentType>
ComponentType DynArray<ComponentType>::back()
{
	assert(size_ > 0)
	return type_[size_ - 1];
}

template<typename ComponentType>
ComponentType DynArray<ComponentType>::front()
{
	assert(size_ > 0)
	return type_[0];
}

template<typename ComponentType>
ComponentType DynArray<ComponentType>::get(int index) const
{
	assert(size_ > index);
	return type_[index];
}

template<typename ComponentType>
void DynArray<ComponentType>::set(ComponentType compType, int index)
{
	assert(capacity_ > index);
	type_[i] = compType;
}

template <typename ComponentType>
void DynArray<ComponentType>::zap()
{
	for (int i = 0; i < size_; i++)
	{
		type_[i] = ComponentType();
	}
}


