#pragma once
#include <string>

#include "ProjectManager.h"

class ProjectViewer
{
private:
	ProjectManager* projectManager;
public:
	ProjectViewer(ProjectManager* projectManager);
	~ProjectViewer();

	void displayMessage(const std::string & message);

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
};

