#pragma once

#ifndef DOUBLEDVD_H
#define DOUBLEDVD_H

#include "SingleDVD.h"
#include "IPackagable.h"
#include <map>

class DoubleDVD : public Disc, public IPackagable
{
private:

	/*
	 * Size of the package X|Y|Z
	 */
	std::tuple<int, int, int> packageDimensions_;

	/*
	 * The type of package the class has
	 */
	std::string packageType_;

	/*
	 * Content on the disc and the side that it is on
	 */
	std::map < int, std::vector<std::string>> contentMap_;


public:
	DoubleDVD();
	~DoubleDVD();

	/*
	* Part of packageable interface
	*/

	/*
	* set and get package dimensions
	*/
	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	/*
	* set and get package type
	*/
	void setPackageType(std::string packageType);
	std::string getPackageType() const;

	/*
	 * content_ getters, setters, 
	 */
	std::map< int, std::vector<std::string> > getAllContent();
	void setContent(const std::map< int, std::vector<std::string>> content);
	std::vector<std::string> getContentOnSide(const int side);
	void setContentOnSide(int, std::vector<std::string> content);

	/*
	* Override toArray and populate from Material class
	*/
	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> elements) override;

};

#endif // !DOUBLEDVD_H
