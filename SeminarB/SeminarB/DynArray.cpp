#include "stdafx.h"
#include "DynArray.h"

template <class ComponentType>
DynArray<ComponentType>::DynArray()
{
	type_ = new ComponentType[6];
	size_ = 0;
	capacity_ = 6;
}

template <class ComponentType>
DynArray<ComponentType>::DynArray(DynArray& copy)
{
}

template <class ComponentType>
DynArray<ComponentType>::DynArray(int indexSize)
{
	type_ = new ComponentType[indexSize];
	size_ = 0;
	capacity_ = indexSize;
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

template <class ComponentType>
void DynArray<ComponentType>::push_back(ComponentType compType)
{
	// If the buffer is full
	if (size_ == (capacity_ - 1))
	{
		capacity_ *= 1.5;
		ComponentType *tempBuffer = new ComponentType[capacity_];
		for (int i = 0; i <= size_; i++)
		{
			tempBuffer[i] = type_[i];
		}
		//delete[] type_;
		type_ = tempBuffer;
		//delete[] tempBuffer;
	}
	// Add to element to array
	type_[size_] = compType;
	size_++;
}

template <class ComponentType>
void DynArray<ComponentType>::pop_back()
{
	
}

template <class ComponentType>
ComponentType& DynArray<ComponentType>::back()
{
	return type_;
}

template<class ComponentType>
ComponentType& DynArray<ComponentType>::front()
{
	return type_;
}

template<class ComponentType>
ComponentType& DynArray<ComponentType>::get(int index) const
{
	return type_;
}

template<class ComponentType>
void DynArray<ComponentType>::set(ComponentType& compType, int i)
{
}

template <class ComponentType>
void DynArray<ComponentType>::zap()
{
	/*for (int i = 0; i < size_; i++)
	{
		type_[i] = nullptr;
	}*/
}

