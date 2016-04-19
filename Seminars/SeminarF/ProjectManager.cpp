#include "stdafx.h"
#include "ProjectManager.h"

#include <iostream>
#include <fstream>
#include <time.h>

#include "Logger.h"

#include "MaterialFactory.h"
#include "CSVHandler.h"

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
	std::fstream saveFile(defaultSavePath);
	
	if (! fileExists(defaultSavePath) || saveFile.peek() == std::fstream::traits_type::eof())	// File doesn't exists or is empty
	{
		saveFile.open(defaultSavePath, std::fstream::in | std::fstream::out | std::fstream::app);		// Create file if it doesn't exist
		saveFile.close();
	
		// File doesn't exist may want to import from and existing file
		return false;
	}
	else
	{
		importCSV(defaultSavePath);
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

			logger->debug("Finished xml import");
			return true;
		}
		else
		{
			return false;
		}

		// If time is available should look into JSON support

	}
	return false;
}

void ProjectManager::save()
{
	std::ofstream saveFile(defaultSavePath);
	saveFile.open(defaultSavePath, std::ofstream::out);
	MaterialFactory* mf = new MaterialFactory();
	CSVHandler csvHandler(defaultSavePath, mf);

	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		csvHandler.writeToFile(it->first, it->second);
	}

	for (Material* material : materials_)
	{
		if (material != nullptr)
			csvHandler.writeToFile(material);
	}

	saveFile.close();
	delete mf;
}

/*
 * Import projects and materials that have been stored in a CSV file
 * Imports lines to materials_ and projects_
 */
void ProjectManager::importCSV(const std::string &CSV)
{
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

	return discs;
}

void ProjectManager::addMaterial(Material * material)
{
	materials_.push_back(material);
}

void ProjectManager::addProject(Project* project, bool nowPlaying)
{
	projects_.insert(std::pair<Project*, bool>(project, nowPlaying));
}

std::vector<Material*> ProjectManager::getMaterials()
{
	return materials_;
}

void ProjectManager::addMaterialToProject(Project* project, std::vector<Material*> materials)
{
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

void ProjectManager::deleteProject()
{
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
