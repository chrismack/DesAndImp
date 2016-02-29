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

void DoubleDVD::setPackageType(std::string packageType)
{
	this->packageType_ = packageType;
}

std::string DoubleDVD::getPackageType() const
{
	return this->packageType_;
}

std::map<int, std::vector<std::string>> DoubleDVD::getAllContent()
{
	return this->contentMap_;
}

void DoubleDVD::setContent(const std::map<int, std::vector<std::string>> content)
{
	this->contentMap_ = content;
}

std::vector<std::string> DoubleDVD::getContentOnSide(const int side)
{
	return this->contentMap_[side];
}

void DoubleDVD::setContentOnSide(const int side, const std::vector<std::string> content)
{
	assert(side > 0 && side < 2);
	this->contentMap_[side] = content;
}

std::string DoubleDVD::toString()
{
	std::string objectString;
	std::vector<std::string> bluRayElements = toStringArray();
	bluRayElements.push_back(this->packageType_);

	std::string packageDimString = "{";
	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)))
		.append("}");

	bluRayElements.push_back(packageDimString);
	bluRayElements.push_back(createStringList(contentMap_));
	bluRayElements.push_back(createStringList(bounsFeatures_));

	std::stringstream ss;
	for (int i = 0; i < bluRayElements.size(); i++)
	{
		ss << bluRayElements[i];
		ss << ",";
	}
	objectString = ss.str();
	objectString = objectString.substr(0, objectString.length() - 1);
	return objectString;
}

void DoubleDVD::generateFromString(std::string str)
{
}

#endif // !DOUBLEDVD_CPP
