#pragma once

#ifndef VHS_H
#define VHS_H

#include "Material.h"
#include "IPackagable.h"

class VHS : public Material, public IPackagable
{
private:
	std::pair<int, int> packageDimensions_;
public:
	VHS();
	~VHS();

	void setPackageDimensions(std::pair<int, int> dimensions);
	std::pair<int, int> getPackageSize() const;
};

#endif // !VHS_H
