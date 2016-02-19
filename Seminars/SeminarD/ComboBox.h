#pragma once

#ifndef COMBOBOX_H 
#define COMBOBOX_H

#include "IPackagable.h"

class ComboBox : public IPackagable
{
public:
	ComboBox();
	~ComboBox();

	virtual std::pair<int, int> getPackageSize();
};

#endif // COMBOBOX_H
