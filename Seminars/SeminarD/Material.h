#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once

#include <string>

class Material
{
private:
	
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
	 *
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


public:
	Material();
	~Material();
};

#endif /* MATERIAL_H */

