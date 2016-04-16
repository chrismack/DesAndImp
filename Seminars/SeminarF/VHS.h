#pragma once

#ifndef VHS_H
#define VHS_H

#include "Material.h"
#include "IPackagable.h"

class VHS : public Material, public IPackagable
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
	 * VHS can only contain a single language track
	 */
	std::string languageTrack_;

	/*
	 * VHS can only have one audio track
	 */
	std::string audioTrack_;
	
	/*
	 * content on the VHS
	 */
	std::vector<std::string> content_;


public:
	VHS();
	~VHS();

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
	 * Get and set the language track
	 */
	std::string getLanguageTrack() const;
	void setlanguageTrack(const std::string languageTrack);

	/*
	 * Get, set add to content_
	 */
	void setContent(std::vector<std::string> content);
	void addContent(std::string content);
	std::vector<std::string> getContent();

	/*
	* Get, set add to content_
	*/
	void setAudioTrack(std::string content);
	std::string getAudioTrack();

	/*
	* Override toArray and populate from Material class
	*/
	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> string) override;

	/*
	* convert a vector into a string to be read from a file
	*/
	std::string createStringList(std::vector<std::string> track);
};

#endif // !VHS_H
