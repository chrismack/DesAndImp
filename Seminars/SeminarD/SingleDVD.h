#pragma once

#ifndef SINGLEDVD_H
#define SINGLEDVD_G

#include "Disc.h"
#include "IPackagable.h"
#include "Serializable.h"

class SingleDVD : public Disc, public IPackagable, public Serializable
{
private:
	std::tuple<int, int, int> packageDimensions_;
public:
	SingleDVD();
	~SingleDVD();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	void toString();
	void generateFromString(std::string str);
};

#endif // !SINGLEDVD_H
