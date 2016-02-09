#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

#include <string>

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
	 * == Need to ask about this == 
	 */
	std::string format;

	/*
	 * == Need to ask about this ==
	 */
	std::string audioFormat;

	/*
	 * How long the film runs for in seconds
	 */
	unsigned int runTime;

	/*
	 * Language of the film
	 * Language of sub titles
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
	float retailPrice() const;
	std::string getSubtitles() const;
	std::pair<int, int> getAspectRatio() const;

	/*
	 * =======================
	 */




};

#endif /* MATERIAL_H */

