#pragma once

#ifndef VHS_H
#define VHS_H

#include "Material.h"
#include "IPackagable.h"

class VHS : public Material, public IPackagable
{
public:
	VHS();
	~VHS();

	virtual std::pair<int, int> getPackageSize();
};

#endif // !VHS_H
