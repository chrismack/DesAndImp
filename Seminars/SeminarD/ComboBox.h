#pragma once

#ifndef COMBOBOX_H 
#define COMBOBOX_H

#include "IPackagable.h"

class ComboBox : public Material, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;
public:
	ComboBox();
	~ComboBox();

	void setPackageDimensions(std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;
};

#endif // COMBOBOX_H
