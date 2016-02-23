#pragma once

#ifndef BLURAY_H
#define BLURAY_H

#include "Disc.h"
#include "IPackagable.h"
class BlueRay : public Disc, public IPackagable 
{
private:
	std::tuple<int, int, int> packageDimensions_;

public:
	BlueRay();
	~BlueRay();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

};

#endif // BLURAY_H
