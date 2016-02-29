#pragma once

#ifndef SINGLEDVD_H
#define SINGLEDVD_G

#include "Disc.h"
#include "IPackagable.h"
#include "Serializable.h"

class SingleDVD : public Disc, public IPackagable, public Serializable
{
private:
	std::tuple<int, int, int> packageDimensions_;
	std::string packageType_;

	std::vector<std::string> content_;
public:
	SingleDVD();
	~SingleDVD();

	void setPackageDimensions(const std::tuple<int, int, int> dimensions);
	std::tuple<int, int, int> getPackageSize() const;

	void setPackageType(std::string packageType);
	std::string getPackageType() const;


	std::vector<std::string> getLanguagetracks();
	void setLanguageTracks(std::vector<std::string> languageTracks);
	void addLanguageTrack(std::string);

	std::vector<std::string> getBonusFeatures();
	void setBonusFeatures(std::vector<std::string> bonusFeatures);
	void addLBonusFeature(int side, std::string);

	std::vector<std::string> getsubtitleTracks();
	void setSubtitleTracks(std::vector<std::string> subtitle);
	void addSubtitleTrack(std::string track);

	std::vector<std::string> getAudioTracks();
	void setAudioTracks(std::vector<std::string> audio);
	void addAudioTrack(std::string track);

	void setContent(std::vector<std::string> content);
	void addContent(std::string content);
	std::vector<std::string> getContent();

	std::string toString();
	void generateFromString(std::string str);
};

#endif // !SINGLEDVD_H
