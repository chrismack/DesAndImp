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
	unsigned int id;

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
	unsigned int runTime;

	/*
	 * Default language of the film 
	 * == Need to ask about this ==
	 */
	std::string language;

	/*
	 * How much the film is being sold for
	 */
	float retailPrice;

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

	std::vector<std::string> baseToStringArray();
	virtual std::string toString() = 0;



};

#endif /* MATERIAL_H */

