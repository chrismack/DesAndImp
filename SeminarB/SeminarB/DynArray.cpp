#include "stdafx.h"
#include "DynArray.h"

template <class ComponentType>
DynArray<ComponentType>::DynArray()
{
	type = new ComponentType[10];
	std::cout << sizeof(ComponentType) << std::endl;
}

template <class ComponentType>
DynArray<ComponentType>::DynArray(DynArray& copy)
{
}

template <class ComponentType>
DynArray<ComponentType>::DynArray(int index)
{
}

template <class ComponentType>
DynArray<ComponentType>::~DynArray()
{
	delete[] type;
}

template <class ComponentType>
int DynArray<ComponentType>::size() const
{
	return 0;
}

template <class ComponentType>
int DynArray<ComponentType>::capacity() const
{
	return 0;
}

template <class ComponentType>
bool DynArray<ComponentType>::empty() const
{
	return false;
}

template <class ComponentType>
void DynArray<ComponentType>::push_back(ComponentType& compType)
{
}

template <class ComponentType>
void DynArray<ComponentType>::pop_back()
{
}

template <class ComponentType>
ComponentType& DynArray<ComponentType>::back()
{
	return type;
}

template<class ComponentType>
ComponentType& DynArray<ComponentType>::front()
{
	return type;
}

template<class ComponentType>
ComponentType& DynArray<ComponentType>::get(int index) const
{
	return type;
}

template<class ComponentType>
void DynArray<ComponentType>::set(ComponentType& compType, int i)
{
}

template <class ComponentType>
void DynArray<ComponentType>::zap()
{
}

