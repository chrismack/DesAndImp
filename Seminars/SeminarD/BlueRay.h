#pragma once

#ifndef BLURAY_H
#define BLURAY_H

#include "Disc.h"
#include "IPackagable.h"
#include "Serializable.h"

class BlueRay : public Disc, public IPackagable, public Serializable
{
private:
	std::tuple<int, int, int> packageDimensions_;

public:
	BlueRay();
	~BlueRay();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	void toString();
	void generateFromString(std::string str);

};

#endif // BLURAY_H
