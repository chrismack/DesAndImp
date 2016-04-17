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
void ProjectManager::setupSaveFile()
{
	std::fstream saveFile(defaultSavePath);
	
	if (! fileExists(defaultSavePath) || saveFile.peek() == std::fstream::traits_type::eof())	// File doesn't exists or is empty
	{
		saveFile.open(defaultSavePath, std::fstream::in | std::fstream::out | std::fstream::app);		// Create file if it doesn't exist
		saveFile.close();
	
		// File doesn't exist may want to import from and existing file
		projectViewer.displayMessage("You do not have any existing projects or materials"		);
		projectViewer.displayMessage("Would you like to import from an existing file? Yes or No");
		
		std::string userImport = toLower(getUserInput());
		if (userImport == "yes" || userImport == "y")
		{
			projectViewer.displayMessage("What file would you like to import?");
			importFile(getUserInput());
		}
	}
	else
	{
		importCSV(defaultSavePath);
	}
}

/*
 * Try to import a file from a specified path
 *
 * return if the file has been imported
 */
bool ProjectManager::importFile(std::string path)
{
	projectViewer.displayMessage("Please enter a path to the file you would like to import : ");
	logger->info("Importing " + path);
	if (fileExists(path))
	{
		logger->debug("file exists");
		std::string extension = path.substr(path.find_last_of('.') + 1);	// Get the extension of the file that is being imported
		if (extension == "csv")
		{
			logger->debug("Starting csv import");
			importCSV(path, true);
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
void ProjectManager::importCSV(const std::string &CSV, const bool checkNowPlaying /* false*/)
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
		if (checkNowPlaying)
		{
			projectViewer.displayMessage("Is this project now playing?");
			projectViewer.displayMessage("Title: " + it->first->getTitle() + " Genre: " + it->first->getGenre() + " Summary: " + it->first->getSummary());
			std::string tmpNowPlayingStr = it->second == true ? "true" : "false";
			projectViewer.displayMessage("Currently saved as : " + tmpNowPlayingStr);
			std::string input = "";
			while (toLower(input) != "yes" && toLower(input) != "no")
			{
				projectViewer.displayMessage("please enter a valid option. Yes or No");
				input = getUserInput();
				if (toLower(input) == "yes" || toLower(input) == "no")
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
					projects_.insert(std::pair<Project*, bool>(it->first, toLower(input) == "yes" ? true : false));
				}
			}
		}
		else
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

/*
 * Creates project class from user inputs
 * returns the created project
 */
Project * ProjectManager::createProject()
{
	Project* project = new Project();
	// title, summary, genre, releasedate, filminglocation, language, keywords, ticketSale
	project->setTitle(messageReturnInput("Set Title"));
	project->setSummary(messageReturnInput("Set Summary"));
	project->setGenre(messageReturnInput("Set Genre"));
	project->setReleaseDate(messageGetDate("Set release date"));
	project->setFilmingLocations(messageReturnUserVector("Set Filming Locations"));
	project->setLanguage(messageReturnInput("Set Language"));
	project->setKeywords(messageReturnUserVector("Set keywords"));

	return project;
}

/*
 * Creates a Materuak from user entered inputs 
 * Returns the created material class
 */
Material * ProjectManager::createMaterial(const bool mustBeDisc /*false*/)
{
	Material* material = nullptr;

	std::string type;

	bool invalid = false;
	do
	{
		if (mustBeDisc)
		{
			projectViewer.displayMessage("Please enter valid type; BluRay, SingleDVD, DoubleDVD");
		}
		else
		{
			projectViewer.displayMessage("Please enter valid type; BluRay, SingleDVD, DoubleDVD, Combo, VHS");
		}
		type = messageReturnInput("Set Type");
		type = toLower(type);

		invalid = false;
		if (type == "bluray")
		{
			material = new BlueRay();
			setBaseMaterialAttributes(material, "BluRay");
			
			BlueRay *blu = dynamic_cast<BlueRay*> (material);
			blu->setContent(messageReturnUserVector("Set content"));
			blu->setBonusFeatures(messageReturnUserVector("Set bonus features"));
			blu->setAudioTracks(messageReturnUserVector("Set audio tacks"));
			blu->setLanguageTracks(messageReturnUserVector("Set language tracks"));
			blu->setSubtitleTracks(messageReturnUserVector("Set subtitles tracks"));

			setMaterialPackage(blu);
		}
		else if (type == "singledvd")
		{
			material = new SingleDVD();
			setBaseMaterialAttributes(material, "SingleDVD");

			SingleDVD *dvd = dynamic_cast<SingleDVD*> (material);
			dvd->setContent(messageReturnUserVector("Set content"));
			dvd->setBonusFeatures(messageReturnUserVector("Set bonus features"));
			dvd->setAudioTracks(messageReturnUserVector("Set audio tacks"));
			dvd->setLanguageTracks(messageReturnUserVector("Set language tracks"));
			dvd->setSubtitleTracks(messageReturnUserVector("Set subtitles tracks"));

			setMaterialPackage(dvd);
		}
		else if (type == "doubledvd")
		{
			material = new DoubleDVD();
			setBaseMaterialAttributes(material, "DoubleDVD");

			DoubleDVD *dvd = dynamic_cast<DoubleDVD*> (material);
			dvd->setContent(setVectorSideMap("Set content"));
			dvd->setBonusFeatures(setVectorSideMap("Set bonus features"));
			dvd->setAudioTracks(setVectorSideMap("Set audio tacks"));
			dvd->setLanguageTracks(setVectorSideMap("Set language tracks"));
			dvd->setSubtitleTracks(setVectorSideMap("Set subtitles tracks"));
		}
		else if (type == "combo" && !mustBeDisc)
		{
			material = new ComboBox();
			setBaseMaterialAttributes(material, "Combo");

			ComboBox *combo = dynamic_cast<ComboBox*> (material);
			combo->setContent(getDiscMaterialsFromUser("Set Materials"));

			setMaterialPackage(combo);			// Set package spec
		}
		else if (type == "vhs" && !mustBeDisc)
		{
			material = new VHS();
			setBaseMaterialAttributes(material, "VHS");

			VHS *vhs = dynamic_cast<VHS*> (material);
			vhs->setContent(messageReturnUserVector("Set content"));
			vhs->setlanguageTrack(messageReturnInput("Set language track"));
			vhs->setAudioTrack(messageReturnInput("Set audio track"));

			setMaterialPackage(vhs);			// Set package spec
		}
		else
		{
			invalid = true;
		}
	} while (invalid);
	
	return material;
}

void ProjectManager::setBaseMaterialAttributes(Material * material, const std::string& type)
{
	materialCount += 1;
	material->setID(materialCount);
	material->setFilmTitle(messageReturnInput("Set Title"));
	material->setFormat(type);
	material->setAudioFormat(messageReturnInput("Set Audio Format"));
	material->setRunTime(messageReturnInt("Set Runtime"));
	material->setLanguage(messageReturnInput("Set Language"));
	material->setRetailPrice(messageReturnFloat("Set Retail Price"));
	material->setSubtitles(messageReturnInput("Set Subtitles"));
	material->setAspectRation(messageGetAspect("Set Aspect Ratio"));
}

std::map<int, std::vector<std::string>> ProjectManager::setVectorSideMap(const std::string & message)
{
	projectViewer.displayMessage(message);
	std::map<int, std::vector<std::string>> discAttributeMap;

	discAttributeMap.insert(std::pair<int, std::vector<std::string>>(0, messageReturnUserVector("Set side one data", true)));
	discAttributeMap.insert(std::pair<int, std::vector<std::string>>(1, messageReturnUserVector("Set side two data", true)));

	return discAttributeMap;
}

void ProjectManager::setMaterialPackage(IPackagable * material)
{
	material->setPackageType(messageReturnInput("Set package type"));
	material->setPackageDimensions(std::tuple<int, int, int>(messageReturnInt("Set package width"), messageReturnInt("Set package height"), messageReturnInt("Set package depth")));
}

std::vector<Disc*> ProjectManager::getDiscMaterialsFromUser(const std::string & message)
{
	projectViewer.displayMessage(message);

	projectViewer.displayMessage("Atleast one value needs to be entered");
	projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<int> validID;
	std::vector<int> selectedId;
	std::vector<Disc*> userData = {};
	std::string input = "";


	projectViewer.displayMessage("ID :	TITLE : FORMAT");
	for (Material* mat: materials_)
	{
		if (mat != nullptr)
		{
			std::string format = mat->getFormat();
			if (toLower(format) == "bluray" || toLower(format) == "singledvd" || toLower(format) == "doubledvd")
			{
				projectViewer.displayMessage(std::to_string(mat->getId()) + " : " + mat->getFilmTitle() + " : " + mat->getFormat());
				validID.push_back(mat->getId());
			}
		}
	}

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		if (yesNoBool("Would you like to create a material (must be disc)? enter no to add existing material"))
		{
			Disc* discMaterial = (Disc*)createMaterial(true);
			userData.push_back(discMaterial);
			selectedId.push_back(discMaterial->getId());
		}
		else
		{
			projectViewer.displayMessage("Please enter material index. Or exit---loop to finish");
			try
			{
				input = getUserInput();
				if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
				{
					int id = std::stoi(input);
					if (std::find(validID.begin(), validID.end(), id) != validID.end())		//Input is a valid ID to select from
					{
						if (std::find(selectedId.begin(), selectedId.end(), id) != selectedId.end())
						{
							if (yesNoBool("you have already added this material do you want to add it again?"))
							{
								userData.push_back((Disc*)materials_[id]);
								selectedId.push_back(id);
							}
						}
						else
						{
							userData.push_back((Disc*)materials_[id]);
							selectedId.push_back(id);
						}
					}
				}
			}
			catch(std::invalid_argument ia)
			{
				projectViewer.displayMessage("Please enter a valid id (integer)");
			}
		}
	}

	return userData;
}

std::vector<Material*> ProjectManager::getMaterialsFromUser(const std::string & message, const bool oneExisting /* false */)
{
	projectViewer.displayMessage(message);

	projectViewer.displayMessage("Atleast one value needs to be entered");
	projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<int> selectedId;
	std::vector<Material*> userData = {};
	std::string input = "";

	projectViewer.displayMessage("ID :	TITLE : FORMAT");
	for (Material* mat : materials_)
	{
		if(mat != nullptr)
		{
			projectViewer.displayMessage(std::to_string(mat->getId()) + " : " + mat->getFilmTitle() + " : " + mat->getFormat());
		}
	}

	if (!oneExisting)
	{
		while ((toLower(input) != "exit---loop") || userData.empty())
		{
			if (yesNoBool("Would you like to create a material? enter no to add existing material"))
			{
				Material* newMaterial = createMaterial();
				userData.push_back(newMaterial);
				selectedId.push_back(newMaterial->getId());
			}
			else
			{
				projectViewer.displayMessage("Please enter material index. Or exit---loop to finish");
				try
				{
					input = getUserInput();
					if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
					{
						int id = std::stoi(input);
						if (std::find(selectedId.begin(), selectedId.end(), id) != selectedId.end())
						{
							if (yesNoBool("you have already added this material do you want to add it again?"))
							{
								userData.push_back(materials_[id]);
								selectedId.push_back(id);
							}
						}
						else
						{
							for (Material* material : materials_)
							{
								if(material != nullptr)
								{
									if (material->getId() == id)
									{
										userData.push_back(material);
										selectedId.push_back(id);
									}
								}
							}
						}
					}
				}
				catch (std::invalid_argument ia)
				{
					projectViewer.displayMessage("Please enter a valid id (integer)");
				}
			}
		}
	}
	else			// Only select one existing material
	{
		if (!materials_.empty())
		{
			bool valid = true;
			do
			{
				projectViewer.displayMessage("Please enter material index");
				try
				{
					input = getUserInput();
					if (input != "" && input.find_first_of(" ") == std::string::npos)
					{
						int id = std::stoi(input);

						for (Material* material : materials_)
						{
							if (material != nullptr)
							{
								if (material->getId() == id)
								{
									userData.push_back(material);
									selectedId.push_back(id);
								}
							}
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
			projectViewer.displayMessage("No materials exist");
		}
	}
	return userData;
}

Material * ProjectManager::getAssociatedMaterial(const std::string & message)
{
	projectViewer.displayMessage(message);
	Material* material = nullptr;
	std::string input;
	std::vector<int> validIndex;
	for (Material* mat : projectAssociatedMaterials)
	{
		if (mat != nullptr)
		{
			projectViewer.displayMessage(std::to_string(mat->getId()) + " : " + mat->getFilmTitle() + " : " + mat->getFormat());
			validIndex.push_back(mat->getId());
		}
	}

	if (!materials_.empty())
	{
		bool valid = false;
		do
		{
			projectViewer.displayMessage("Please enter material index");
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
		projectViewer.displayMessage("No materials exist");
	}
	return material;
}

Project * ProjectManager::getProjectFromUser(const std::string & message)
{
	projectViewer.displayMessage(message);

	Project* project = nullptr;
	std::vector<Project*> tmpProjects;
	if (!projects_.empty())
	{
		projectViewer.displayMessage("INDEX : TITLE : SUMMARY : GENRE");

		int index = 0;
		std::map<Project*, bool>::iterator it;
		for (it = projects_.begin(); it != projects_.end(); ++it)
		{
			projectViewer.displayMessage(std::to_string(index) + " : " + it->first->getTitle() + " : " + it->first->getSummary() + " : " + it->first->getGenre());
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
		projectViewer.displayMessage("Their are no loaded projects! Import or create one");
		return nullptr;
	}

	return project;
}

void ProjectManager::linkMedia()
{
	projectViewer.displayMessage("Please select a project and material to link");
	if (!materials_.empty() && !projects_.empty())		
	{
		Project* project = getProjectFromUser("Please select a project");
		if (project != nullptr)
		{
			if (isReleased(project))
			{
				std::vector<Material*> materials = getMaterialsFromUser("Please select materials to link");
				if (!materials.empty())
				{
					project->setMaterials(materials);

					int materialIndex = -1;
					for (Material* material : materials_)
					{
						if (material != nullptr)
						{
							materialIndex++;
							for (Material* localMaterial : materials)
							{
								if (localMaterial != nullptr)
								{
									if (material->getId() == localMaterial->getId())
									{
										projectAssociatedMaterials.push_back(localMaterial);
										materials_[materialIndex] = nullptr;
									}
								}
							}
						}
					}
				}
			}
			else
			{
				projectViewer.displayMessage("Project has not been released. Materials cannot be added");
			}
		}
	}
	else		// Missing either a project or material
	{
		projectViewer.displayMessage("You need to have atleast one project and one material to make a link");
	}
}

void ProjectManager::updateDisplay(const std::string & message)
{
	projectViewer.displayMessage(message);
}

void ProjectManager::displayViewOptions()
{
	projectViewer.displayViewOptions();
}

void ProjectManager::displayCreateMenu()
{
	projectViewer.displayCreateMenu();
}

void ProjectManager::displaySearchMenu()
{
	projectViewer.displaySearchMenu();
}

void ProjectManager::displayMenuOptions()
{
	projectViewer.displayMenuOptions();
}

void ProjectManager::clearView()
{
	projectViewer.clearScreen();
}

void ProjectManager::viewProjects()
{
	std::map<Project*, bool>::iterator it;
	for (it = projects_.begin(); it != projects_.end(); ++it)
	{
		projectViewer.displayMessage(it->first->getTitle());
	}
}

void ProjectManager::viewMaterials()
{
	for (Material* material : materials_)
	{
		if (material != nullptr)
			projectViewer.displayMessage(std::to_string(material->getId()) + " : " + material->getFilmTitle());
	}

	for (Material* material : projectAssociatedMaterials)
	{
		if (material != nullptr)
			projectViewer.displayMessage(std::to_string(material->getId()) + " : " + material->getFilmTitle() + "Associated with project");
	}
}

void ProjectManager::createAndAddProject()
{
	Project* project = createProject();
	bool nowPlaying = yesNoBool("Is the project now playing?");
	if (isReleased(project))
	{
		if (yesNoBool("Would you like to link materials to the project?"))
		{
			project->setMaterials(getMaterialsFromUser("Add material to project"));
		}
	}
	projects_.insert(std::pair<Project*, bool>(project, nowPlaying));
	
}

void ProjectManager::createAndAddMaterial()
{
	materials_.push_back(createMaterial());
}

void ProjectManager::createLink()
{
		projectViewer.displayMessage("Please select a project and material to link");
		linkMedia();
}

void ProjectManager::projectFindMaterial()
{
	Project* project = getProjectFromUser("Select project to view associated materials");
	if (!project->getMaterials().empty())
	{
		for (Material* material : project->getMaterials())
		{
			projectViewer.displayMessage("TITLE : " + material->getFilmTitle() + "   ", false);
			projectViewer.displayMessage("FORMAT : " + material->getFormat() + "   ", false);
			projectViewer.displayMessage("LANGIAGE : " + material->getLanguage() + "   ", false);
			projectViewer.displayMessage(" ");

			if (yesNoBool("Would you like to view the full material?"))
			{
				projectViewer.viewFullMaterial(material);
			}
				 
		}
	}
	else
	{
		projectViewer.displayMessage("Project doesn't have any associated materials");
	}
}

void ProjectManager::materialFindProject()
{
	Material* material = getAssociatedMaterial("Select a material to view linked project");
	if (material != nullptr)
	{
		std::map<Project*, bool>::iterator it;

		std::vector<Project*> projects;

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

		for (Project* proj : projects)
		{
			projectViewer.displayMessage("TILTE: " + proj->getTitle() + " SUMMARY:" + proj->getSummary());

			if (yesNoBool("Would you like to see the whole project?"))
			{
				projectViewer.viewFullProject(proj);
			}
		}
	}
	else
	{
		projectViewer.displayMessage("Couldn't find associated project");
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
 * Heavily based on:
 * http://www.cplusplus.com/reference/ctime/mktime/
 */
const long ProjectManager::messageGetDate(const std::string & message)
{

	projectViewer.displayMessage(message);

	time_t rawTime;
	struct tm timeInfo;
	int year, month, day;
	long timestamp = -1;

	bool validInput = true;

	while (timestamp == -1)
	{
		/*
		 * Get user input date
		 */
		try
		{
			projectViewer.displayMessage("Enter Year: ", false); year = stoi(getUserInput());
			projectViewer.displayMessage("Enter Month: ", false); month = stoi(getUserInput());
			projectViewer.displayMessage("Enter Day: ", false); day = stoi(getUserInput());
		}
		catch (std::invalid_argument ia)
		{
			validInput = false;
			projectViewer.displayMessage("Invalid input please re enter");
		}

		if (validInput)
		{
			time(&rawTime);						
			localtime_s(&timeInfo, &rawTime);				// Init timeInfo struct
	
			timeInfo.tm_year = year - 1900;					// Setup timeInfo struct
			timeInfo.tm_mon = month - 1;
			timeInfo.tm_mday = day;
			timeInfo.tm_hour = 1;
			timeInfo.tm_min = 0;
			timeInfo.tm_sec = 0;
		
			timestamp = mktime(&timeInfo);					// COnvert to unix
		
			if (timestamp == -1)							// Invalid date set entered
				projectViewer.displayMessage("invalid date please re enter");
		}
	}

	return timestamp;
}

/*
* display user with a message and return a non null input
*/
const std::string ProjectManager::messageReturnInput(const std::string & message)
{
	projectViewer.displayMessage(message);
	projectViewer.displayMessage("Please enter your input");

	std::string input = getUserInput();
	while ((input == "") && (input.find_first_of(" ") == std::string::npos))  // Ensure user input is not null or only spaces
	{
		projectViewer.displayMessage("Your input cannot be nothing. Please try again");
		input = getUserInput();
	}

	return input;
}

/*
 * Display message on screen and get multiple user input and return in a vector
 */
const std::vector<std::string> ProjectManager::messageReturnUserVector(const std::string & message, const bool canBeNull /*false*/)
{
	projectViewer.displayMessage(message);
	if(!canBeNull)
		projectViewer.displayMessage("Atleast one value needs to be entered");
	projectViewer.displayMessage("enter : exit---loop to finish");
	
	std::vector<std::string> userData = {};
	std::string input = "";
	
	while ((toLower(input) != "exit---loop") || (userData.empty() && !canBeNull))
	{
		projectViewer.displayMessage("Please enter a value. Or exit---loop to finish");
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

	projectViewer.displayMessage(message);

	projectViewer.displayMessage("Atleast one value needs to be entered");
	projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<int> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		projectViewer.displayMessage("Please enter a value. Or exit---loop to finish");
		projectViewer.displayMessage("This is data set : " + userData.size() + 1);
		input = getUserInput();
		if (toLower(input) != "exit---loop")
		{
			try
			{
				userData.push_back(std::stoi(input));
			}
			catch (std::invalid_argument ia)
			{
				projectViewer.displayMessage("Could not convert " + input + " to an integer");
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
	projectViewer.displayMessage(message);

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
			projectViewer.displayMessage("Invalid input entered! please try again (must be an integer)");
		}
	}

	return aspectratio;
}

/*
 * Displays a message and converts input to an integer 
 */
const int ProjectManager::messageReturnInt(const std::string & message)
{
	projectViewer.displayMessage(message);
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
			projectViewer.displayMessage("Not a valid input plese try again");
		}
	}
	return i;
}


/*
 * Gets a user input and converts to a float
 */
const float ProjectManager::messageReturnFloat(const std::string & message)
{
	projectViewer.displayMessage(message);
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
			projectViewer.displayMessage("Not a valid input plese try again");
		}
	}
	return f;
}


const bool ProjectManager::yesNoBool(const std::string & message)
{
	projectViewer.displayMessage(message);

	std::string input = "";
	while (toLower(input) != "yes" && toLower(input) != "no")
	{
		projectViewer.displayMessage("please enter a valid option. Yes or No");
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

const bool ProjectManager::isreleased(const long timestamp)
{
	time_t rawTime;
	time(&rawTime);

	return timestamp <= rawTime;
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
