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

	setupSaveFile();
	start();
}


ProjectManager::~ProjectManager()
{
	projects_.clear();
	materials_.clear();
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
		displayMenuOptions();
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
	materials_.insert(materials_.end(), materialsFromFile.begin(), materialsFromFile.end());	// Append to existing projects
	materialsFromFile.clear();

	/*
	 * Append projects to list of existing projects
	 */
	std::vector<Project*> projectsFromFile = csvHandler.getProjectsFromFile();
	for (Project* project : projectsFromFile)
	{
		std::cout << "Is this project now playing?" << std::endl;
		std::cout << project->getTitle() << " : " << project->getGenre() << " : " << project->getSummary() << std::endl;
		std::string input = "";
		while (toLower(input) != "yes" || toLower(input) != "no")
		{
			std::cout << "please enter a valid option. Yes or No" << std::endl;
			input = getUserInput();
			if (toLower(input) == "yes" || toLower(input) == "no")
			{
				projects_.insert(std::pair<Project*, bool>(project, toLower(input) == "yes" ? true : false));
			}
		}
	}
	//projects_.insert(projects_.end(), projectsFromFile.begin(), projectsFromFile.end());	// Append to existing projects
	//projectsFromFile.clear();

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
			std::cout << material->getId() << " : " << material->getFilmTitle() << std::endl;
			delete material;
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

		std::cout << "Is the project now playing?" << std::endl;

		std::string input = "";
		while (toLower(input) != "yes" && toLower(input) != "no")
		{
			std::cout << "please enter a valid option. Yes or No" << std::endl;
			input = getUserInput();
			if (toLower(input) == "yes" || toLower(input) == "no")
			{
				projects_.insert(std::pair<Project*, bool>(project, toLower(input) == "yes" ? true : false));
			}
		}
	}
	else if (input == "2" || input == "create material")
	{
		createMaterial();
	}
	else if (input == "3" || input == "link media")
	{
		displayLinkingMenu();
	}
}

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

Material * ProjectManager::createMaterial()
{
	Material* material;
	std::string type = messageReturnInput("Set Type");
	if (type == "BluRay")
	{
		BlueRay* material = new BlueRay();
	}
	else if (type == "SingleDVD")
	{
		SingleDVD* material = new SingleDVD();
	}
	else if (type == "DoubleDVD")
	{
		DoubleDVD* material = new DoubleDVD();
	}
	else if (type == "Combo")
	{
		ComboBox* material = new ComboBox();
	}
	else if (type == "VHS")
	{
		VHS* material = new VHS();
	}

	material->setID(materials_.size());
	material->setFilmTitle(messageReturnInput("Set Title"));
	material->setFormat(messageReturnInput("Set Format"));
	material->setAudioFormat(messageReturnInput("Set Audio Format"));
	//material->setRunTime(messageReturnInput("Set Runtime"));
	material->setLanguage(messageReturnInput("Set Language"));
	//material->setRetailPrice(messageReturnInput("Set Retail Price"));
	material->setSubtitles(messageReturnInput("Set Subtitles"));
	//material->setAspectRation(messageReturnInput("Set Aspect Ratio"));

	return material;
}

/*
 * Display options for linking materials and projects together
 */
void ProjectManager::displayLinkingMenu()
{
	std::cout << "Would you like to link a Project to a material or material to project" << std::endl;
	std::cout << "1) Project to material" << std::endl;
	std::cout << "2) Material to project" << std::endl;
}

void ProjectManager::processLinkingOptins()
{
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
	std::cin >> userInput;
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
			 csvHandler.writeToFile(it->first);
		 }

		 /*for (Project* project : projects_)
		 {
			 csvHandler.writeToFile(project);
			 delete project;
		 }*/

		 for (Material* material : materials_)
		 {
			 csvHandler.writeToFile(material);
			 delete material;
		 }

		 saveFile.close();
		 delete mf;
	 }
	 else if (input == "3" || input == "view")
	 {
		 displayViewOptions();
	 }
	 else if (input == "4" || input == "create")
	 {
		 displayCreateMenu();
	 }
	 else			// No valid option has been entered
	 {
		 std::cout << "You didn't enter a valid option" << std::endl;
	 }
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
			//printf("Enter year: "); fflush(stdout); scanf_s("%d", &year);
			//printf("Enter month: "); fflush(stdout); scanf_s("%d", &month);
			//printf("Enter day: "); fflush(stdout); scanf_s("%d", &day);
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

const std::vector<std::string> ProjectManager::messageReturnUserVector(const std::string & message)
{
	std::cout << message << std::endl;
	
	std::cout << "Atleast one value needs to be entered" << std::endl;
	std::cout << "enter : exit---loop to finish" << std::endl;
	
	std::vector<std::string> userData = {};
	std::string input = "";
	
	while ((toLower(input) != "exit---loop") || userData.empty())
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
