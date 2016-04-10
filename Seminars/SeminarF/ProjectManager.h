#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#pragma once

#include <string>
#include <vector>

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
	std::vector<Project*>  projects_;

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
	 * Converts a string to all lower case
	 */
	std::string toLower(std::string &input);
};

#endif // !PROJECTMANAGER_H
