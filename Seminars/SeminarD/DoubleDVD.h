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
};

#endif // !DOUBLEDVD_H
