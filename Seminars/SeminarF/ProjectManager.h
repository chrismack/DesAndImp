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

	//ProjectViewer projectViewer;

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
	bool setupSaveFile();

	void clearView();

	void viewProjects();

	void viewMaterials();

	void createLink();

	std::vector<Material*> projectFindMaterial(Project* material);

	std::vector<Project*> materialFindProject(Material* material);

	void deleteProject();

	void deleteMaterial();
	
	int getMaterialCount();

	void incrementMaterialCount();

	void setMaterialCounter(const int count);

	std::vector<Disc*> getExistingDiscs();

	void addMaterial(Material* material);

	void addProject(Project* project, bool nowPlaying);

	std::vector<Project*> getProjects();

	std::vector<Material*> getMaterials();

	std::vector<Material*> getProjectAssociatedMaterials();

	std::pair<std::vector<Material*>, std::vector<Material*>> getAllMaterials();

	std::map<Project*, bool> getProjectMap();

	void addMaterialToProject(Project* project, std::vector<Material*> materials);

	void setMaterialsList(std::vector<Material*> materials);

	void setAssociatedMaterialsList(std::vector<Material*> materials);


	/*
	* Check if a project has been released or not
	* Check against local time
	*/
	const bool isReleased(Project* project);

private: // Functions


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
	 * Display a message and continue to get user inputs and add to a vector until the user is satisifed
	 */
	const std::vector<std::string> messageReturnUserVector(const std::string& message, const bool canBeNull = false);

	/*
	 * Display a message and continue to get user inputs and add to a vector until the user is satisifed
	 * returns vector of ints, used for ticket sales
	 */
	const std::vector<int> messageReturnUserVectorInt(const std::string& message);

	/*
	 * Ask the user a yes no question and convert their answer to a bool
	 * yes : true
	 * no  : false
	 */
	const bool yesNoBool(const std::string & message);

	/*
	 * Converts a string to all lower case
	 */
	std::string toLower(std::string &input);

};

#endif // !PROJECTMANAGER_H
