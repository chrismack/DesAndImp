#include "stdafx.h"
#include "ProjectManager.h"

#include <iostream>
#include <fstream>

#include "Logger.h"

#include "MaterialFactory.h"
#include "CSVHandler.h"

#include "../SeminarD/BlueRay.h"


#define _CRT_SECURE_NO_WARNINGS

ProjectManager::ProjectManager()
{
	exit_ = false;	// Initally set that we don't want to leave the application
	
	start();
}

ProjectManager::ProjectManager(SDI::Logger *logger)
{
	logger = LogHandler::getHandler()->logger;
	logger->setLogLevel(SDI::Logger::LogLevel::ALL);

	
	exit_ = false;	// Initally set that we don't want to leave the application
	logger->info("Starting the Project Manager");
	start();
}


ProjectManager::~ProjectManager()
{
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
			MaterialFactory* mf = new MaterialFactory();
			CSVHandler csvHandler(path, mf);
			
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
	std::cout << "0)exit   : leave the application" << std::endl;
	std::cout << "1)import : Import from file"		<< std::endl;
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
