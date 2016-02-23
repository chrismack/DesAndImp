#pragma once

#ifndef SINGLEDVD_H
#define SINGLEDVD_G

#include "Disc.h"
#include "IPackagable.h"

class SingleDVD : public Disc, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;
public:
	SingleDVD();
	~SingleDVD();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;
};

#endif // !SINGLEDVD_H
