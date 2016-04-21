#pragma once
#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#include "Material.h"
#include "Project.h"

#include <string>
#include <map>

class ProjectViewer
{
public:
	ProjectViewer();
	~ProjectViewer();

	void displayMessage(const std::string & message, const bool newLine = true);

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
	* Display the create menu sub options
	* displayed when option 4(create) from menu is selected
	*/
	void displayCreateMenu();

	/*
	 * Display delete options
	 */
	void displayDeleteMenu();

	/*
	* Print the display menu to the screen
	*/
	void displaySearchMenu();

	void displayEditMenu();

	void displayBrowseMenu();

	void displayProjectFieldsToEdit();

	void displayInteractiveSearchMenu();

	void displayMaterialFieldsToEdit(Material* material);

	void clearScreen();

	void viewFullMaterial(Material* material);
	void viewFullProject(Project* project);

	void displayPartialProject(Project* project);
	void displayPartialMaterial(Material* material);

	void displayMaterialVector(std::vector<Material*> materials);

	void allMaterials(std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials);

	void allProjects(std::map<Project*, bool> projects);

	void displayProjects(std::vector<Project*> projects);

	void displayProjectMap(std::map<Project*, bool> projects);

	std::string toLower(std::string & input);
	
};

#endif // !PROJECTVIEWER_H
