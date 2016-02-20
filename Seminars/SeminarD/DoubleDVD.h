#pragma once

#ifndef DOUBLEDVD_H
#define DOUBLEDVD_H

#include "SingleDVD.h"
#include "IPackagable.h"

class DoubleDVD : public SingleDVD, public IPackagable
{
private:
	std::pair<int, int> packageDimensions_;
public:
	DoubleDVD();
	~DoubleDVD();

	void setPackageDimensions(std::pair<int, int> dimensions);
	std::pair<int, int> getPackageSize() const;
};

#endif // !DOUBLEDVD_H
