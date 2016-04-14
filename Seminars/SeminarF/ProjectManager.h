#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#pragma once

#include <string>
#include <vector>
#include <map>

#include "Material.h"
#include "Project.h"

#include "LogHandler.h"
#include "Logger.h"

class ProjectManager
{
private: // Variables

	SDI::Logger* logger;

	/*
	 * List of all imported projects
	 */
	//std::vector<Project*>  projects_;
	std::map<Project*, bool> projects_;

	/*
	 * List of all imported materials
	 */
	std::vector<Material*> materials_;
	/*
	 * Flag to test if the user wants to leave the application
	 */
	bool exit_;

	/*
	 * The default save location for the projects and materials to be saved to 
	 */
	std::string defaultSavePath = "projectmanager.csv";

public:  // Functions

	/*
	 * start project with logging
	 */
	ProjectManager(SDI::Logger * logger);

	/*
	 * Deconstructor
	 */
	~ProjectManager();

private: // Functions

	/*
	 * Check for the default save file and if it exists or not
	 */
	void setupSaveFile();

	/*
	 * The main loop for the application 
	 */
	void start();

	/*
	 * Write options to the display
	 */
	void displayMenuOptions();

	/*
	 * Display message on screen for views that can be selected
	 * displayed when option 3(view) from the menu is selected 
	 */
	void displayViewOptions();

	/*
	 * Process the user input for the view menu
	 */
	void processViewOptinos();

	/*
	 * Display the create menu sub options
	 * displayed when option 4(create) from menu is selected
	 */
	void displayCreateMenu();

	/*
	 * Process the user input for the create media options
	 */
	void processCreateOptions();

	/*
	 * Allow user to create a material
	 * Should allow materials with the same name as existing material
	 */
	Project* createProject();

	/*
	 * Allow user to create a material
	 * Present options depending on material type
	 */
	Material* createMaterial();

	/*
	 * Display the options for linking media together
	 * Material to Project or Project to Material
	 */
	void displayLinkingMenu();

	/*
	 * Process the user input for linking media together
	 */
	void processLinkingOptins();

	/*
	 * Display a message to the user and ask if they would like to continue
	 * Process the information if they would like to carry one in the application or not
	 */
	void userContinueOption();

	/*
	 * Get input from the user 
	 *
	 * Return std::cin (what they have entered)
	 */
	std::string getUserInput();

	/*
	 * Takes the users input and completes the operation that relates to the
	 * input entered
	 */
	void processUserInput(const std::string &input);

	/*
	 * import projects and materials from a specified class
	 *
	 * path   : to the file to be imported
	 * Return : if the file can be properly imported
	 */
	bool importFile(const std::string path);

	/*
	 * Process and import data that has been formatted in CSV
	 */
	void importCSV(const std::string &CSV);

	/*
	 * Check if file at path exists
	 */
	const bool fileExists(const std::string &path);

	/*
	 * Display a message and get a non null user input
	 */
	const std::string messageReturnInput(const std::string& message);

	/*
	 * Display a message and convert the user input into a unix time stamp
	 */
	const long messageGetDate(const std::string& message);

	/*
	 * Display a message and continue to get user inputs and add to a vector until the user is satisifed
	 */
	const std::vector<std::string> messageReturnUserVector(const std::string& message);

	/*
	 * Display a message and continue to get user inputs and add to a vector until the user is satisifed
	 * returns vector of ints, used for ticket sales
	 */
	const std::vector<int> messageReturnUserVectorInt(const std::string& message);

	/*
	 * This should be in the CSVHandler but i'm not sure if i'm aloud to chage it so it shall go here
	 * Write Projects to file with the now playing arg
	 */
	void writeToFile(Project* project, bool nowPlaying);

	/*
	 * Converts a string to all lower case
	 */
	std::string toLower(std::string &input);
};

#endif // !PROJECTMANAGER_H