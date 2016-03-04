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

//std::vector<std::string> Disc::toStringArray()
//{
//	std::vector<std::string> baseArray = baseToStringArray();
//
//
//	baseArray.push_back(createStringList(getLanguagetracks()));
//	baseArray.push_back(createStringList(getsubtitleTracks()));
//	baseArray.push_back(createStringList(getAudioTracks()));
//	
//	return baseArray;
//}


std::string Disc::createStringList(std::map<int, std::vector<std::string>> mapTrack)
{
	std::string tmpString;
	std::stringstream ss;

	std::map<int, std::vector<std::string>>::iterator it;
	for (it = mapTrack.begin(); it != mapTrack.end(); ++it)
	{
		if (it->first == 1)
		{
			ss << "-";
			if(it->second.size() == 0)
			{
				ss << " ";
			}
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
		ss << " ";
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

	for (int i = 0; i < track.size(); i++)
	{
		ss << track[i];
		if (i < track.size() - 1)
		{
			ss << "|";
		}
	}
	tmpString = ss.str();
	if (tmpString.length() > 0)
	{
		tmpString.substr(tmpString.length() - 1);
	}
	else
	{
		tmpString = " ";
	}


	return tmpString;
}

std::vector<std::string> Disc::toArray()
{
	std::vector<std::string> attributes = Material::toArray();
	
	attributes.push_back(createStringList(getLanguagetracks()));
	attributes.push_back(createStringList(getsubtitleTracks()));
	attributes.push_back(createStringList(getAudioTracks()));

	return attributes;
}

void Disc::populate(std::vector<std::string> elements)
{
	// If the string is a map
	audioTracks_    = stringToMap(elements[11]);
	elements.pop_back();
	subtitleTracks_ = stringToMap(elements[10]);
	elements.pop_back();
	languageTracks_ = stringToMap(elements[9]);
	elements.pop_back();

	Material::populate(elements);
}

std::map<int, std::vector<std::string>> Disc::stringToMap(std::string string)
{
	std::map<int, std::vector<std::string>> trackMap;
	if (string.find("-") != std::string::npos)
	{
		std::vector<std::string> mapArray = split(string, "-");
		if (mapArray.size() != 1)
		{
			//Disc only has 2 sides
			for (int i = 0; i < 2; i++)
			{
				trackMap[i] = split(mapArray[i], "|");
			}
		}
		else
		{
			trackMap[0] = std::vector<std::string>{" "};
			trackMap[1] = split(mapArray[0], "|");
		}
	}
	else
	{
		trackMap[0] = split(string, "|");
	}
	return trackMap;
}

#endif // !DISC_CPP
