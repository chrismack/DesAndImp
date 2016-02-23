#ifndef DOUBLEDVD_CPP
#define DOUBLEDVD_CPP

#include "stdafx.h"
#include "DoubleDVD.h"

DoubleDVD::DoubleDVD()
{
}


DoubleDVD::~DoubleDVD()
{
}

void DoubleDVD::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> DoubleDVD::getPackageSize() const
{
	return this->packageDimensions_;
}

#endif // !DOUBLEDVD_CPP
