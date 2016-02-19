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
};

#endif // !VHS_H
