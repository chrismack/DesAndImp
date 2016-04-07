#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

#include "../SeminarB/DynArray.h"

#include <assert.h>
#include <string>
#include <vector>

class Material
{
private: /* Variables */
	
	/*
	 * Unique id for the film
	 */
	int id = -1;

	/*
	 * Name of the film
	 */
	std::string filmTitle;

	/*
	 * What class should be generated
	 */
	std::string format;

	/*
	 * What audio format the film uses
	 */
	std::string audioFormat;

	/*
	 * How long the film runs for in seconds
	 */
	int runTime = -1;

	/*
	 * Default language of the film 
	 * == Need to ask about this ==
	 */
	std::string language;

	/*
	 * How much the film is being sold for
	 */
	float retailPrice = -1;

	/*
	 * == Need to ask about this ==
	 */
	std::string subtitles;

	/*
	 * Size of the film ie 16 : 9
	 */
	std::pair<int, int> frameAspect;


public: /* Functions */

	Material();
	~Material();

	/*
	 * ======= GETTERS =======
	 */

	int getId() const;
	std::string getFilmTitle() const;
	std::string getFormat() const;
	std::string getAudioFormat() const;
	unsigned int getRunTime() const;
	std::string getLanguage() const;
	float getRetailPrice() const;
	std::string getSubtitles() const;
	std::pair<int, int> getAspectRatio() const;

	/*
	 * =======SETTERS==========
	 */
	void setID(const int id);
	void setFilmTitle(const std::string filmTitle);
	void setFormat(const std::string format);
	void setAudioFormat(std::string audioFormat);
	void setRunTime(const unsigned int runTime);
	void setLanguage(const std::string language);
	void setRetailPrice(const float runTime);
	void setSubtitles(const std::string subtitles);
	void setAspectRation(const std::pair<int, int> aspectRatio);

	/*
	 * gets all class attributes and puts them into a vector
	 */
	virtual std::vector<std::string> toArray();

	/*
	 * Takes attributes from a vector and set class attributes
	 * Vector has to be in correct order and have correct size
	 */
	virtual void populate(std::vector<std::string>);

	/*
	 * Split string on specified delimeter
	 */
	std::vector<std::string> split(std::string string, std::string del);

};

#endif /* MATERIAL_H */

