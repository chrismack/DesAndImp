#pragma once

#ifndef COMBOBOX_H 
#define COMBOBOX_H

#include "Material.h"
#include "IPackagable.h"
#include "Serializable.h"

class ComboBox : public Material, public IPackagable, public Serializable
{
private:
	std::tuple<int, int, int> packageDimensions_;
public:
	ComboBox();
	~ComboBox();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	void toString();
	void generateFromString(std::string str);
};

#endif // COMBOBOX_H
