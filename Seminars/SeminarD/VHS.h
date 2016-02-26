#pragma once

#ifndef VHS_H
#define VHS_H

#include "Material.h"
#include "IPackagable.h"
#include "Serializable.h"

class VHS : public Material, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;

	std::string languageTrack;

public:
	VHS();
	~VHS();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	std::string getLanguageTrack() const;
	void setlanguageTrack(const std::string languageTrack);

	void toString();
	void generateFromString(std::string str);
};

#endif // !VHS_H
