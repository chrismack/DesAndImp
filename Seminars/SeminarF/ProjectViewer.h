#pragma once
#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#include "Material.h"
#include "Project.h"

#include <string>

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
	* Print the display menu to the screen
	*/
	void displaySearchMenu();

	void clearScreen();

	void viewFullMaterial(Material* material);
	void viewFullProject(Project* project);
};

#endif // !PROJECTVIEWER_H
