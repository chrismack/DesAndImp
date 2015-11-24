#pragma once 

#ifndef DYNARRAY_CPP
#define DYNARRAY_CPP

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
	type_ = new ComponentType[copy.size()];
	size_ = copy.size();
	for (unsigned int i = 0; i < size_; ++i)
	{
		type_[i] = copy.get(i);
	}
}

template <class ComponentType>
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

template<class ComponentType>
DynArray<ComponentType>::DynArray(unsigned int indexSize, bool clean)
{
	if (clean)
	{
		type_ = new ComponentType[value];
		size_ = 0;
		capacity_ = indexSize;
	}
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
	capacity = 6;
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

template <class ComponentType>
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

template <class ComponentType>
void DynArray<ComponentType>::pop_back()
{
	//Array cannot be empty
	assert(size_ > 0);
	type_[size_ - 1] = ComponentType();
	size_--;

}

template<class ComponentType>
void DynArray<ComponentType>::push_front(ComponentType)
{
	insert(0, ComponentType);
}

template<class ComponentType>
void DynArray<ComponentType>::pop_front()
{
	remove(0);
}

template<class ComponentType>
void DynArray<ComponentType>::shrink()
{
	if (capacity_ > size_)
	{
		capacity_ = size_;
		reallocate(capacity_);
	}
}

template<class ComponentType>
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

template<class ComponentType>
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

template<class ComponentType>
void DynArray<ComponentType>::append(const DynArray &copy)
{
	if (size_ + copy.size() > capacity_)
	{
		reallocate(size_ + copy.size());
	}

	for (int i = 0; i < copy.size(); i++)
	{
		type_[size_ + i] = copy.get(i);
	}
	size_ += copy.size();
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
ComponentType& DynArray<ComponentType>::operator[](unsigned int i)
{
	return type_[i];
}

template<class ComponentType>
DynArray<ComponentType> & DynArray<ComponentType>::operator+=(const DynArray &copy)
{
	append(copy);
	return (*this);
}

template<class ComponentType>
std::ostream & operator<<(std::ostream &out, const DynArray<ComponentType> &copy)
{
	for (int i = 0; i < copy.size() - 1; i++)
	{
		out << copy.get(i) << ", ";
	}
	out << copy.get(i);
	return out;
}

template<class ComponentType>
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

template <class ComponentType>
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
void DynArray<ComponentType>::set(ComponentType compType, int index)
{
	assert(capacity_ > index);
	type_[i] = compType;
}

template <class ComponentType>
void DynArray<ComponentType>::zap()
{
	for (int i = 0; i < size_; i++)
	{
		type_[i] = ComponentType();
	}
}

#endif