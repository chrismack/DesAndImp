#pragma once

#ifndef PROJECTMANAGER_CPP
#define PROJECTMANAGER_CPP

#include "stdafx.h"
#include "ProjectManager.h"

#include <iostream>
#include <fstream>
#include <time.h>

#include "Logger.h"

#include "MaterialFactory.h"
#include "CSVHandler.h"
#include "XMLHandler.h"

#include "BlueRay.h"


#define _CRT_SECURE_NO_WARNINGS


ProjectManager::ProjectManager()
{
	this->logger = LogHandler::getHandler()->logger;
	this->logger->setLogLevel(SDI::Logger::LogLevel::ALL);
	this->logger->info("Starting the Project Manager");

	materialCount = -1;
}


ProjectManager::~ProjectManager()
{
	logger->debug("closing project manager");
	for (Material* material : materials_)
	{
		delete material;
	}

	for (Material* material : projectAssociatedMaterials)
	{
		delete material;
	}

	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		delete it->first;
	}
}

/*
 * Create default save file and import any data that is contained in the def location
 *
 * If no data has been saved (fresh start) prompt for import
 */
bool ProjectManager::setupSaveFile()
{
	logger->info("setting up save file");
	std::fstream saveFile(defaultSavePath);
	
	if (! fileExists(defaultSavePath) || saveFile.peek() == std::fstream::traits_type::eof())	// File doesn't exists or is empty
	{
		logger->info("file empty");
		saveFile.open(defaultSavePath, std::fstream::in | std::fstream::out | std::fstream::app);		// Create file if it doesn't exist
		saveFile.close();
	
		// File doesn't exist may want to import from and existing file
		return false;
	}
	else
	{
		logger->info("default file found");
		saveFile.close();
		importFile(defaultSavePath);
		//importCSV(defaultSavePath);
		return true;
	}
}

/*
 * Try to import a file from a specified path
 *
 * return if the file has been imported
 */
bool ProjectManager::importFile(std::string path)
{
	
	logger->info("Importing " + path);
	if (fileExists(path))
	{
		logger->debug("file exists");
		std::string extension = path.substr(path.find_last_of('.') + 1);	// Get the extension of the file that is being imported
		if (extension == "csv")
		{
			logger->debug("Starting csv import");
			importCSV(path);
			logger->debug("Finished csv import");
			return true;
		}
		else if (extension == "xml")
		{
			logger->debug("Starting xml import");

			// TODO : Need to implement XML handler like the CSV handler
			importXML(path);

			logger->debug("Finished xml import");
			return true;
		}
		else
		{
			logger->info("file :" + path + " could not be imported");
			return false;
		}

		// If time is available should look into JSON support

	}
	return false;
}

void ProjectManager::save()
{
	if (std::remove(defaultSavePath.c_str()) != 0)
	{
		//error
	}
	else
	{

	}
	logger->info("saving file");
	std::ofstream saveFile(defaultSavePath);
	saveFile.close();

	MaterialFactory* mf = new MaterialFactory();
	XMLHandler xmlHandler(defaultSavePath.c_str(), mf);

	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		xmlHandler.writeToFile(it->first, it->second);
	}

	for (Material* material : materials_)
	{
		if (material != nullptr)
			xmlHandler.writeToFile(material);
	}
	delete mf;
}

/*
 * Import projects and materials that have been stored in a CSV file
 * Imports lines to materials_ and projects_
 */
void ProjectManager::importCSV(const std::string &CSV)
{
	logger->info("importing csv");
	MaterialFactory* mf = new MaterialFactory();
	CSVHandler csvHandler(CSV, mf);

	/*
	* Append materials to list of existing materials
	*/
	std::vector<Material*> materialsFromFile = csvHandler.getMaterialsFromFile();
	for (int i = 0; i < materialsFromFile.size(); i++)											// Make imported ids unique to the new set
	{
		materialCount += 1;
		materialsFromFile[i]->setID(materialCount);
	}
	materials_.insert(materials_.end(), materialsFromFile.begin(), materialsFromFile.end());	// Append to existing projects
	materialsFromFile.clear();

	/*
	 * Append projects to list of existing projects
	 */
	//std::vector<Project*> projectsFromFile = csvHandler.getProjectsFromFile();
	
	std::map<Project*, bool> projectsFromFile = csvHandler.getProjects();
	std::map<Project*, bool>::iterator it;

	for (it = projectsFromFile.begin(); it != projectsFromFile.end(); ++it)
	{

		for (Material* material : it->first->getMaterials())
		{
			if (material != nullptr)
			{
				//material->setID(materials_.size());
				materialCount += 1;
				material->setID(materialCount);
				projectAssociatedMaterials.push_back(material);
			}
		}
		projects_.insert(std::pair<Project*, bool>(it->first, it->second));
	}
		
	logger->debug("csv import finished");
	delete mf;
}

void ProjectManager::importXML(const std::string & XML)
{
	MaterialFactory* mf = new MaterialFactory();
	XMLHandler xmlHandler(XML, mf);

	logger->info("importing xml");

	/*
	* Append materials to list of existing materials
	*/
	std::vector<Material*> materialsFromFile = xmlHandler.getMaterialsFromFile();
	for (int i = 0; i < materialsFromFile.size(); i++)											// Make imported ids unique to the new set
	{
		materialCount += 1;
		materialsFromFile[i]->setID(materialCount);
	}
	materials_.insert(materials_.end(), materialsFromFile.begin(), materialsFromFile.end());	// Append to existing projects
	materialsFromFile.clear();

	/*
	* Append projects to list of existing projects
	*/
	//std::vector<Project*> projectsFromFile = csvHandler.getProjectsFromFile();

	std::map<Project*, bool> projectsFromFile = xmlHandler.getProjectsFromFile();
	std::map<Project*, bool>::iterator it;

	for (it = projectsFromFile.begin(); it != projectsFromFile.end(); ++it)
	{

		for (Material* material : it->first->getMaterials())
		{
			if (material != nullptr)
			{
				//material->setID(materials_.size());
				materialCount += 1;
				material->setID(materialCount);
				projectAssociatedMaterials.push_back(material);
			}
		}
		projects_.insert(std::pair<Project*, bool>(it->first, it->second));
	}

	logger->debug("xml import finished");
	delete mf;
}


/*
 * Check if a file in a specified path exists
 * Returns true or false depending if the file could be found
 */
const bool ProjectManager::fileExists(const std::string & path)
{
	std::ifstream file(path);
	if (file.good())
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

std::vector<Disc*> ProjectManager::getExistingDiscs()
{
	std::vector<Disc*> discs;

	for (Material* mat : materials_)
	{
		if (mat != nullptr)
		{
			std::string format = mat->getFormat();
			if (toLower(format) == "bluray" || toLower(format) == "singledvd" || toLower(format) == "doubledvd")
			{
				discs.push_back((Disc*)mat);
			}
		}
	}
	for (Material* mat : projectAssociatedMaterials)
	{
		if (mat != nullptr)
		{
			std::string format = mat->getFormat();
			if (toLower(format) == "bluray" || toLower(format) == "singledvd" || toLower(format) == "doubledvd")
			{
				discs.push_back((Disc*)mat);
			}
		}
	}

	logger->debug("exisiting discs = ");
	for (Disc* d : discs)
	{
		logger->debug(d->getId() + " : " + d->getFilmTitle());
	}

	return discs;
}

void ProjectManager::addMaterial(Material * material)
{
	logger->debug("adding material : " + material->getFilmTitle());
	materials_.push_back(material);
}

void ProjectManager::addProject(Project* project, bool nowPlaying)
{
	logger->debug("adding project : " + project->getTitle());
	projects_.insert(std::pair<Project*, bool>(project, nowPlaying));
}

std::vector<Material*> ProjectManager::getMaterials()
{
	return materials_;
}

void ProjectManager::addMaterialToProject(Project* project, std::vector<Material*> materials)
{
	logger->debug("adding material to project");
	for (Material* material : materials)
	{
		for (int i = 0; i < materials_.size(); i++)
		{
			if (material->getId() == materials_[i]->getId() && material->getFilmTitle() == materials_[i]->getFilmTitle() && material->getFormat() == materials_[i]->getFormat())
			{
				projectAssociatedMaterials.push_back(material);
				materials_.erase(materials_.begin() + materials_[i]->getId());
			}
			else
			{
				projectAssociatedMaterials.push_back(material);
			}

		}
	}
	
	project->setMaterials(materials);
	logger->info("added materials to " + project->getTitle());
}

void ProjectManager::setMaterialsList(std::vector<Material*> materials)
{
	materials_ = materials;
}

void ProjectManager::setAssociatedMaterialsList(std::vector<Material*> materials)
{
	projectAssociatedMaterials = materials;
}

std::vector<Project*> ProjectManager::getProjects()
{
	std::vector<Project*> allProjects;
	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		allProjects.push_back(it->first);
	}

	return allProjects;
}

std::vector<Material*> ProjectManager::getProjectAssociatedMaterials()
{
	return projectAssociatedMaterials;
}

std::pair<std::vector<Material*>, std::vector<Material*>> ProjectManager::getAllMaterials()
{
	std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials;
	allMaterials.first = materials_;
	allMaterials.second = projectAssociatedMaterials;

	return allMaterials;
}

std::map<Project*, bool> ProjectManager::getProjectMap()
{
	return projects_;
}

int ProjectManager::getMaterialCount()
{
	return materialCount;
}

void ProjectManager::incrementMaterialCount()
{
	materialCount++;
}

void ProjectManager::setMaterialCounter(const int count)
{
	materialCount = count;
}


std::vector<Project*> ProjectManager::materialFindProject(Material* lmaterial)
{
	std::vector<Project*> projects;
	Material* material = lmaterial;
	if (material != nullptr)
	{
		std::map<Project*, bool>::iterator it;

		for (it = projects_.begin(); it != projects_.end(); ++it)
		{
			if (!it->first->getMaterials().empty())
			{
				for (Material* mat : it->first->getMaterials())
				{
					if (mat->getId() == material->getId() && mat->getFilmTitle() == material->getFilmTitle() && mat->getFormat() == material->getFormat())
					{
						projects.push_back(it->first);
					}
				}
			}
		}
	}
	return projects;
}

void ProjectManager::deleteProject(Project* project)
{
	logger->info("deleting project : " + project->getTitle());
	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		if (project->getTitle() == it->first->getTitle() && project->getSummary() == it->first->getSummary() && project->getLanguage() == it->first->getLanguage() && project->getReleaseDate() == it->first->getReleaseDate())
		{
			if (it->first->getMaterials().size() > 0)
			{
				for (Material* material : it->first->getMaterials())
				{
					int count = 0;
					for (int i = 0; i < projectAssociatedMaterials.size(); i++)
					{
						if (projectAssociatedMaterials[i]->getId() == material->getId() && projectAssociatedMaterials[i]->getFilmTitle() == material->getFilmTitle() && projectAssociatedMaterials[i]->getFormat() == material->getFormat())
						{
							delete projectAssociatedMaterials[i];
							projectAssociatedMaterials.erase(projectAssociatedMaterials.begin() + count);
							i--;
						}

					}
				}
			}
			delete it->first;
			projects_.erase(it);
			break;
		}
	}
}

void ProjectManager::deleteMaterial(std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials, int id)
{
	logger->info("deleting material id : " + std::to_string(id));
	if (id < allMaterials.first.size())
	{
		delete allMaterials.first[id];
		allMaterials.first.erase(allMaterials.first.begin() + id);
		setMaterialsList(allMaterials.first);
	}
	else
	{

		std::map<Project*, bool> projects = getProjectMap();
		std::map<Project*, bool>::iterator it;
		for (it = projects.begin(); it != projects.end(); ++it)
		{
			int projMaterialId = 0;
			for (Material* localMaterial : it->first->getMaterials())
			{
				if (localMaterial->getId() == allMaterials.second[id - (allMaterials.first.size())]->getId() && localMaterial->getFilmTitle() == allMaterials.second[id - (allMaterials.first.size())]->getFilmTitle() && localMaterial->getFormat() == allMaterials.second[id - (allMaterials.first.size())]->getFormat())
				{
					delete localMaterial;
					std::vector<Material*> projMaterial = it->first->getMaterials();
					projMaterial.erase(projMaterial.begin() + projMaterialId);
					it->first->setMaterials(projMaterial);
				}
				projMaterialId++;
			}
		}

		allMaterials.second.erase(allMaterials.second.begin() + (id - (allMaterials.first.size())));
		setAssociatedMaterialsList(allMaterials.second);
	}
}


const bool ProjectManager::isReleased(Project * project)
{
	time_t rawTime;
	time(&rawTime);
	
	return project->getReleaseDate() <= rawTime;
}

/*
  * Converts the input string to all lower case characters
  */
 std::string ProjectManager::toLower(std::string & input)
 {
	 for (int i = 0; i < input.length(); i++)
	 {
		 input[i] = tolower(input[i]);
	 }
	return input;
}

 Material* ProjectManager::getMaterialFromId(int id)
 {
	 for (Material* material : getMaterials())
	 {
		 if (material != nullptr)
		 {
			 if (material->getId() == id)
			 {
				 return material;
			 }
		 }
	 }
	 return nullptr;
 }

 std::vector<Project*> ProjectManager::findProjects(std::map<int, std::string> searchCritera)
 {
	 std::vector<Project*> projects;

	 std::map<int, std::string>::iterator it;

	 for (Project* project : getProjects())
	 {
		 bool addProj = true;
		 for (it = searchCritera.begin(); it != searchCritera.end(); ++it)
		 {
			 if (it->first == 1)			//Title
			 {
				 if (toLower(it->second) != toLower(project->getTitle()))
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 2)		//Summary
			 {
				 if (toLower(it->second) != toLower(project->getSummary()))
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 3)		//Genre
			 {
				 if (toLower(it->second) != toLower(project->getGenre()))
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 4)		//ReleaseDate
			 {
				 if (toLower(it->second) != toLower(std::to_string(project->getReleaseDate())));
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 5)		//Filming location
			 {
				 if (std::find(project->getFilmingLocations().begin(), project->getFilmingLocations().end(), it->second) == project->getFilmingLocations().end())
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 6)		//Keyword
			 {
				 if (std::find(project->getKeywords().begin(), project->getKeywords().end(), it->second) == project->getKeywords().end())
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 7)		//Crew
			 {
				 if (std::find(project->getCrew().begin(), project->getCrew().end(), it->second) == project->getCrew().end())
				 {
					 addProj = false;
					 break;
				 }
			 }
			 else if (it->first == 8)		//Material Format
			 {
				 addProj = false;
				 for (Material* material : project->getMaterials())
				 {
					 if (toLower(it->second) == material->getFormat())
					 {
						 addProj = true;
						 break;
					 }
				 }
			 }
		 }
		 if (addProj)
		 {
			 projects.push_back(project);
		 }
	 }

	 return projects;
 }

#endif // !PROJECTMANAGER_CPP