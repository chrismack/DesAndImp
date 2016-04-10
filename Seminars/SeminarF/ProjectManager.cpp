#include "stdafx.h"
#include "ProjectManager.h"

#include <iostream>
#include <fstream>

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
	projects_.insert(projects_.end(), projectsFromFile.begin(), projectsFromFile.end());	// Append to existing projects
	projectsFromFile.clear();
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
	std::cout << "			MENU			      "	<< std::endl;
	std::cout << "0)exit   : leave the application" << std::endl;		// Leave applicatoin
	std::cout << "1)import : Import from file"		<< std::endl;		// Import materials from files
	std::cout << "2)save   : Save to file"			<< std::endl;		// Save material strings to file
	std::cout << "3)view   : View data"				<< std::endl;		// View Materials and projects currently stored in memory
	std::cout << std::endl;			
}

void ProjectManager::displayViewOptions()
{
	std::cout << "What would you like to view?" << std::endl << "1)Projects or 2)Materials" << std::endl;;
	std::cout << "Please enter you choice" << std::endl;
}

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
		 CSVHandler csvHandler(defaultSavePath, new MaterialFactory());
		 
		 for (Project* project : projects_)
		 {
			 csvHandler.writeToFile(project);
			 delete project;
		 }

		 for (Material* material : materials_)
		 {
			 csvHandler.writeToFile(material);
			 delete material;
		 }

		 saveFile.close();
	 }
	 else if (input == "3" || input == "view")
	 {
		 displayViewOptions();
		 std::string viewOption = toLower(getUserInput());
		 if (viewOption == "1" || viewOption == "projects")
		 {
			 for (Project* project : projects_)
			 {
				 std::cout << project->getTitle() << std::endl;
				 delete project;
			 }
		 }
		 else if (viewOption == "2" || viewOption == "materials")
		 {
			 for (Material* material : materials_)
			 {
				 std::cout << material->getId() << " : "<< material->getFilmTitle() << std::endl;
				 delete material;
			 }
		 }
		 else		// No valid option has been entered for view option
		 {
			 std::cout << "You didn't enter a valid option for view" << std::endl;
		 }
	 }
	 else			// No valid option has been entered
	 {
		 std::cout << "You didn't enter a valid option" << std::endl;
	 }
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
