#pragma once

#ifndef DOUBLEDVD_H
#define DOUBLEDVD_H

#include "SingleDVD.h"
#include "IPackagable.h"

class DoubleDVD : public SingleDVD, public IPackagable
{
public:
	DoubleDVD();
	~DoubleDVD();

	virtual std::pair<int, int> getPackageSize();
};

#endif // !DOUBLEDVD_H
