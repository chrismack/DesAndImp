#ifndef VHS_CPP
#define VHS_CPP

#include "stdafx.h"
#include "VHS.h"

VHS::VHS()
{
}

VHS::~VHS()
{
}

void VHS::setPackageDimensions(std::pair<int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::pair<int, int> VHS::getPackageSize() const
{
	return this->packageDimensions_;
}

#endif // !VHS_CPP
