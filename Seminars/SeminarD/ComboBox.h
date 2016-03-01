#pragma once

#ifndef COMBOBOX_H 
#define COMBOBOX_H

#include "Material.h"
#include "IPackagable.h"

#include "Disc.h"

class ComboBox : public Material, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;
	std::string packageType_;

	std::vector<Disc*> content_;
public:
	ComboBox();
	~ComboBox();

	void setDiscContent();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	void setPackageType(std::string packageType);
	std::string getPackageType() const;

	void setContent(std::vector<Disc*> content);
	void addContent(Disc* disc);
	std::vector<Disc*> getContent();

	std::string toString();
	void generateFromString(std::string str);
};

#endif // COMBOBOX_H
