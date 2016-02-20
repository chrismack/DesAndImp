#pragma once

#ifndef IPACKAGEABLE_H
#define IPACKAGEABLE_H

#include <utility> // std::pair

class IPackagable
{
public:

	virtual ~IPackagable();
	virtual std::pair<int, int> getPackageSize();
};

#endif // !IPACKAGEABLE_H
