#ifndef BLUERAY_CPP
#define BLURAY_CPP

#include "stdafx.h"
#include "BlueRay.h"

BlueRay::BlueRay()
{
}


BlueRay::~BlueRay()
{
}

void BlueRay::setPackageDimensions(std::tuple<int, int, int> dimensions)
{
	this->packageDimensions_ = dimensions;
}

std::tuple<int, int, int> BlueRay::getPackageSize() const
{
	return this->packageDimensions_;
}

void BlueRay::setPackageType(std::string packageType)
{
	this->packageType_ = packageType;
}

std::string BlueRay::getPackageType() const
{
	return packageType_;
}

std::vector<std::string> BlueRay::getLanguagetracks()
{
	return languageTracks_[0];
}

void BlueRay::setLanguageTracks(std::vector<std::string> languageTracks)
{
	std::map<int, std::vector<std::string>> langaugeMap;
	langaugeMap.insert(std::pair<int, std::vector<std::string>>(0, languageTracks));
	languageTracks_ = langaugeMap;
}

void BlueRay::addLanguageTrack(std::string languageTrack)
{
	languageTracks_[0].push_back(languageTrack);
}

std::vector<std::string> BlueRay::getBonusFeatures()
{
	return bounsFeatures_[0];
}

void BlueRay::setBonusFeatures(std::vector<std::string> bonusFeatures)
{
	std::map<int, std::vector<std::string>> bonusMap;
	bonusMap.insert(std::pair<int, std::vector<std::string>>(0, bonusFeatures));
	bounsFeatures_ = bonusMap;
}

void BlueRay::addLBonusFeature(int side, std::string feature)
{
	bounsFeatures_[0].push_back(feature);
}

std::vector<std::string> BlueRay::getsubtitleTracks()
{
	return subtitleTracks_[0];
}

void BlueRay::setSubtitleTracks(std::vector<std::string> subtitle)
{
	std::map<int, std::vector<std::string>> subtitleMap;
	subtitleMap.insert(std::pair<int, std::vector<std::string>>(0, subtitle));
	subtitleTracks_ = subtitleMap;
}

void BlueRay::addSubtitleTrack(std::string track)
{
	subtitleTracks_[0].push_back(track);
}

std::vector<std::string> BlueRay::getAudioTracks()
{
	return audioTracks_[0];
}

void BlueRay::setAudioTracks(std::vector<std::string> audio)
{
	std::map<int, std::vector<std::string>> audioMap;
	audioMap.insert(std::pair<int, std::vector<std::string>>(0, audio));
	audioTracks_ = audioMap;
}

void BlueRay::addAudioTrack(std::string track)
{
	audioTracks_[0].push_back(track);
}


void BlueRay::setContent(std::vector<std::string> content)
{
	this->content_ = content;
}

void BlueRay::addContent(std::string content)
{
	this->content_.push_back(content);
}

std::vector<std::string> BlueRay::getContent()
{
	return this->content_;
}

//std::string BlueRay::toString()
//{
//	std::string objectString;
//	std::vector<std::string> bluRayElements = toStringArray();
//	bluRayElements.push_back(this->packageType_);
//	
//	std::string packageDimString = "{";
//	packageDimString.append(std::to_string(std::get<0>(this->packageDimensions_)))
//					.append("|")
//					.append(std::to_string(std::get<1>(this->packageDimensions_)))
//					.append("|")
//					.append(std::to_string(std::get<2>(this->packageDimensions_)))
//					.append("}");
//
//	bluRayElements.push_back(packageDimString);
//	bluRayElements.push_back(createStringList(content_));
//	bluRayElements.push_back(createStringList(getBonusFeatures()));
//
//	std::stringstream ss;
//	for (int i = 0; i < bluRayElements.size(); i++)
//	{
//		ss << bluRayElements[i];
//		ss << ",";
//	}
//	objectString = ss.str();
//	objectString = objectString.substr(0, objectString.length() - 1);
//
//	return objectString;
//	
//}


std::vector<std::string> BlueRay::toArray()
{

	std::vector<std::string> bluRayElements = Disc::toArray();
	bluRayElements.push_back(this->packageType_ != "" ? this->packageType_ : " ");

	std::string packageDimString = std::to_string(std::get<0>(this->packageDimensions_))
		.append("|")
		.append(std::to_string(std::get<1>(this->packageDimensions_)))
		.append("|")
		.append(std::to_string(std::get<2>(this->packageDimensions_)));

	bluRayElements.push_back(packageDimString);
	bluRayElements.push_back(createStringList(content_));
	bluRayElements.push_back(createStringList(getBonusFeatures()));
	return bluRayElements;
}

void BlueRay::populate(std::vector<std::string> elements)
{
	bounsFeatures_ = stringToMap(elements[15]);
	elements.pop_back();
	content_ = split(elements[14], "|");
	elements.pop_back();
	
	std::vector<std::string> packageVector;
	packageVector = split(elements[13], "|");
	packageDimensions_ = std::tuple<int, int, int>(std::stoi(packageVector[0]), std::stoi(packageVector[1]), std::stoi(packageVector[2]));
	elements.pop_back();

	packageType_ = elements[12];
	elements.pop_back();

	Disc::populate(elements);


}

#endif // !BLUERAY_CPP
