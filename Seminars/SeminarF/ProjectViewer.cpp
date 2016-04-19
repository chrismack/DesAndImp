#ifndef PROJECTVIEWER_CPP
#define PROJECTVIEWER_CPP


#include "stdafx.h"
#include "ProjectViewer.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

ProjectViewer::ProjectViewer()
{
}


ProjectViewer::~ProjectViewer()
{
}

void ProjectViewer::displayMessage(const std::string & message, const bool newLine /* true*/)
{
	if (newLine)
	{
		std::cout << message << std::endl;
	}
	else
	{
		std::cout << message;
	}
}

/*
* Display menu options on screen
*/
void ProjectViewer::displayMenuOptions()
{
	std::cout << "			MENU			      " << std::endl;
	std::cout << "0)exit   : leave the application" << std::endl;		// Leave applicatoin
	std::cout << "1)import : Import from file" << std::endl;		// Import materials from files
	std::cout << "2)save   : Save to file" << std::endl;		// Save material strings to file
	std::cout << "3)view   : View data" << std::endl;		// View Materials and projects currently stored in memory
	std::cout << "4)create : Create Material or Proj" << std::endl;
	std::cout << "5)search : Search for linked media" << std::endl;
	std::cout << "6)delete : Delete project or material" << std::endl;
	std::cout << std::endl;
}

/*
* Display options for viewing materials loaded into memory
*/
void ProjectViewer::displayViewOptions()
{
	std::cout << "What would you like to view?" << std::endl << "1)Projects or 2)Materials" << std::endl;;
	std::cout << "Please enter you choice" << std::endl;
}

void ProjectViewer::displayCreateMenu()
{
	std::cout << "What operation would you like to complete?" << std::endl;
	std::cout << "1) Create Project" << std::endl;		// Create a project and add to projects_
	std::cout << "2) Create Material" << std::endl;		// Create a material and add to materials_
	std::cout << "3) Link Media" << std::endl;		// Display linking menu

	std::cout << "Please enter your option : " << std::endl;
}

void ProjectViewer::displayDeleteMenu()
{
	std::cout << "Please select an option to delete" << std::endl;
	std::cout << "1)Delete Project" << std::endl;
	std::cout << "2)Delete Material" << std::endl;
}

void ProjectViewer::displaySearchMenu()
{
	std::cout << std::endl;
	std::cout << "Please select a seach option" << std::endl;
	std::cout << "1)Find materials associated with project" << std::endl;
	std::cout << "2)Find project associated with material" << std::endl;
}

void ProjectViewer::clearScreen()
{
	system("cls");
}

void ProjectViewer::viewFullMaterial(Material * material)
{
	std::vector<std::string> materialElements = material->toArray();

	std::stringstream ss;

	for (std::string element : materialElements)
	{
		ss << element << " :: ";
	}

	displayMessage(ss.str());
}

void ProjectViewer::viewFullProject( Project * project)
{
	std::vector<std::string> projElements = project->toArray();
	std::stringstream ss;
	for (std::string element : projElements)
	{
		ss << element << " :: ";
	}
	displayMessage(ss.str());
}

void ProjectViewer::displayPartialProject(Project * project)
{

}

void ProjectViewer::displayPartialMaterial(Material * material)
{
	std::cout << "TITLE : " + material->getFilmTitle() + "   ";
	std::cout << "FORMAT : " + material->getFormat() + "   ";
	std::cout << "LANGIAGE : " + material->getLanguage() + "   " << std::endl;
}

void ProjectViewer::allMaterials(std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials)
{
	for (Material* material : allMaterials.first)
	{
		if (material != nullptr);
		std::cout << std::to_string(material->getId()) + " : " + material->getFilmTitle() << std::endl;
	}

	for (Material* material : allMaterials.second)
	{
		if (material != nullptr);
		std::cout << std::to_string(material->getId()) + " : " + material->getFilmTitle() + "Associated with project" << std::endl;
	}
}

void ProjectViewer::allProjects(std::map<Project*, bool> projects)
{
	std::map<Project*, bool>::iterator it;
	for (it = projects.begin(); it != projects.end(); ++it)
	{
		std::cout << it->first->getTitle() << std::endl;
	}
}

void ProjectViewer::displayProjects(std::vector<Project*> projects)
{
	for (Project* proj : projects)
	{
		std::cout << "TILTE: " + proj->getTitle() + " SUMMARY:" + proj->getSummary() << std::endl;
	}
}

#endif 