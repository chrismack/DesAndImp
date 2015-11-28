#pragma once
#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stdarg.h>
#include <assert.h>
#include <iostream>

template<class ComponentType>
class DynArray
{
private:
	ComponentType *type_;
	int size_;
	int capacity_;
public:
	/* Constructors */
	DynArray();
	DynArray(DynArray&);
	DynArray(unsigned int indexSize);
	DynArray(unsigned int indexSize, bool clean);
	DynArray(const ComponentType);
	/* Deconstructor */
	~DynArray();

	// Get the number of elements in the array
	int size() const;
	// Get the number of elements the array can hold
	int capacity() const;

	// Return of the array has any
	bool empty() const;
	// Check if two arrays are same size and order
	bool equality(DynArray&) const;

	// Puts element on the back of the array
	void push_back(const ComponentType);
	// Removes the last element on the array
	void pop_back();
	// Puts element at start of array moves all other element back
	void push_front(const ComponentType);
	// Removes first element moves all other elements foward
	void pop_front();
	// Set the number of elements that can be stored in the array
	void reserve(const int);
	// Set the size of the array to the number of elements in the array
	void shrink();
	// put element in any position in the array moves elements after index back
	void insert(const int, const ComponentType);
	// remove element in any position moves elements after index foward
	void remove(const int);
	// Add elements in second array to end of array
	void append(const DynArray&);
	//set any element in array
	void set(const int, const ComponentType);
	// Remove all elements in array
	void zap();

	/* Operator Overrides*/
	DynArray & operator=(const DynArray &rhs);
	DynArray & operator+=(const DynArray &rhs);
	ComponentType& operator[](unsigned int index);
	const ComponentType& operator[](unsigned int index) const;

	template <typename U>
	friend std::ostream & operator<<(std::ostream& out, const DynArray<U>& rhs);

	// Get the last element in the array
	ComponentType back() const;
	// Get the first element in the array
	ComponentType front() const;
	// Get element at specific index
	ComponentType get(const int) const;
};


#include "DynArray.cpp"
#endif /*end DYNARRAY*/


