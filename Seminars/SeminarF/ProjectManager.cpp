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


ProjectManager::ProjectManager(SDI::Logger *logger)
{
	this->logger = LogHandler::getHandler()->logger;
	this->logger->setLogLevel(SDI::Logger::LogLevel::ALL);

	exit_ = false;	// Initally set that we don't want to leave the application
	this->logger->info("Starting the Project Manager");

	projectViewer = new ProjectViewer(this);

	materialCount = -1;
	
	setupSaveFile();
	start();
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
		std::cout << "You do not have any existing projects or materials"		 << std::endl;
		std::cout << "Would you like to import from an existing file? Yes or No" << std::endl;
		
		std::string userImport = toLower(getUserInput());
		if (userImport == "yes" || userImport == "y")
		{
			std::cout << "What file would you like to import?" << std::endl;
			importFile(getUserInput());
		}
	}
	else
	{
		importCSV(defaultSavePath);
	}
}

void ProjectManager::start()
{
	while (!exit_)
	{
		projectViewer->displayMenuOptions();
		processUserInput(getUserInput());
		userContinueOption();
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
			std::cout << "Is this project now playing?" << std::endl;
			std::cout << "Title: " << it->first->getTitle() << " Genre: " << it->first->getGenre() << " Summary: " << it->first->getSummary() << std::endl;
			std::string tmpNowPlayingStr = it->second == true ? "true" : "false";
			std::cout << "Currently saved as : " << tmpNowPlayingStr << std::endl;
			std::string input = "";
			while (toLower(input) != "yes" && toLower(input) != "no")
			{
				std::cout << "please enter a valid option. Yes or No" << std::endl;
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
 * Display menu options on screen
 */
void ProjectManager::displayMenuOptions()
{
	std::cout << "			MENU			      " << std::endl;
	std::cout << "0)exit   : leave the application" << std::endl;		// Leave applicatoin
	std::cout << "1)import : Import from file" << std::endl;		// Import materials from files
	std::cout << "2)save   : Save to file" << std::endl;		// Save material strings to file
	std::cout << "3)view   : View data" << std::endl;		// View Materials and projects currently stored in memory
	std::cout << "4)create : Create Material or Proj" << std::endl;
	std::cout << "5)search : Search for linked media" << std::endl;
	std::cout << std::endl;
}

/*
 * Display options for viewing materials loaded into memory
 */
void ProjectManager::displayViewOptions()
{
	std::cout << "What would you like to view?" << std::endl << "1)Projects or 2)Materials" << std::endl;;
	std::cout << "Please enter you choice" << std::endl;
	processViewOptinos();
}

void ProjectManager::processViewOptinos()
{
	std::string viewOption = toLower(getUserInput());
	if (viewOption == "1" || viewOption == "projects")
	{

		std::map<Project*, bool>::iterator it;
		for (it = projects_.begin(); it != projects_.end(); ++it)
		{
			std::cout << it->first->getTitle() << std::endl;
		}
		/*for (Project* project : projects_)
		{
			std::cout << project->getTitle() << std::endl;
			delete project;
		}*/
	}
	else if (viewOption == "2" || viewOption == "materials")
	{
		for (Material* material : materials_)
		{
			if(material != nullptr)
				std::cout << material->getId() << " : " << material->getFilmTitle() << std::endl;
		}

		for (Material* material : projectAssociatedMaterials)
		{
			if (material != nullptr)
				std::cout << material->getId() << " : " << material->getFilmTitle() << "Associated with project" << std::endl;
		}

	}
	else		// No valid option has been entered for view option
	{
		std::cout << "You didn't enter a valid option for view" << std::endl;
	}
}

/*
 * display the options for creating materials or projects
 */
void ProjectManager::displayCreateMenu()
{
	std::cout << "What operation would you like to complete?" << std::endl;
	std::cout << "1) Create Project" << std::endl;		// Create a project and add to projects_
	std::cout << "2) Create Material" << std::endl;		// Create a material and add to materials_
	std::cout << "3) Link Media" << std::endl;		// Display linking menu

	std::cout << "Please enter your option : " << std::endl;
	processCreateOptions();
}

void ProjectManager::processCreateOptions()
{
	std::string input = toLower(getUserInput());
	if (input == "1" || input == "create project")
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
	else if (input == "2" || input == "create material")
	{
		materials_.push_back(createMaterial());
	}
	else if (input == "3" || input == "link media")
	{
		std::cout << "Please select a project and material to link" << std::endl;
		processLinkingOptins();
	}
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
			std::cout << "Please enter valid type; BluRay, SingleDVD, DoubleDVD" << std::endl;
		}
		else
		{
			std::cout << "Please enter valid type; BluRay, SingleDVD, DoubleDVD, Combo, VHS" << std::endl;
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
	std::cout << message << std::endl;
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
	std::cout << message << std::endl;

	std::cout << "Atleast one value needs to be entered" << std::endl;
	std::cout << "enter : exit---loop to finish" << std::endl;

	std::vector<int> validID;
	std::vector<int> selectedId;
	std::vector<Disc*> userData = {};
	std::string input = "";

	std::cout << "ID :	TITLE : FORMAT" << std::endl;
	for (Material* mat: materials_)
	{
		if (mat != nullptr)
		{
			std::string format = mat->getFormat();
			if (toLower(format) == "bluray" || toLower(format) == "singledvd" || toLower(format) == "doubledvd")
			{
				std::cout << mat->getId() << " : " << mat->getFilmTitle() << " : " << mat->getFormat() << std::endl;
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
			std::cout << "Please enter material index. Or exit---loop to finish" << std::endl;
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
				std::cout << "Please enter a valid id (integer)" << std::endl;
			}
		}
	}

	return userData;
}

std::vector<Material*> ProjectManager::getMaterialsFromUser(const std::string & message, const bool oneExisting /* false */)
{
	std::cout << message << std::endl;

	std::cout << "Atleast one value needs to be entered" << std::endl;
	std::cout << "enter : exit---loop to finish" << std::endl;

	std::vector<int> selectedId;
	std::vector<Material*> userData = {};
	std::string input = "";

	std::cout << "ID :	TITLE : FORMAT" << std::endl;
	for (Material* mat : materials_)
	{
		if(mat != nullptr)
		{
			std::cout << mat->getId() << " : " << mat->getFilmTitle() << " : " << mat->getFormat() << std::endl;
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
				std::cout << "Please enter material index. Or exit---loop to finish" << std::endl;
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
					std::cout << "Please enter a valid id (integer)" << std::endl;
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
				std::cout << "Please enter material index" << std::endl;
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
			std::cout << "No materials exist" << std::endl;
		}
	}
	return userData;
}

Material * ProjectManager::getAssociatedMaterial(const std::string & message)
{
	std::cout << message << std::endl;
	Material* material = nullptr;
	std::string input;
	std::vector<int> validIndex;
	for (Material* mat : projectAssociatedMaterials)
	{
		if (mat != nullptr)
		{
			std::cout << mat->getId() << " : " << mat->getFilmTitle() << " : " << mat->getFormat() << std::endl;
			validIndex.push_back(mat->getId());
		}
	}

	if (!materials_.empty())
	{
		bool valid = false;
		do
		{
			std::cout << "Please enter material index" << std::endl;
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
		std::cout << "No materials exist" << std::endl;
	}
	return material;
}

Project * ProjectManager::getProjectFromUser(const std::string & message)
{
	std::cout << message << std::endl;

	Project* project = nullptr;
	std::vector<Project*> tmpProjects;
	if (!projects_.empty())
	{
		std::cout << "INDEX : TITLE : SUMMARY : GENRE" << std::endl;

		int index = 0;
		std::map<Project*, bool>::iterator it;
		for (it = projects_.begin(); it != projects_.end(); ++it)
		{
			std::cout << index << " : " << it->first->getTitle() << " : " << it->first->getSummary() << " : " << it->first->getGenre() << std::endl;
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
		std::cout << "Their are no loaded projects! Import or create one" << std::endl;
		return nullptr;
	}

	return project;
}

void ProjectManager::processLinkingOptins()
{
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
				std::cout << "Project has not been released. Materials cannot be added" << std::endl;
			}
		}
	}
	else		// Missing either a project or material
	{
		std::cout << "You need to have atleast one project and one material to make a link" << std::endl;
	}
}

/*
 * Has the user finished using the program
 */
void ProjectManager::userContinueOption()
{

	if (exit_ == false) // Skip this step if we are already leaving the application
	{
		// Display message to the user
		std::cout << std::endl;		// Blank space
		std::cout << "Would you like to continue?" << std::endl;
		std::cout << "Yes or No" << std::endl;
	
		std::string userContinue = toLower(getUserInput());
		if (userContinue == "no" )
			exit_ = true;

		system("cls");
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
 * Takes the users input and processes input that has been entered
 */
 void ProjectManager::processUserInput(const std::string &input)
 {
	 if (input == "exit" || input == "0")
	 {
		 exit_ = true;
	 }
	 else if (input == "1" || input == "import")
	 {
		 std::cout << "Please enter a path to the file you would like to import : " << std::endl;
		 importFile(getUserInput());
	 }
	 else if (input == "2" || input == "save")
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

		 /*for (Project* project : projects_)
		 {
			 csvHandler.writeToFile(project);
			 delete project;
		 }*/

		 for (Material* material : materials_)
		 {
			 if(material != nullptr)
				 csvHandler.writeToFile(material);
		 }

		 saveFile.close();
		 delete mf;
	 }
	 else if (input == "3" || input == "view")
	 {
		 projectViewer->displayViewOptions();// displayViewOptions();
	 }
	 else if (input == "4" || input == "create")
	 {
		 displayCreateMenu();
	 }
	 else if (input == "5" || input == "search")
	 {
		 displaySearchMenu();
	 }
	 else			// No valid option has been entered
	 {
		 std::cout << "You didn't enter a valid option" << std::endl;
	 }
 }

 /*
  * Display the search menu
  */
 void ProjectManager::displaySearchMenu()
 {
	 std::cout << std::endl;
	 std::cout << "Please select a seach option" << std::endl;
	 std::cout << "1)Find materials associated with project" << std::endl;
	 std::cout << "2)Find project associated with material" << std::endl;
	 processSearchOptions();
 }

 /*
  * Process the user input after the search menu
  */
 void ProjectManager::processSearchOptions()
 {
	 bool valid = true;
	 std::string input;
	 do
	 {
		 input = messageReturnInput("Please enter your option. 1 or 2");
		 input = toLower(input);

		 if (input == "1")
		 {
			 Project* project = getProjectFromUser("Select project to view associated materials");
			 if (!project->getMaterials().empty())
			 {
				 for (Material* material : project->getMaterials())
				 {
					 std::cout << "TITLE : " << material->getFilmTitle() << "   ";
					 std::cout << "FORMAT : " << material->getFormat() << "   ";
					 std::cout << "" << material->getLanguage() << "   ";
					 std::cout << std::endl;

					 if (yesNoBool("Would you like to view the full material?"))
					 {
						 viewFullMaterial(material);
					 }
				 
				 }
				 valid = true;
			 }
			 else
			 {
				 std::cout << "Project doesn't have any associated materials" << std::endl;
			 }
		 }
		 else if (input == "2")
		 {
			Material* material = getAssociatedMaterial("Select a material to view linked project");
			if (material != nullptr)
			{

				valid = true;
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
					std::cout << "TILTE: " << proj->getTitle() << " SUMMARY:" << proj->getSummary() << std::endl;
				
					if (yesNoBool("Would you like to see the whole project?"))
					{
						std::vector<std::string> projElements = proj->toArray();
						std::stringstream ss;
						for (std::string element : projElements)
						{
							ss << element << " :: ";
						}
						std::cout << ss.str() << std::endl;
					}
				}
			}
			else
			{
				std::cout << "Couldn't find associated project" << std::endl;
			}
		 }
		 else
		 {
			 valid = false;
		 }
	 } while (!valid);
 }


/*
 * Heavily based on:
 * http://www.cplusplus.com/reference/ctime/mktime/
 */
const long ProjectManager::messageGetDate(const std::string & message)
{

	std::cout << message << std::endl;

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
			std::cout << "Enter Year: " ; year  = stoi(getUserInput());
			std::cout << "Enter Month: "; month = stoi(getUserInput());
			std::cout << "Enter Day: "  ; day   = stoi(getUserInput());
		}
		catch (std::invalid_argument ia)
		{
			validInput = false;
			std::cout << "Invalid input please re enter" << std::endl;
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
				std::cout << "invalid date please re enter" << std::endl;
		}
	}

	return timestamp;
}

/*
* display user with a message and return a non null input
*/
const std::string ProjectManager::messageReturnInput(const std::string & message)
{
	std::cout << message << std::endl;
	std::cout << "Please enter your input" << std::endl;

	std::string input = getUserInput();
	while ((input == "") && (input.find_first_of(" ") == std::string::npos))  // Ensure user input is not null or only spaces
	{
		std::cout << "Your input cannot be nothing. Please try again" << std::endl;
		input = getUserInput();
	}

	return input;
}

/*
 * Display message on screen and get multiple user input and return in a vector
 */
const std::vector<std::string> ProjectManager::messageReturnUserVector(const std::string & message, const bool canBeNull /*false*/)
{
	std::cout << message << std::endl;
	if(!canBeNull)
		std::cout << "Atleast one value needs to be entered" << std::endl;
	std::cout << "enter : exit---loop to finish" << std::endl;
	
	std::vector<std::string> userData = {};
	std::string input = "";
	
	while ((toLower(input) != "exit---loop") || (userData.empty() && !canBeNull))
	{
		std::cout << "Please enter a value. Or exit---loop to finish" << std::endl;
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

	std::cout << message << std::endl;

	std::cout << "Atleast one value needs to be entered" << std::endl;
	std::cout << "enter : exit---loop to finish" << std::endl;

	std::vector<int> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		std::cout << "Please enter a value. Or exit---loop to finish" << std::endl;
		std::cout << "This is data set : " << userData.size() + 1 << std::endl;
		input = getUserInput();
		if (toLower(input) != "exit---loop")
		{
			try
			{
				userData.push_back(std::stoi(input));
			}
			catch (std::invalid_argument ia)
			{
				std::cout << "Could not convert " << input << " to an integer" << std::endl;
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
	std::cout << message << std::endl;

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
			std::cout << "Invalid input entered! please try again (must be an integer)" << std::endl;
		}
	}

	return aspectratio;
}

/*
 * Displays a message and converts input to an integer 
 */
const int ProjectManager::messageReturnInt(const std::string & message)
{
	std::cout << message << std::endl;
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
			std::cout << "Not a valid input plese try again" << std::endl;
		}
	}
	return i;
}


/*
 * Gets a user input and converts to a float
 */
const float ProjectManager::messageReturnFloat(const std::string & message)
{
	std::cout << message << std::endl;
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
			std::cout << "Not a valid input plese try again" << std::endl;
		}
	}
	return f;
}


const bool ProjectManager::yesNoBool(const std::string & message)
{
	std::cout << message << std::endl;

	std::string input = "";
	while (toLower(input) != "yes" && toLower(input) != "no")
	{
		std::cout << "please enter a valid option. Yes or No" << std::endl;
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

void ProjectManager::viewFullMaterial(Material * material)
{
	std::vector<std::string> materialElements = material->toArray();

	std::stringstream ss;

	for (std::string element : materialElements)
	{
		ss << element << " :: ";
	}

	std::cout << ss.str() << std::endl;
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
