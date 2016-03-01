#pragma once

#ifndef VHS_H
#define VHS_H

#include "Material.h"
#include "IPackagable.h"

class VHS : public Material, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;

	std::string languageTrack_;

	std::string packageType_;

	std::vector<std::string> content_;

	std::string audioTrack;

public:
	VHS();
	~VHS();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	std::string getLanguageTrack() const;
	void setlanguageTrack(const std::string languageTrack);

	void setPackageType(std::string packageType);
	std::string getPackageType() const;

	void setContent(std::vector<std::string> content);
	void addContent(std::string content);
	std::vector<std::string> getContent();

	std::string toString();
	void generateFromString(std::string str);

	std::string createStringList(std::vector<std::string> track);
};

#endif // !VHS_H
