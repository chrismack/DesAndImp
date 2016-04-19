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

Material * ProjectManager::getAssociatedMaterial(const std::string & message)
{
	//projectViewer.displayMessage(message);
	Material* material = nullptr;
	std::string input;
	std::vector<int> validIndex;
	for (Material* mat : projectAssociatedMaterials)
	{
		if (mat != nullptr)
		{
			//projectViewer.displayMessage(std::to_string(mat->getId()) + " : " + mat->getFilmTitle() + " : " + mat->getFormat());
			validIndex.push_back(mat->getId());
		}
	}

	if (!materials_.empty())
	{
		bool valid = false;
		do
		{
			//projectViewer.displayMessage("Please enter material index");
			try
			{
				input = getUserInput();
				if (input != "" && input.find_first_of(" ") == std::string::npos)
				{
					int id = std::stoi(input);
	
					for (int i : validIndex)
					{
						if (id == i)
						{
							valid = true;
						}
					}

					if (valid)
					{
						
						for (Material* localMaterial : projectAssociatedMaterials)
						{
							if (localMaterial != nullptr)
							{
								if (localMaterial->getId() == id)
								{
									material = localMaterial;
								}
							}
						}
					}
					else
					{
						valid = false;
					}
				}
			}
			catch (std::invalid_argument ia)
			{
				valid = false;
			}

		} while (!valid);
	}
	else
	{
		//projectViewer.displayMessage("No materials exist");
	}
	return material;
}

Project * ProjectManager::getProjectFromUser(const std::string & message)
{
	//projectViewer.displayMessage(message);

	Project* project = nullptr;
	std::vector<Project*> tmpProjects;
	if (!projects_.empty())
	{
		//projectViewer.displayMessage("INDEX : TITLE : SUMMARY : GENRE");

		int index = 0;
		std::map<Project*, bool>::iterator it;
		for (it = projects_.begin(); it != projects_.end(); ++it)
		{
			//projectViewer.displayMessage(std::to_string(index) + " : " + it->first->getTitle() + " : " + it->first->getSummary() + " : " + it->first->getGenre());
			index++;
			tmpProjects.push_back(it->first);
		}
		
		int selectedIndex;
		do
		{
			selectedIndex = messageReturnInt("Enter Project index");
			if (selectedIndex > -1 && selectedIndex < projects_.size())  // if valid selection
			{
				return tmpProjects[selectedIndex];
			}
		} while (selectedIndex > -1 && selectedIndex < projects_.size());
	}
	else		// No projects are loaded to memory
	{
		//projectViewer.displayMessage("Their are no loaded projects! Import or create one");
		return nullptr;
	}

	return project;
}

//void ProjectManager::linkMedia()
//{
//	//projectViewer.displayMessage("Please select a project and material to link");
//	if (!materials_.empty() && !projects_.empty())		
//	{
//		Project* project = getProjectFromUser("Please select a project");
//		if (project != nullptr)
//		{
//			if (isReleased(project))
//			{
//				std::vector<Material*> materials =getMaterialsFromUser("Please select materials to link");
//				if (!materials.empty())
//				{
//					project->setMaterials(materials);
//
//					int materialIndex = -1;
//					for (Material* material : materials_)
//					{
//						if (material != nullptr)
//						{
//							materialIndex++;
//							for (Material* localMaterial : materials)
//							{
//								if (localMaterial != nullptr)
//								{
//									if (material->getId() == localMaterial->getId())
//									{
//										projectAssociatedMaterials.push_back(localMaterial);
//										materials_.erase(materials_.begin() + materialIndex);
//									}
//								}
//							}
//						}
//						if (materialIndex + 1 >= materials_.size())
//						{
//							break;
//						}
//					}
//				}
//			}
//			else
//			{
//				//projectViewer.displayMessage("Project has not been released. Materials cannot be added");
//			}
//		}
//	}
//	else		// Missing either a project or material
//	{
//		//projectViewer.displayMessage("You need to have atleast one project and one material to make a link");
//	}
//}

void ProjectManager::clearView()
{
	//projectViewer.clearScreen();
}

void ProjectManager::viewProjects()
{
	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		//projectViewer.displayMessage(it->first->getTitle());
	}
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



void ProjectManager::viewMaterials()
{
	for (Material* material : materials_)
	{
		if (material != nullptr);
			//projectViewer.displayMessage(std::to_string(material->getId()) + " : " + material->getFilmTitle());
	}

	for (Material* material : projectAssociatedMaterials)
	{
		if (material != nullptr);
			//projectViewer.displayMessage(std::to_string(material->getId()) + " : " + material->getFilmTitle() + "Associated with project");
	}
}

void ProjectManager::createLink()
{
		//projectViewer.displayMessage("Please select a project and material to link");
		//linkMedia();
}

std::vector<Material*> ProjectManager::projectFindMaterial(Project* project)
{
	std::vector<Material*> materials;
	if (!project->getMaterials().empty())
	{
		for (Material* material : project->getMaterials())
		{
			//projectViewer.displayMessage("TITLE : " + material->getFilmTitle() + "   ", false);
			//projectViewer.displayMessage("FORMAT : " + material->getFormat() + "   ", false);
			//projectViewer.displayMessage("LANGIAGE : " + material->getLanguage() + "   ", false);
			//projectViewer.displayMessage(" ");

			if (yesNoBool("Would you like to view the full material?"))
			{
				//projectViewer.viewFullMaterial(material);
			}
				 
		}
	}
	else
	{
		//projectViewer.displayMessage("Project doesn't have any associated materials");
	}
	return materials;
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

void ProjectManager::deleteMaterial()
{
	std::vector<Material*> allMaterials;

	//projectViewer.displayMessage("Select a material to delete");
	//projectViewer.displayMessage("INDEX : TITLE : FORMAT");

	int split;

	for (Material* material : materials_)
	{
		if (material != nullptr)
		{
			//projectViewer.displayMessage(std::to_string(allMaterials.size()) + " : " + material->getFilmTitle() + " : " + material->getFormat());
			allMaterials.push_back(material);
		}
	}

	split = allMaterials.size() - 1;

	for (Material* material : projectAssociatedMaterials)
	{
		if (material != nullptr)
		{
			//projectViewer.displayMessage(std::to_string(allMaterials.size()) + " : " + material->getFilmTitle() + " : " + material->getFormat());
			allMaterials.push_back(material);
		}
	}

	int id = messageReturnInt("Select a material index");
	if (id > -1 && id < allMaterials.size())
	{
		if (id <= split) // in main material
		{
				delete materials_[id];
				materials_.erase(materials_.begin() + id);
		}
		else	//Associated material
		{
			delete projectAssociatedMaterials[id - (split + 1)];
			projectAssociatedMaterials.erase(projectAssociatedMaterials.begin() + (id - (split + 1)));

			std::map<Project*, bool>::iterator it;
			for (it = projects_.begin(); it != projects_.end(); ++it)
			{
				int projMaterialId = 0;
				for (Material* localMaterial : it->first->getMaterials())
				{
					if (localMaterial->getId() == allMaterials[id - (split + 1)]->getId() && localMaterial->getFilmTitle() == allMaterials[id - (split + 1)]->getFilmTitle() && localMaterial->getFormat() == allMaterials[id - (split + 1)]->getFormat())
					{
						delete localMaterial;
						it->first->getMaterials().erase(it->first->getMaterials().begin() + projMaterialId);
					}
					projMaterialId++;
				}
			}
		}
	}
}

/*
 * Return text user has entered
 */
std::string ProjectManager::getUserInput()
{
	std::string userInput = "";
	std::getline(std::cin, userInput);
	//std::cin >> userInput;
	return userInput;
}

/*
* display user with a message and return a non null input
*/
const std::string ProjectManager::messageReturnInput(const std::string & message)
{
	//projectViewer.displayMessage(message);
	//projectViewer.displayMessage("Please enter your input");

	std::string input = getUserInput();
	while ((input == "") && (input.find_first_of(" ") == std::string::npos))  // Ensure user input is not null or only spaces
	{
		//projectViewer.displayMessage("Your input cannot be nothing. Please try again");
		input = getUserInput();
	}

	return input;
}

/*
 * Display message on screen and get multiple user input and return in a vector
 */
const std::vector<std::string> ProjectManager::messageReturnUserVector(const std::string & message, const bool canBeNull /*false*/)
{
	//projectViewer.displayMessage(message);
	if (!canBeNull);
		//projectViewer.displayMessage("Atleast one value needs to be entered");
	//projectViewer.displayMessage("enter : exit---loop to finish");
	
	std::vector<std::string> userData = {};
	std::string input = "";
	
	while ((toLower(input) != "exit---loop") || (userData.empty() && !canBeNull))
	{
		//projectViewer.displayMessage("Please enter a value. Or exit---loop to finish");
		input = getUserInput();
		if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
		{
			userData.push_back(input);
		}
	}

	return userData;
}

/*
 * Display a message on screen and get user entered integers and return a vector of ints
 */
const std::vector<int> ProjectManager::messageReturnUserVectorInt(const std::string & message)
{

	//projectViewer.displayMessage(message);

	//projectViewer.displayMessage("Atleast one value needs to be entered");
	//projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<int> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		//projectViewer.displayMessage("Please enter a value. Or exit---loop to finish");
		//projectViewer.displayMessage("This is data set : " + userData.size() + 1);
		input = getUserInput();
		if (toLower(input) != "exit---loop")
		{
			try
			{
				userData.push_back(std::stoi(input));
			}
			catch (std::invalid_argument ia)
			{
				//projectViewer.displayMessage("Could not convert " + input + " to an integer");
			}
		}
	}


	return userData;
}

/*
 * Return a pair of ints 
 */
const std::pair<int, int> ProjectManager::messageGetAspect(const std::string & message)
{
	//projectViewer.displayMessage(message);

	std::pair<int, int> aspectratio;
	bool invalid = true;
	while (invalid)
	{
		try
		{
			aspectratio.first = std::stoi(messageReturnInput("Please enter width"));
			aspectratio.second = std::stoi(messageReturnInput("Please enter height"));
			invalid = false;
		}
		catch (std::invalid_argument ia)
		{
			//projectViewer.displayMessage("Invalid input entered! please try again (must be an integer)");
		}
	}

	return aspectratio;
}

/*
 * Displays a message and converts input to an integer 
 */
const int ProjectManager::messageReturnInt(const std::string & message)
{
	//projectViewer.displayMessage(message);
	bool invalid = true;

	int i;

	while (invalid)
	{
		try
		{
			i = std::stoi(messageReturnInput("Enter Integer"));
			invalid = false;
		}
		catch (std::invalid_argument)
		{
			//projectViewer.displayMessage("Not a valid input plese try again");
		}
	}
	return i;
}


/*
 * Gets a user input and converts to a float
 */
const float ProjectManager::messageReturnFloat(const std::string & message)
{
	//projectViewer.displayMessage(message);
	bool invalid = true;

	float f;

	while (invalid)
	{
		try
		{
			f = std::stof(messageReturnInput("Enter decimal"));
			invalid = false;
		}
		catch (std::invalid_argument)
		{
			//projectViewer.displayMessage("Not a valid input plese try again");
		}
	}
	return f;
}


const bool ProjectManager::yesNoBool(const std::string & message)
{
	//projectViewer.displayMessage(message);

	std::string input = "";
	while (toLower(input) != "yes" && toLower(input) != "no")
	{
		//projectViewer.displayMessage("please enter a valid option. Yes or No");
		input = getUserInput();
		if (toLower(input) == "yes" || toLower(input) == "no")
		{
			return input == "yes" ? true : false;
		}
	}

	return false;
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
