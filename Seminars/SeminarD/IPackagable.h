#pragma once

#ifndef IPACKAGEABLE_H
#define IPACKAGEABLE_H

#include <utility> //std::pair
#include <tuple>
#include <string>

class IPackagable
{
public:
	//virtual void setPackageDimensions(const std::pair<int, int> dimensions) = 0;
	//virtual std::pair<int, int> getPackageSize() const = 0;
	
	virtual void setPackageDimensions(const std::tuple<int, int, int> dimensions) = 0;
	virtual std::tuple<int, int, int> getPackageSize() const = 0;

	virtual void setPackageType(std::string packageType) = 0;
	virtual std::string getPackageType() const = 0;
};

#endif // !IPACKAGEABLE_H
