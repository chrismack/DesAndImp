#ifndef BLUERAY_CPP
#define BLURAY_CPP

#include "stdafx.h"
#include "BlueRay.h"

BlueRay::BlueRay()
{
}


BlueRay::~BlueRay()
{
}

void BlueRay::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> BlueRay::getPackageSize() const
{
	return this->packageDimensions_;
}

void BlueRay::toString()
{
}

void BlueRay::generateFromString(std::string str)
{
}

#endif // !BLUERAY_CPP
