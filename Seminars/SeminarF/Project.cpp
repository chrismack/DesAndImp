#ifndef PROJECT_CPP
#define PROJECT_CPP
#define _CRT_SECURE_NO_WARNINGS // Used for strtok doesn't compile with out

#include <sstream>

#include "stdafx.h"
#include "Project.h"

#include "SingleDVD.h"
#include "DoubleDVD.h"
#include "BlueRay.h"
#include "ComboBox.h"
#include "VHS.h"


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

std::vector<std::string> Project::toArray()
{
	std::vector<std::string> elements;

	elements.push_back(title_);
	elements.push_back(summary_);
	elements.push_back(genre_);
	elements.push_back(std::to_string(releaseDate_));
	
	std::stringstream filmLocStrings;
	for (int i = 0; i < filmingLocations_.size(); i++)
	{
		filmLocStrings << filmingLocations_[i];
		if (i < filmingLocations_.size() - 1)
		{
			filmLocStrings << "|";
		}
	}

	elements.push_back(filmLocStrings.str());
	elements.push_back(language_);
	
	std::stringstream keywordStrings;
	for (int i = 0; i < keywords_.size(); i++)
	{
		keywordStrings << keywords_[i];
		if (i < keywords_.size() - 1)
		{
			keywordStrings << "|";
		}
	}
	elements.push_back(keywordStrings.str());

	std::stringstream salesStrings;
	for (int i = 0; i < weeklyTicketSales_.size(); i++)
	{
		salesStrings << weeklyTicketSales_[i];
		if (i < weeklyTicketSales_.size() - 1)
		{
			salesStrings << "|";
		}
	}
	elements.push_back(salesStrings.str());

	std::stringstream materialString;
	materialString << "{";
	for (int i = 0; i < materials_.size(); i++)
	{
		int arraySize = materials_[i]->toArray().size();
		std::vector<std::string> localContent = materials_[i]->toArray();
		for (int j = 0; j < arraySize; j++)
		{
			materialString << localContent[j];
			if (j < arraySize - 1)
			{
				materialString << ",";
			}
		}
		if (i < materials_.size() - 1)
		{
			materialString << "~";
		}
	}
	materialString << "}";
	elements.push_back(materialString.str());
	return elements;
}

void Project::populate(std::vector<std::string> elements)
{
	title_ = elements[0];
	summary_ = elements[1];
	genre_ = elements[2];
	releaseDate_ = stol(elements[3]);
	filmingLocations_ = split(elements[4], "|");
	language_ = elements[5];
	keywords_ = split(elements[6], "|");
	
	std::vector<std::string> weeklySalesStrings = split(elements[7], "|");
	std::vector<int> weeklySales;
	for (int i = 0; i < weeklySalesStrings.size(); i++)
	{
		weeklySales.push_back(std::stoi(weeklySalesStrings[i]));
	}
	weeklyTicketSales_ = weeklySales;

	if (elements[8][0] == '{')
	{
		elements[8] = elements[8].substr(1, elements[8].length() - 2);
		std::vector<std::string> materialStrings = split(elements[8], "~");
		for (int i = 0; i < materialStrings.size(); i++)
		{
			std::string type = split(materialStrings[i], ",")[2];
			std::vector<std::string> materialElements = split(materialStrings[i], ",");

			if (type =="BluRay")
			{
				Material* material = new BlueRay;
				BlueRay* bluRay = static_cast<BlueRay*>(material);
				bluRay->populate(materialElements);
				materials_.push_back(bluRay);
				
			}
			else if (type == "SingleDVD")
			{
				Material* material = new SingleDVD;
				SingleDVD* singleDVD = static_cast<SingleDVD*>(material);
				singleDVD->populate(materialElements);
				materials_.push_back(singleDVD);
			}
			else if (type == "DoubleDVD")
			{
				Material* material = new DoubleDVD;
				DoubleDVD* doubleDVD = static_cast<DoubleDVD*>(material);
				doubleDVD->populate(materialElements);
				materials_.push_back(doubleDVD);
			}
			else if (type == "Combo")
			{
				std::string dvds;
				dvds = materialStrings[i].substr(materialStrings[i].find('['), materialStrings[i].length());
				materialStrings[i] = materialStrings[i].substr(0, materialStrings[i].find('['));
				materialElements = split(materialStrings[i], ",");
				materialElements.push_back(dvds);

				Material* material = new ComboBox;
				ComboBox* combo = static_cast<ComboBox*>(material);
				combo->populate(materialElements);
				materials_.push_back(combo);
			}
			else if (type == "VHS")
			{
				Material* material = new VHS;
				VHS* vhs = static_cast<VHS*>(material);
				vhs->populate(materialElements);
				materials_.push_back(vhs);
			}
			else
			{
				return;
			}
		}
	}
}

std::vector<std::string> Project::split(std::string string, std::string del)
{
	/* http://stackoverflow.com/questions/16286095/similar-function-to-javas-string-split-in-c */

	char* cstr = const_cast<char*>(string.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, del.c_str());
	while (current != NULL)
	{
		arr.push_back(current);
		current = strtok(NULL, del.c_str());
	}

	return arr;
}

#endif // !PROJECT_CPP
