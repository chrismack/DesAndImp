#ifndef SINGLEDVD_CPP
#define SINGLEDVD_CPP

#include "stdafx.h"
#include "SingleDVD.h"

SingleDVD::SingleDVD()
{
}


SingleDVD::~SingleDVD()
{
}

void SingleDVD::setPackageDimensions(std::pair<int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::pair<int, int> SingleDVD::getPackageSize() const
{
	return this->packageDimensions_;
}

#endif // !SINGLEDVD_CPP
