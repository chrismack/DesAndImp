#pragma once

#ifndef BLURAY_H
#define BLURAY_H

#include "Disc.h"
#include "IPackagable.h"
class BlueRay : public Disc, public IPackagable 
{
public:
	BlueRay();
	~BlueRay();

	virtual std::pair<int, int> getPackageSize();

};

#endif // BLURAY_H
