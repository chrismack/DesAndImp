#pragma once

#ifndef DISC_H
#define DISC_H

#include "Material.h"

#include "../SeminarB/DynArray.h"
#include <sstream>
#include <map>
#include <vector>
#include <string>

class Disc : public Material
{
protected:
	std::map<int, std::vector<std::string>> languageTracks_;
	std::map<int, std::vector<std::string>> bounsFeatures_;
	std::map<int, std::vector<std::string>> subtitleTracks_;
	std::map<int, std::vector<std::string>> audioTracks_;

	std::string createStringList(std::map<int, std::vector<std::string>> track);
	std::string createStringList(std::vector<std::string> track);

	

public:
	Disc();
	~Disc();
	
	std::map<int, std::vector<std::string>> getLanguagetracks();
	void setLanguageTracks(std::map<int, std::vector<std::string>> languageTracks);
	void addLanguageTrack(int side, std::string);

	std::map<int, std::vector<std::string>> getBonusFeatures();
	void setBonusFeatures(std::map<int, std::vector<std::string>> bonusFeatures);
	void addLBonusFeature(int side, std::string);

	std::map<int, std::vector<std::string>> getsubtitleTracks();
	void setSubtitleTracks(std::map<int, std::vector<std::string>> subtitle);
	void addSubtitleTrack(int side, std::string track);

	std::map<int, std::vector<std::string>> getAudioTracks();
	void setAudioTracks(std::map<int, std::vector<std::string>> audioTrack);
	void addAudioTrack(int side, std::string track);

	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> elements) override;

	std::map<int, std::vector<std::string>> stringToMap(std::string string);

};

#endif // !DISC_H
