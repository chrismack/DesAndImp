#include "stdafx.h"
#include "ProjectManager.h"

#include <iostream>
#include <fstream>


#include "MaterialFactory.h"
#include "CSVHandler.h"

#include "../SeminarD/BlueRay.h"



ProjectManager::ProjectManager()
{
	SDI::Logger l;
	l.setLogLevel(SDI::Logger::LogLevel::ALL);
	l.info("Logger started");
	exit_ = false;	// Initally set that we don't want to leave the application
	
	while (!exit_)
	{
		displayMenuOptions();
		processUserInput(getUserInput());
		userContinueOption();
	}
	std::cout << "Hello" << std::endl;
	importFile("test.csv");
	displayMenuOptions();
}


ProjectManager::~ProjectManager()
{
}

/*
 * Try to import a file from a specified path
 *
 * return if the file has been imported
 */
bool ProjectManager::importFile(std::string path)
{
	std::cout << "Importing " << path << std::endl;
	if (fileExists(path))
	{
		std::string extension = path.substr(path.find_last_of('.') + 1);	// Get the extension of the file that is being imported

		if (extension == "csv")
		{
			
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
			
			return true;
		}
		else if (extension == "xml")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

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

 std::string ProjectManager::toLower(std::string & input)
 {
	 for (int i = 0; i < input.length(); i++)
	 {
		 input[i] = tolower(input[i]);
	 }
	return input;
}
