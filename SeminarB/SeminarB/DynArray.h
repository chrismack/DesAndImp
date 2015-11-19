#pragma once
#ifndef DYNARRAY
#define DYNARRAY

#include <iostream>

template<typename ComponentType>
class DynArray
{
private:
	ComponentType *type_;
	int size_;
	int capacity_;

	void reallocate(int size);
public:
	/* Constructors */
	DynArray();
	DynArray(DynArray&);
	DynArray(unsigned int indexSize);
	DynArray(ComponentType);

	~DynArray();

	int size() const;
	int capacity() const;
	bool empty() const;
	bool equality(DynArray&);

	void push_back(ComponentType);
	void pop_back();
	void shrink();
	void insert(int, ComponentType);
	void remove(int);
	void append(const DynArray&);

	/* Operator Overrides*/
	DynArray & operator=(const DynArray &rhs);
	ComponentType & operator[](unsigned int);
	DynArray & operator+=(const DynArray &rhs);

	template <typename U>
	friend std::ostream & operator<<(std::ostream& out, const DynArray<U>& rhs);

	ComponentType back();
	ComponentType front();
	ComponentType get(int) const;

	void set(ComponentType, int);
	void zap();
};

#endif /*end DYNARRAY*/


