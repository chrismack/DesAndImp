#pragma once
#ifndef DYNARRAY
#define DYNARRAY

template<class ComponentType>
class DynArray
{
private:
	ComponentType *type_;
	int size_;
	int capacity_;
public:
	DynArray();
	DynArray(DynArray&);
	DynArray(int);
	~DynArray();

	int size() const;
	int capacity() const;
	bool empty() const;

	void push_back(ComponentType&);
	void pop_back();

	ComponentType& back();
	ComponentType& front();
	ComponentType& get(int) const;

	void set(ComponentType&, int);
	void zap();
};

#endif /*end DYNARRAY*/