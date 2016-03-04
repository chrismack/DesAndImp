#pragma once

#ifndef DOUBLEDVD_H
#define DOUBLEDVD_H

#include "SingleDVD.h"
#include "IPackagable.h"
#include <map>

class DoubleDVD : public Disc, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;

	std::map < int, std::vector<std::string>> contentMap_;

	std::string packageType_;

public:
	DoubleDVD();
	~DoubleDVD();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	void setPackageType(std::string packageType);
	std::string getPackageType() const;

	std::map< int, std::vector<std::string> > getAllContent();
	void setContent(const std::map< int, std::vector<std::string>> content);
	std::vector<std::string> getContentOnSide(const int side);
	void setContentOnSide(int, std::vector<std::string> content);

	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> elements) override;

};

#endif // !DOUBLEDVD_H
