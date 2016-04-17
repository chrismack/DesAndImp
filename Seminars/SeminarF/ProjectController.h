#pragma once

#include "Logger.h"

#include "ProjectManager.h"	//Model

class ProjectController
{
private :

	SDI::Logger* logger;

	/*
	* The default save location for the projects and materials to be saved to
	*/
	std::string defaultSavePath = "projectmanager.csv";

	ProjectManager projectManager;

public:
	ProjectController(SDI::Logger * logger);
	~ProjectController();

	/*
	* Get input from the user
	*
	* Return std::cin (what they have entered)
	*/
	std::string getUserInput();

private:

	bool exit_;

	/*
	* The main loop for the application
	*/
	void start();

	/*
	* Display a message to the user and ask if they would like to continue
	* Process the information if they would like to carry one in the application or not
	*/
	void userContinueOption();

	/*
	* Converts a string to all lower case
	*/
	std::string toLower(std::string &input);
	
	/*
	* Takes the users input and completes the operation that relates to the
	* input entered
	*/
	void processUserInput(const std::string & message);

	void processViewOptions();

	void processCreateOptions();

	void processSearchOptions();
};

