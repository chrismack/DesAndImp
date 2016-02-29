#ifndef COMBOBOX_CPP
#define COMBOBOX_CPP

#include "stdafx.h"
#include "ComboBox.h"
#include "Material.h"

#include <sstream>

ComboBox::ComboBox()
{
}


ComboBox::~ComboBox()
{
}

void ComboBox::setDiscContent()
{
}

void ComboBox::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> ComboBox::getPackageSize() const
{
	return this->packageDimensions_;
}

void ComboBox::setPackageType(std::string packageType)
{
	this->packageType_ = packageType;
}

std::string ComboBox::getPackageType() const
{
	return this->packageType_;
}

void ComboBox::setContent(std::vector<Disc*> content)
{
	this->content_ = content;
}

void ComboBox::addContent(Disc* disc)
{
	this->content_.push_back(disc);
}

std::vector<Disc*> ComboBox::getContent()
{
	return this->content_;
}

std::string ComboBox::toString()
{
	std::string objectString;
	std::vector<std::string> baseElements = baseToStringArray();
	baseElements.push_back(this->packageType_);

	std::string packageDimString = "{";
	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)))
		.append("}");

	baseElements.push_back(packageDimString);

	std::string dvdListString = "[]";
	std::stringstream tmpStringStream;
	if (content_.size() > 0)
	{
		tmpStringStream << "[";
		for (int i = 0; i < content_.size(); i++)
		{
			tmpStringStream << content_[i]->toString();
			if (i < content_.size() - 1)
			{
				tmpStringStream << "|";
			}
		}
		tmpStringStream << "]";
	}
	dvdListString = tmpStringStream.str();
	baseElements.push_back(dvdListString);

	std::stringstream ss;
	for (int i = 0; i < baseElements.size(); i++)
	{
		ss << baseElements[i];
		ss << ",";
	}
	objectString = ss.str();
	objectString = objectString.substr(0, objectString.length() - 1);

	return objectString;
}

void ComboBox::generateFromString(std::string str)
{
}

#endif // !COMBOBOX_CPP
