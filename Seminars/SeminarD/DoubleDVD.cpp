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

//std::string DoubleDVD::toString()
//{
//	std::string objectString;
//	std::vector<std::string> bluRayElements = toStringArray();
//	bluRayElements.push_back(this->packageType_);
//
//	std::string packageDimString = "{";
//	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
//		.append("|")
//		.append(std::to_string(std::get<1>(this->packageDimensions_)))
//		.append("|")
//		.append(std::to_string(std::get<2>(this->packageDimensions_)))
//		.append("}");
//
//	bluRayElements.push_back(packageDimString);
//	bluRayElements.push_back(createStringList(contentMap_));
//	bluRayElements.push_back(createStringList(bounsFeatures_));
//
//	std::stringstream ss;
//	for (int i = 0; i < bluRayElements.size(); i++)
//	{
//		ss << bluRayElements[i];
//		ss << ",";
//	}
//	objectString = ss.str();
//	objectString = objectString.substr(0, objectString.length() - 1);
//	return objectString;
//}

std::vector<std::string> DoubleDVD::toArray()
{
	std::vector<std::string> baseElements = Disc::toArray();
	baseElements.push_back(this->packageType_ != "" ? this->packageType_ : " ");

	std::string packageDimString = std::to_string(std::get<0>(this->packageDimensions_))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)));

	baseElements.push_back(packageDimString);
	baseElements.push_back(createStringList(contentMap_));
	baseElements.push_back(createStringList(bounsFeatures_));
	return baseElements;
}

void DoubleDVD::populate(std::vector<std::string> elements)
{
	bounsFeatures_ = stringToMap(elements[15]);
	elements.pop_back();
	contentMap_ = stringToMap(elements[14]);
	elements.pop_back();

	std::vector<std::string> packageVector;
	packageVector = split(elements[13], "|");
	packageDimensions_ = std::tuple<int, int, int>(std::stoi(packageVector[0]), std::stoi(packageVector[1]), std::stoi(packageVector[2]));
	elements.pop_back();

	packageType_ = elements[12];
	elements.pop_back();

	Disc::populate(elements);
}

#endif // !DOUBLEDVD_CPP
