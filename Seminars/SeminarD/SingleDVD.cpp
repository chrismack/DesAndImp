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

void SingleDVD::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> SingleDVD::getPackageSize() const
{
	return this->packageDimensions_;
}

void SingleDVD::toString()
{
}

void SingleDVD::generateFromString(std::string str)
{
}

#endif // !SINGLEDVD_CPP
