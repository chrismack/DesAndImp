#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H


#pragma once
#include <string>

class Serializable
{
public:
	virtual void toString();
	virtual void generateFromString(std::string str);
};

#endif // !SERIALIZABLE_H