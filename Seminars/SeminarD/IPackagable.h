#pragma once

#ifndef IPACKAGEABLE_H
#define IPACKAGEABLE_H

#include <utility> //std::pair

class IPackagable
{
public:
	virtual void setPackageDimensions(const std::pair<int, int> dimensions) = 0;
	virtual std::pair<int, int> getPackageSize() const = 0;
};

#endif // !IPACKAGEABLE_H
