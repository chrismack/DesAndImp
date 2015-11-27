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

	~DynArray();

	int size() const;
	int capacity() const;

	bool empty() const;
	bool equality(DynArray&) const;

	void push_back(const ComponentType);
	void pop_back();
	void push_front(const ComponentType);
	void pop_front();
	void reserve(const int);
	void shrink();
	void insert(const int, const ComponentType);
	void remove(const int);
	void append(const DynArray&);
	void set(const int, const ComponentType);
	void zap();

	/* Operator Overrides*/
	DynArray & operator=(const DynArray &rhs);
	DynArray & operator+=(const DynArray &rhs);
	
	//ComponentType & operator[](const unsigned int);

	ComponentType& operator[](unsigned int index);
	const ComponentType& operator[](unsigned int index) const;

	template <typename U>
	friend std::ostream & operator<<(std::ostream& out, const DynArray<U>& rhs);

	ComponentType back() const;
	ComponentType front() const;
	ComponentType get(const int) const;
};


#include "DynArray.cpp"
#endif /*end DYNARRAY*/


