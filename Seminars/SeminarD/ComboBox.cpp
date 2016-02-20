#ifndef COMBOBOX_CPP
#define COMBOBOX_CPP

#include "stdafx.h"
#include "ComboBox.h"

ComboBox::ComboBox()
{
}


ComboBox::~ComboBox()
{
}

void ComboBox::setPackageDimensions(std::pair<int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::pair<int, int> ComboBox::getPackageSize() const
{
	return this->packageDimensions_;
}

#endif // !COMBOBOX_CPP
