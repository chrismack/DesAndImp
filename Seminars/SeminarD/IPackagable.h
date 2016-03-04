#pragma once

#ifndef IPACKAGEABLE_H
#define IPACKAGEABLE_H

#include <utility> //std::pair
#include <tuple>
#include <string>

class IPackagable
{
public:
	
	/*
	 * Interface class used as not all materials will have a package
	 */

	/*
	 * Set the size of a material
	 */
	virtual void setPackageDimensions(const std::tuple<int, int, int> dimensions) = 0;
	
	/*
	 * Get the X|Y|Z dimensions of the package
	 */
	virtual std::tuple<int, int, int> getPackageSize() const = 0;

	/*
	 * set the type of package the material has
	 */
	virtual void setPackageType(std::string packageType) = 0;

	/*
	 * get the type of package a material has
	 */
	virtual std::string getPackageType() const = 0;
};

#endif // !IPACKAGEABLE_H
