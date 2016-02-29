#ifndef DISC_CPP
#define DISC_CPP

#include "stdafx.h"
#include "Disc.h"


Disc::Disc()
{
}


Disc::~Disc()
{
}

std::map<int, std::vector<std::string>> Disc::getLanguagetracks()
{
	return this->languageTracks_;
}

void Disc::setLanguageTracks(std::map<int, std::vector<std::string>> languageTracks)
{
	this->languageTracks_ = languageTracks;
}

void Disc::addLanguageTrack(int side, std::string languageTrack)
{
	languageTracks_[side].push_back(languageTrack);
}

void Disc::setBonusFeatures(const std::map<int, std::vector<std::string>> bonusFeatures)
{
	bounsFeatures_ = bonusFeatures;
}

std::map<int, std::vector<std::string>> Disc::getBonusFeatures()
{
	return this->bounsFeatures_;
}

void Disc::addLBonusFeature(int side, std::string feature)
{
	this->bounsFeatures_[side].push_back(feature);
}

void Disc::setSubtitleTracks(const std::map<int, std::vector<std::string>> subtitle)
{
	this->subtitleTracks_ = subtitle;
}

std::map<int, std::vector<std::string>> Disc::getsubtitleTracks()
{
	return this->subtitleTracks_;
}

void Disc::addSubtitleTrack(int side, std::string track)
{
	this->subtitleTracks_[side].push_back(track);
}

void Disc::setAudioTracks(const std::map<int, std::vector<std::string>> subtitle)
{
	this->audioTracks_ = subtitle;
}

std::map<int, std::vector<std::string>> Disc::getAudioTracks()
{
	return this->audioTracks_;
}

void Disc::addAudioTrack(int side, std::string track)
{
	this->audioTracks_[side].push_back(track);
}

std::vector<std::string> Disc::toStringArray()
{
	std::vector<std::string> baseArray = baseToStringArray();


	baseArray.push_back(createStringList(getLanguagetracks()));
	baseArray.push_back(createStringList(getsubtitleTracks()));
	baseArray.push_back(createStringList(getAudioTracks()));
	
	return baseArray;
}

std::string Disc::createStringList(std::map<int, std::vector<std::string>> mapTrack)
{
	std::string tmpString;
	std::stringstream ss;

	std::map<int, std::vector<std::string>>::iterator it;
	if (mapTrack.size() > 0)
	{
		ss << "{";
	}
	for (it = mapTrack.begin(); it != mapTrack.end(); ++it)
	{
		if (it->first == 1)
		{
			ss << "-";
		}
		for (int i = 0; i < it->second.size(); i++)
		{
			ss << it->second[i];
			if (i < it->second.size() - 1)
			{
				ss << "|";
			}
		}
	}
	if (mapTrack.count(1) == 0 && mapTrack.count(0) == 0)
	{
		ss << "-";
	}
	if (mapTrack.size() > 0)
	{
		ss << "}";
	}
	tmpString = ss.str();
	if (tmpString.length() > 1)
	{
		tmpString.substr(tmpString.length() - 1);
	}
	return tmpString;
}

std::string Disc::createStringList(std::vector<std::string> track)
{
	std::string tmpString;
	std::stringstream ss;
	if (track.size() > 1)
	{
		ss << "{";
	}
	for (int i = 0; i < track.size(); i++)
	{
		ss << track[i];
		if (i < track.size() - 1)
		{
			ss << "|";
		}
	}
	tmpString = ss.str();
	tmpString.substr(tmpString.length() - 1);
	if (track.size() > 1)
	{
		tmpString.append("}");
	}

	return tmpString;
}

#endif // !DISC_CPP
