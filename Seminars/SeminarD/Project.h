#pragma once

#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <vector>
#include "Material.h"
class Project
{
private:
	std::string title_;
	std::string summary_;
	std::string genre_;
	long releaseDate_;
	std::vector<std::string> filmingLocations_;
	std::string language_;
	std::vector<std::string> keywords_;
	std::vector<int> weeklyTicketSales_;

	std::vector<Material*> materials_;

	std::vector<std::string> split(std::string string, std::string del);



public:
	Project();
	~Project();

	std::string getTitle() const;
	std::string getSummary() const;
	std::string getGenre() const;
	long getReleaseDate() const;
	std::vector<std::string> getFilmingLocations() const;
	std::string getLanguage() const;
	std::vector<std::string> getKeywords() const;
	std::vector<int> getTicketSales() const;

	void setTitle(const std::string title);
	void setSummary(const std::string summary);
	void setGenre(const std::string genre);
	void setReleaseDate(const long releasedate);
	void setFilmingLocations(const std::vector<std::string> locations);
	void setLanguage(const std::string language);
	void setKeywords(const std::vector<std::string> keywords);
	void setTicketSales(const std::vector<int> ticketSales);

	std::vector<Material*> getMaterials();
	void setMaterials(std::vector<Material*> materials);
	void addMaterial(Material* material);

	std::vector<std::string> toArray();
	void populate(std::vector<std::string> elements);
};

#endif // !PROJECT_H
