#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H


#pragma once
#include <string>

class Serializable
{
public:
	virtual void toString() = 0;
	virtual void generateFromString(std::string str) = 0;
};

#endif // !SERIALIZABLE_H