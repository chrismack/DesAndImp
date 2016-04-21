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
	std::string defaultSavePath = "test.xml";

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

	std::vector<Project*> materialFindProject(Material* material);

	void deleteProject(Project* project);
	
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

	void deleteMaterial(std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials, int id);

	Material* getMaterialFromId(int id);

	std::vector<Project*> findProjects(std::map<int, std::string> searchCritera);


	/*
	* Check if a project has been released or not
	* Check against local time
	*/
	const bool isReleased(Project* project);

private: // Functions

	/*
	 * Process and import data that has been formatted in CSV
	 */
	void importCSV(const std::string &CSV);

	void importXML(const std::string &XML);

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
