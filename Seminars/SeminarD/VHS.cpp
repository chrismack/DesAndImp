#ifndef VHS_CPP
#define VHS_CPP

#include "stdafx.h"
#include "VHS.h"

#include <sstream>

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
	this->languageTrack_ = languageTrack;
}

void VHS::setPackageType(std::string packageType)
{
	this->packageType_ = packageType;
}

std::string VHS::getPackageType() const
{
	return this->packageType_;
}

void VHS::setContent(std::vector<std::string> content)
{
	this->content_ = content;
}

void VHS::addContent(std::string content)
{
	this->content_.push_back(content);
}

std::vector<std::string> VHS::getContent()
{
	return this->content_;
}

std::string VHS::toString()
{
	std::string objectString;
	std::vector<std::string> baseArray = baseToStringArray();

	std::string packageDimString = "{";
	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)))
		.append("}");

	baseArray.push_back(this->packageType_);
	baseArray.push_back(packageDimString);
	baseArray.push_back(createStringList(content_));
	return objectString;
}

void VHS::generateFromString(std::string str)
{
}

std::string VHS::createStringList(std::vector<std::string> track)
{
	std::string tmpString;
	std::stringstream ss;
	if (track.size() > 1)
	{
		ss << "{";
	}
	for (int i = 0; i < track.size(); i++)
	{
		ss << track[i];
		if (i < track.size() - 1)
		{
			ss << "|";
		}
	}
	tmpString = ss.str();
	tmpString.substr(tmpString.length() - 1);
	if (track.size() > 1)
	{
		tmpString.append("}");
	}

	return tmpString;
}

#endif // !VHS_CPP
