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

std::map<int, SDI::DynArray<std::string>> DoubleDVD::getAllContent() const
{
	return std::map<int, SDI::DynArray<std::string>>();
}

void DoubleDVD::setContent(const std::map<int, SDI::DynArray<std::string>> content)
{
}

SDI::DynArray<std::string> DoubleDVD::getContentOnSide(const int side) const
{
	return SDI::DynArray<std::string>();
}

void DoubleDVD::setContentOnSide(const int, const SDI::DynArray<std::string> content)
{
}

#endif // !DOUBLEDVD_CPP
