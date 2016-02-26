#ifndef COMBOBOX_CPP
#define COMBOBOX_CPP

#include "stdafx.h"
#include "ComboBox.h"
#include "Material.h"

ComboBox::ComboBox()
{
}


ComboBox::~ComboBox()
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

void ComboBox::toString()
{
}

void ComboBox::generateFromString(std::string str)
{
}

#endif // !COMBOBOX_CPP
