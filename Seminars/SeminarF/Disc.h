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
	/*
	 * Map of tracks, double sided dvds will use 0-1
	 * singleDVD and BluRay will use only map[0]
	 */

	/*
	 * side of disc and the language tracks they hold
	 */
	std::map<int, std::vector<std::string>> languageTracks_;
	
	/*
	* side of disc and the bonus features tracks they hold
	*/
	std::map<int, std::vector<std::string>> bounsFeatures_;
	
	/*
	* side of disc and the subtitles tracks they hold
	*/
	std::map<int, std::vector<std::string>> subtitleTracks_;
	
	/*
	* side of disc and the audio tracks they hold
	*/
	std::map<int, std::vector<std::string>> audioTracks_;

	/*
	 * convert a map into a string to be read from file
	 */
	std::string createStringList(std::map<int, std::vector<std::string>> track);

	/*
	 * convert a vector into a string to be read from a file
	 */
	std::string createStringList(std::vector<std::string> track);

	

public:
	Disc();
	~Disc();
	
	/*
	 * languageTracks_ get,set, add
	 */
	std::map<int, std::vector<std::string>> getLanguagetracks();
	void setLanguageTracks(std::map<int, std::vector<std::string>> languageTracks);
	void addLanguageTrack(int side, std::string);

	/*
	 * bounsFeatures_ get,set, add
	 */
	std::map<int, std::vector<std::string>> getBonusFeatures();
	void setBonusFeatures(std::map<int, std::vector<std::string>> bonusFeatures);
	void addLBonusFeature(int side, std::string);

	/*
	 * subtitleTracks_ get,set, add
	 */
	std::map<int, std::vector<std::string>> getsubtitleTracks();
	void setSubtitleTracks(std::map<int, std::vector<std::string>> subtitle);
	void addSubtitleTrack(int side, std::string track);

	/*
	 * audioTracks_ get,set, add
	 */
	std::map<int, std::vector<std::string>> getAudioTracks();
	void setAudioTracks(std::map<int, std::vector<std::string>> audioTrack);
	void addAudioTrack(int side, std::string track);

	/*
	* Override toArray and populate from Material class
	*/
	std::vector<std::string> toArray() override;
	void populate(std::vector<std::string> elements) override;

	/*
	 * convert the string generate by createStringList(map) back to a map
	 */
	std::map<int, std::vector<std::string>> stringToMap(std::string string);

};

#endif // !DISC_H
