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

void VHS::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> VHS::getPackageSize() const
{
	return this->packageDimensions_;
}

std::string VHS::getLanguageTrack() const
{
	return std::string();
}

void VHS::setlanguageTrack(const std::string languageTrack)
{
}

#endif // !VHS_CPP
