#pragma once

#ifndef SINGLEDVD_H
#define SINGLEDVD_G

#include "Disc.h"
#include "IPackagable.h"

class SingleDVD : public Disc, public IPackagable
{
public:
	SingleDVD();
	~SingleDVD();

	virtual std::pair<int, int> getPackageSize();
};

#endif // !SINGLEDVD_H
