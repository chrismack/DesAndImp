#pragma once

#ifndef COMBOBOX_H 
#define COMBOBOX_H

#include "Material.h"
#include "IPackagable.h"

#include "Disc.h"

class ComboBox : public Material, public IPackagable
{
private:
	
	/*
     * Size of the package X|Y|Z
 	 */
	std::tuple<int, int, int> packageDimensions_;

	/*
	* The type of package the class has
	*/
	std::string packageType_;

	/*
	 * Content - Combo boxes can contain either SingleDVD, DoubleDVD or BluRay
	 */
	std::vector<Disc*> content_;
public:
	ComboBox();
	~ComboBox();

	/*
	* Part of packageable interface
	*/

	/*
	* set and get package dimensions
	*/
	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	/*
	* set and get package type
	*/
	void setPackageType(std::string packageType);
	std::string getPackageType() const;

	/*
	 * Disc get,set,add
	 * put new material into the combobox
	 */
	void setContent(std::vector<Disc*> content);
	void addContent(Disc* disc);
	std::vector<Disc*> getContent();

	/*
	* Override toArray and populate from Material class
	*/
	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> elements) override;
};

#endif // COMBOBOX_H
