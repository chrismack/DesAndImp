#ifndef COMBOBOX_CPP
#define COMBOBOX_CPP

#include "stdafx.h"

#include "ComboBox.h"
#include "Material.h"
#include "BlueRay.h"
#include "SingleDVD.h"
#include "DoubleDVD.h"

#include <sstream>
#include <algorithm>

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

//std::string ComboBox::toString()
//{
//	std::string objectString;
//	std::vector<std::string> baseElements = baseToStringArray();
//	baseElements.push_back(this->packageType_);
//
//	std::string packageDimString = "{";
//	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
//		.append("|")
//		.append(std::to_string(std::get<1>(this->packageDimensions_)))
//		.append("|")
//		.append(std::to_string(std::get<2>(this->packageDimensions_)))
//		.append("}");
//
//	baseElements.push_back(packageDimString);
//
//	std::string dvdListString = "[]";
//	std::stringstream tmpStringStream;
//	if (content_.size() > 0)
//	{
//		tmpStringStream << "[";
//		for (int i = 0; i < content_.size(); i++)
//		{
//			//tmpStringStream << content_[i]->toString();
//			if (i < content_.size() - 1)
//			{
//				tmpStringStream << "|";
//			}
//		}
//		tmpStringStream << "]";
//	}
//	dvdListString = tmpStringStream.str();
//	baseElements.push_back(dvdListString);
//
//	std::stringstream ss;
//	for (int i = 0; i < baseElements.size(); i++)
//	{
//		ss << baseElements[i];
//		ss << ",";
//	}
//	objectString = ss.str();
//	objectString = objectString.substr(0, objectString.length() - 1);
//
//	return objectString;
//}

std::vector<std::string> ComboBox::toArray()
{
	std::vector<std::string> baseElements = Material::toArray();
	baseElements.push_back(this->packageType_ != "" ? this->packageType_ : " ");

	std::string packageDimString = std::to_string(std::get<0>(this->packageDimensions_))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)));

	baseElements.push_back(packageDimString);

	std::string dvdListString = "[]";
	std::stringstream tmpStringStream;
	if (content_.size() > 0)
	{
		tmpStringStream << "[";
		for (int i = 0; i < content_.size(); i++)
		{
			int arraySize = content_[i]->toArray().size();
			std::vector<std::string> localContent = content_[i]->toArray();
			
			for (int j = 0; j < localContent.size(); j++)
			{
				tmpStringStream << localContent[j];
				if (j < arraySize - 1)
				{
					tmpStringStream << ",";
				}
			}
			if (i < content_.size() - 1)
			{
				tmpStringStream << "_";
			}
		}
		tmpStringStream << "]";
	}
	dvdListString = tmpStringStream.str();
	baseElements.push_back(dvdListString);

	return baseElements;
}

void ComboBox::populate(std::vector<std::string> elements)
{
	if (elements[11][0] = '[')
	{
		elements[11] = elements[11].substr(1, elements[11].find(']') - 1);
		std::vector<std::string> dvdStrings = split(elements[11], "_");

		Disc* disc = nullptr;

		for (int i = 0; i < dvdStrings.size(); i++)
		{
			std::string type;
			type = split(dvdStrings[i], ",")[2];
			type.erase(std::remove_if(type.begin(), type.end(), isspace), type.end());
			//type.erase(std::remove_if(type.begin(), type.end(), ' '));
			if (type == "BluRay")
			{
				Material* mat = new BlueRay;
				disc = static_cast<BlueRay*>(mat);
			}
			else if (type == "SingleDVD")
			{
				Material* mat = new SingleDVD;
				disc = static_cast<SingleDVD*>(mat);
			}
			else if (type == "DoubleDVD")
			{
				Material* mat = new DoubleDVD;
				disc = static_cast<DoubleDVD*>(mat);
			}
			else
			{
				return;
			}

			if (disc != nullptr)
			{
				disc->populate(split(dvdStrings[i], ","));
				content_.push_back(disc);
			}
		}
	}
	elements.pop_back();

	std::vector<std::string> packageVector;
	packageVector = split(elements[10], "|");
	packageDimensions_ = std::tuple<int, int, int>(std::stoi(packageVector[0]), std::stoi(packageVector[1]), std::stoi(packageVector[2]));
	elements.pop_back();

	packageType_ = elements[9];
	elements.pop_back();
	

	Material::populate(elements);
}

#endif // !COMBOBOX_CPP
