#include "stdafx.h"
#include "DynArray.h"
#include <assert.h>

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
DynArray<ComponentType>::DynArray(int indexSize)
{
	type_ = new ComponentType[indexSize];
	size_ = 0;
	capacity_ = indexSize;
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

template <typename ComponentType>
void DynArray<ComponentType>::push_back(ComponentType compType)
{
	// If the buffer is full
	if (size_ == capacity_)
	{
		capacity_ *= 1.5;

		// Create a temp buffer to save content while new address is set
		ComponentType *tempBuffer = new ComponentType[capacity_];
		for (int i = 0; i < size_; i++)
		{
			tempBuffer[i] = type_[i];
		}

		// Return old memory location to heap
		delete[] type_;
		type_ = tempBuffer;
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

template <typename ComponentType>
ComponentType DynArray<ComponentType>::back()
{
	assert(size_ > 0)
	return type_[size_ - 1];
}

template<class ComponentType>
ComponentType DynArray<ComponentType>::front()
{
	assert(size_ > 0)
	return type_[0];
}

template<class ComponentType>
ComponentType DynArray<ComponentType>::get(int index) const
{
	assert(size_ > index);
	return type_[index];
}

template<class ComponentType>
void DynArray<ComponentType>::set(ComponentType compType, int i)
{
	assert(size_ > i);
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

