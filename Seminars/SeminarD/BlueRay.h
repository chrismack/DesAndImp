#pragma once

#ifndef BLURAY_H
#define BLURAY_H

#include "Disc.h"
#include "IPackagable.h"

class BlueRay : public Disc, public IPackagable
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
	 * The content on the disc
	 */
	std::vector<std::string> content_;


public:
	BlueRay();
	~BlueRay();

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
	 * Language track get, set, add
	 */
	std::vector<std::string> getLanguagetracks();
	void setLanguageTracks(std::vector<std::string> languageTracks);
	void addLanguageTrack(std::string);

	/*
	 * Bonus Features track get, set, add
	 */
	std::vector<std::string> getBonusFeatures();
	void setBonusFeatures(std::vector<std::string> bonusFeatures);
	void addLBonusFeature(int side, std::string);

	/*
	 * Subtitles track get, set, add
	 */
	std::vector<std::string> getsubtitleTracks();
	void setSubtitleTracks(std::vector<std::string> subtitle);
	void addSubtitleTrack(std::string track);

	/*
	 * Audio track get, set, add
	 */
	std::vector<std::string> getAudioTracks();
	void setAudioTracks(std::vector<std::string> audio);
	void addAudioTrack(std::string track);

	/*
	 * get, set, add content_
	 */
	void setContent(std::vector<std::string> content);
	void addContent(std::string content);
	std::vector<std::string> getContent();

	/*
	 * Override toArray and populate from Material class
	 */
	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> elements) override;

};

#endif // BLURAY_H
