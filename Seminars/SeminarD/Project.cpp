#ifndef PROJECT_CPP
#define PROJECT_CPP

#include "stdafx.h"
#include "Project.h"

Project::Project()
{
}


Project::~Project()
{
}

std::string Project::getTitle() const
{
	return this->title_;
}

std::string Project::getSummary() const 
{
	return this->summary_;
}

std::string Project::getGenre() const 
{
	return this->genre_;
}

long Project::getReleaseDate() const
{
	return this->releaseDate_;
}

std::vector<std::string> Project::getFilmingLocations() const
{
	return this->filmingLocations_;
}

std::string Project::getLanguage() const
{
	return this->language_;
}

std::vector<std::string> Project::getKeywords() const
{
	return this->keywords_;
}

std::vector<int> Project::getTicketSales() const
{
	return this->weeklyTicketSales_;
}

void Project::setTitle(const std::string title)
{
	this->title_ = title;
}

void Project::setSummary(const std::string summary)
{
	this->summary_ = summary;
}

void Project::setGenre(const std::string genre)
{
	this->genre_ = genre;
}

void Project::setReleaseDate(const long releasedate)
{
	this->releaseDate_ = releasedate;
}

void Project::setFilmingLocations(const std::vector<std::string> locations)
{
	this->filmingLocations_ = locations;
}

void Project::setLanguage(const std::string language)
{
	this->language_ = language;
}

void Project::setKeywords(const std::vector<std::string> keywords)
{
	this->keywords_ = keywords;
}

void Project::setTicketSales(const std::vector<int> ticketSales)
{
	this->weeklyTicketSales_ = ticketSales;
}

std::vector<Material*> Project::getMaterials()
{
	return materials_;
}

void Project::setMaterials(std::vector<Material*> materials)
{
	this->materials_ = materials;
}

void Project::addMaterial(Material* material)
{
	this->materials_.push_back(material);
}


#endif // !PROJECT_CPP
