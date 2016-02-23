#pragma once

#ifndef DOUBLEDVD_H
#define DOUBLEDVD_H

#include "SingleDVD.h"
#include "IPackagable.h"
#include <map>

class DoubleDVD : public SingleDVD, public IPackagable
{
private:
	std::tuple<int, int, int> packageDimensions_;

	std::map < int, SDI::DynArray<std::string> > contentMap_;

public:
	DoubleDVD();
	~DoubleDVD();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	std::map< int, SDI::DynArray<std::string> > getAllContent() const;
	void setContent(const std::map< int, SDI::DynArray<std::string>> content);
	SDI::DynArray<std::string> getContentOnSide(const int side) const;
	void setContentOnSide(const int, const SDI::DynArray<std::string> content);

};

#endif // !DOUBLEDVD_H
