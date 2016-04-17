#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#pragma once

#include <string>
#include <vector>
#include <map>

#include "Material.h"
#include "Project.h"
#include "IPackagable.h"
#include "Disc.h"

#include "LogHandler.h"
#include "Logger.h"
#include "ProjectViewer.h"

class ProjectManager
{
private: // Variables

	SDI::Logger* logger;

	ProjectViewer projectViewer;

	/*
	 * List of all imported projects
	 */
	//std::vector<Project*>  projects_;
	std::map<Project*, bool> projects_;

	/*
	 * List of all imported materials
	 */
	std::vector<Material*> materials_;
	std::vector<Material*> projectAssociatedMaterials;

	int materialCount = 0;

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
	ProjectManager();

	/*
	 * Deconstructor
	 */
	~ProjectManager();

	/*
	* import projects and materials from a specified class
	*
	* path   : to the file to be imported
	* Return : if the file can be properly imported
	*/
	bool importFile(const std::string path);

	/*
	 * Saves memory to file
	 */
	void save();

	/*
	 * Check for the default save file and if it exists or not
	 */
	void setupSaveFile();

	void updateDisplay(const std::string & message);

	void displayViewOptions();

	void displayCreateMenu();

	void displaySearchMenu();

	void displayMenuOptions();

	void clearView();

	void viewProjects();

	void viewMaterials();

	void createAndAddProject();

	void createAndAddMaterial();

	void createLink();

	void projectFindMaterial();

	void materialFindProject();

	/*
	* Process the user input for linking media together
	*/
	void linkMedia();

private: // Functions

	/*
	 * Allow user to create a material
	 * Should allow materials with the same name as existing material
	 */
	Project* createProject();

	/*
	 * Allow user to create a material
	 * Present options depending on material type
	 */
	Material* createMaterial(const bool mustBeDisc = false);

	/*
	 * Set the attributes of the referenced material
	 */
	void setBaseMaterialAttributes(Material* material, const std::string& message);

	/*
	 * Display a message to the user
	 * Get their input and put their input
	 */
	std::map<int, std::vector<std::string>> setVectorSideMap(const std::string & message);

	/*
	 * Set package attributes for a material
	 */
	void setMaterialPackage(IPackagable* material);

	/*
	 * prints message to display
	 * gets a list of materials defined by the users
	 * Presents user with list of materials loaded into memory for them to select from
	 */
	std::vector<Disc*> getDiscMaterialsFromUser(const std::string& message);

	/*
	 * Prints message to display
	 * Gets a list of materials
	 */
	std::vector<Material*> getMaterialsFromUser(const std::string& message, const bool oneExisting = false);

	Material* getAssociatedMaterial(const std::string& message);

	/*
	 * Prints message to display and promts user and returns their selected project
	 */
	Project* getProjectFromUser(const std::string & message);

	/*
	 * Get input from the user 
	 *
	 * Return std::cin (what they have entered)
	 */
	std::string getUserInput();

	/*
	 * Process and import data that has been formatted in CSV
	 */
	void importCSV(const std::string &CSV, const bool checkNowPlaying = false);

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
	const std::vector<std::string> messageReturnUserVector(const std::string& message, const bool canBeNull = false);

	/*
	 * Display a message and continue to get user inputs and add to a vector until the user is satisifed
	 * returns vector of ints, used for ticket sales
	 */
	const std::vector<int> messageReturnUserVectorInt(const std::string& message);

	/*
	 * Display a message and get the users input for an aspect ratio (int, int)
	 */
	const std::pair<int, int> messageGetAspect(const std::string & message);

	/*
	 * Display a message and get a user entered integer
	 */
	const int messageReturnInt(const std::string & message);

	/*
	* Display a message and get a user entered float
	*/
	const float messageReturnFloat(const std::string & message);

	/*
	 * Ask the user a yes no question and convert their answer to a bool
	 * yes : true
	 * no  : false
	 */
	const bool yesNoBool(const std::string & message);

	/*
	 * Check if a project has been released or not
	 * Check against local time
	 */
	const bool isReleased(Project* project);

	/*
	* Check if unix time stamp is more than or equal to local timestamp
	*/
	const bool isreleased(const long timestamp);

	/*
	 * Converts a string to all lower case
	 */
	std::string toLower(std::string &input);

};

#endif // !PROJECTMANAGER_H
