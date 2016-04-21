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
	
	ProjectViewer projectViewer;

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

	void processDeleteOptions();

	void processEditOptions();

	void processProjectEditFields(Project* project);
	
	void processMaterialEditFields(Material* material);

	void processBrowseOptions();

	void processInteractiveSearch();

	void sequentialBrowseProjects();

	void sequentialBrowseMaterials();

	/*
	* Ask the user a yes no question and convert their answer to a bool
	* yes : true
	* no  : false
	*/
	const bool yesNoBool(const std::string & message);


	/*
	* Prints message to display
	* Gets a list of materials
	*/
	std::vector<Material*> getMaterialsFromUser(const std::string& message, const bool oneExisting = false);

	/*
	* Display a message and get a user entered integer
	*/
	const int messageReturnInt(const std::string & message);

	/*
	* Display a message and get a non null user input
	*/
	const std::string messageReturnInput(const std::string& message);

	/*
	* Process the user input for linking media together
	*/
	void linkMedia();

	Material * getAssociatedMaterial(const std::string & message);

	/*
	* Prints message to display and promts user and returns their selected project
	*/
	Project* getProjectFromUser(const std::string & message);

	const std::vector<int> messageReturnUserVectorInt(const std::string & message);

	const long messageGetDate(const std::string & message);
	/*
	* Display a message and continue to get user inputs and add to a vector until the user is satisifed
	*/
	const std::vector<std::string> messageReturnUserVector(const std::string& message, const bool canBeNull = false);

};

