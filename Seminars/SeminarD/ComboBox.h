#pragma once

#ifndef COMBOBOX_H 
#define COMBOBOX_H

#include "IPackagable.h"

class ComboBox : public IPackagable
{
private:
	std::pair<int, int> packageDimensions_;
public:
	ComboBox();
	~ComboBox();

	void setPackageDimensions(std::pair<int, int> dimensions);
	std::pair<int, int> getPackageSize() const;
};

#endif // COMBOBOX_H
