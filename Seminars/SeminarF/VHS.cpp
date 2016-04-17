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
	return this->languageTrack_;
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

void VHS::setAudioTrack(std::string content)
{
	this->audioTrack_ = content;
}


std::string VHS::getAudioTrack()
{
	return this->audioTrack_;
}

//std::string VHS::toString()
//{
//	std::string objectString;
//	std::vector<std::string> baseArray = baseToStringArray();
//
//	std::string packageDimString = "{";
//	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
//		.append("|")
//		.append(std::to_string(std::get<1>(this->packageDimensions_)))
//		.append("|")
//		.append(std::to_string(std::get<2>(this->packageDimensions_)))
//		.append("}");
//
//	baseArray.push_back(this->packageType_);
//	baseArray.push_back(packageDimString);
//	baseArray.push_back(createStringList(content_));
//	return objectString;
//}

std::vector<std::string> VHS::toArray()
{
	std::vector<std::string> baseArray = Material::toArray();

	baseArray.push_back(this->packageType_ != "" ? this->packageType_ : " ");
	std::string packageDimString = std::to_string(std::get<0>(this->packageDimensions_))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)));

	baseArray.push_back(packageDimString);
	baseArray.push_back(createStringList(content_));

	return baseArray;
}

void VHS::populate(std::vector<std::string> elements)
{
	content_ = split(elements[11], "|");
	elements.pop_back();

	std::vector<std::string> packageVector;
	packageVector = split(elements[10], "|");
	packageDimensions_ = std::tuple<int, int, int>(std::stoi(packageVector[0]), std::stoi(packageVector[1]), std::stoi(packageVector[2]));
	elements.pop_back();

	packageType_ = elements[9];
	elements.pop_back();

	Material::populate(elements);


}

std::string VHS::createStringList(std::vector<std::string> track)
{
	std::string tmpString;
	std::stringstream ss;
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

	return tmpString;
}

#endif // !VHS_CPP
