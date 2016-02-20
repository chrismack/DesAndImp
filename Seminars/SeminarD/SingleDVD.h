#pragma once

#ifndef SINGLEDVD_H
#define SINGLEDVD_G

#include "Disc.h"
#include "IPackagable.h"

class SingleDVD : public Disc, public IPackagable
{
private:
	std::pair<int, int> packageDimensions_;
public:
	SingleDVD();
	~SingleDVD();

	void setPackageDimensions(std::pair<int, int> dimensions);
	std::pair<int, int> getPackageSize() const;
};

#endif // !SINGLEDVD_H
