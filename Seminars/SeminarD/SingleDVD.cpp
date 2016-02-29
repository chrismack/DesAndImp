#ifndef SINGLEDVD_CPP
#define SINGLEDVD_CPP

#include "stdafx.h"
#include "SingleDVD.h"

SingleDVD::SingleDVD()
{
}


SingleDVD::~SingleDVD()
{
}

void SingleDVD::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> SingleDVD::getPackageSize() const
{
	return this->packageDimensions_;
}

void SingleDVD::setPackageType(std::string packageType)
{
	this->packageType_ = packageType;
}

std::string SingleDVD::getPackageType() const
{
	return this->packageType_;
}


std::vector<std::string> SingleDVD::getLanguagetracks()
{
	return languageTracks_[0];
}

void SingleDVD::setLanguageTracks(std::vector<std::string> languageTracks)
{
	std::map<int, std::vector<std::string>> langaugeMap;
	langaugeMap.insert(std::pair<int, std::vector<std::string>>(0, languageTracks));
	languageTracks_ = langaugeMap;
}

void SingleDVD::addLanguageTrack(std::string languageTrack)
{
	languageTracks_[0].push_back(languageTrack);
}

std::vector<std::string> SingleDVD::getBonusFeatures()
{
	return bounsFeatures_[0];
}

void SingleDVD::setBonusFeatures(std::vector<std::string> bonusFeatures)
{
	std::map<int, std::vector<std::string>> bonusMap;
	bonusMap.insert(std::pair<int, std::vector<std::string>>(0, bonusFeatures));
	bounsFeatures_ = bonusMap;
}

void SingleDVD::addLBonusFeature(int side, std::string feature)
{
	bounsFeatures_[0].push_back(feature);
}

std::vector<std::string> SingleDVD::getsubtitleTracks()
{
	return subtitleTracks_[0];
}

void SingleDVD::setSubtitleTracks(std::vector<std::string> subtitle)
{
	std::map<int, std::vector<std::string>> subtitleMap;
	subtitleMap.insert(std::pair<int, std::vector<std::string>>(0, subtitle));
	subtitleTracks_ = subtitleMap;
}

void SingleDVD::addSubtitleTrack(std::string track)
{
	subtitleTracks_[0].push_back(track);
}

std::vector<std::string> SingleDVD::getAudioTracks()
{
	return audioTracks_[0];
}

void SingleDVD::setAudioTracks(std::vector<std::string> audio)
{
	std::map<int, std::vector<std::string>> audioMap;
	audioMap.insert(std::pair<int, std::vector<std::string>>(0, audio));
	audioTracks_ = audioMap;
}

void SingleDVD::addAudioTrack(std::string track)
{
	audioTracks_[0].push_back(track);
}

void SingleDVD::setContent(std::vector<std::string> content)
{
	this->content_ = content;
}

void SingleDVD::addContent(std::string content)
{
	this->content_.push_back(content);
}

std::vector<std::string> SingleDVD::getContent()
{
	return this->content_;
}

std::string SingleDVD::toString()
{
	std::string objectString;
	std::vector<std::string> bluRayElements = toStringArray();
	bluRayElements.push_back(this->packageType_);

	std::string packageDimString = "{";
	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)))
		.append("}");

	bluRayElements.push_back(packageDimString);
	bluRayElements.push_back(createStringList(content_));
	bluRayElements.push_back(createStringList(getBonusFeatures()));

	std::stringstream ss;
	for (int i = 0; i < bluRayElements.size(); i++)
	{
		ss << bluRayElements[i];
		ss << ",";
	}
	objectString = ss.str();
	objectString = objectString.substr(0, objectString.length() - 1);

	return objectString;
}

void SingleDVD::generateFromString(std::string str)
{
}

#endif // !SINGLEDVD_CPP
