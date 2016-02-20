#pragma once

#ifndef BLURAY_H
#define BLURAY_H

#include "Disc.h"
#include "IPackagable.h"
class BlueRay : public Disc, public IPackagable 
{
private:
	std::pair<int, int> packageDimensions_;

public:
	BlueRay();
	~BlueRay();

	void setPackageDimensions(std::pair<int, int> dimensions);
	std::pair<int, int> getPackageSize() const;

};

#endif // BLURAY_H
