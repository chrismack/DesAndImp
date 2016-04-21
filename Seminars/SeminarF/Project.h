#pragma once

#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include "Material.h"
class Project
{
private:

	/*
	 * The title of a project
	 */
	std::string title_;

	/*
	 * The project summary
	 */
	std::string summary_;

	/*
	 * The genre of a project
	 * string used as sub-genres can be seperated by dashes or spaces
	 */
	std::string genre_;

	/*
	 * The release date of a project
	 * Long used to support the unix clock
	 */
	long releaseDate_;

	/*
	 * List of all the filming locations
	 */
	std::vector<std::string> filmingLocations_;
	
	/*
	 * The language of the project
	 */
	std::string language_;

	/*
	 * List of all the key words for the project
	 */
	std::vector<std::string> keywords_;

	/*
	 * Number of tickets sold each week
	 *
	 * Could consider using a map to track start date of each week
	 * however this is probably redundant
	 */
	std::vector<int> weeklyTicketSales_;

	/*
	 * List of all the materials that are associated with the project
	 */
	std::vector<Material*> materials_;

	std::vector<std::string> crew_;

	/*
	 * split a string into a list around a specified delemeter
	 */
	std::vector<std::string> split(std::string string, std::string del);

public:
	Project();
	~Project();

	/*
	 * GETTERS
	 */
	std::string getTitle() const;
	std::string getSummary() const;
	std::string getGenre() const;
	long getReleaseDate() const;
	std::vector<std::string> getFilmingLocations() const;
	std::string getLanguage() const;
	std::vector<std::string> getKeywords() const;
	std::vector<int> getTicketSales() const;
	std::vector<std::string> getCrew() const;

	/*
	 * SETTERS
	 */
	void setTitle(const std::string title);
	void setSummary(const std::string summary);
	void setGenre(const std::string genre);
	void setReleaseDate(const long releasedate);
	void setFilmingLocations(const std::vector<std::string> locations);
	void setLanguage(const std::string language);
	void setKeywords(const std::vector<std::string> keywords);
	void setTicketSales(const std::vector<int> ticketSales);
	void setCrew(const std::vector<std::string> crew);

	/*
	 * get the list of materials_ in the project
	 */
	std::vector<Material*> getMaterials();

	/*
	 * set the list of materials in the project
	 */
	void setMaterials(std::vector<Material*> materials);

	/*
	 * Add a material to the project
	 */
	void addMaterial(Material* material);

	/*
	 * Serves the same function as the toArray and populate in material 
	 * used to generate a list of attributes and load attributes from vector
	 */
	std::vector<std::string> toArray();
	void populate(std::vector<std::string> elements);
};

#endif // !PROJECT_H
