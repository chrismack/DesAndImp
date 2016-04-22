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
	std::cout << "7)edit   : Edit project or material" << std::endl;
	std::cout << "8)browse : Browse project or material" << std::endl;
	std::cout << "9)interactive : Search interactivly for projects" << std::endl;
	std::cout << std::endl;
}

/*
* Display options for viewing materials loaded into memory
*/
void ProjectViewer::displayViewOptions()
{
	std::cout << std::endl;
	std::cout << "What would you like to view?" << std::endl << "1)Projects or 2)Materials" << std::endl;;
	std::cout << "Please enter you choice" << std::endl;
}

void ProjectViewer::displayCreateMenu()
{
	std::cout << std::endl;
	std::cout << "What operation would you like to complete?" << std::endl;
	std::cout << "1) Create Project" << std::endl;		// Create a project and add to projects_
	std::cout << "2) Create Material" << std::endl;		// Create a material and add to materials_
	std::cout << "3) Link Media" << std::endl;		// Display linking menu

	std::cout << "Please enter your option : " << std::endl;
}

void ProjectViewer::displayDeleteMenu()
{
	std::cout << std::endl;
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

void ProjectViewer::displayEditMenu()
{
	std::cout << std::endl;
	std::cout << "Please select a edit option" << std::endl;
	std::cout << "1)Edit Proejct" << std::endl;
	std::cout << "2)Edit Material" << std::endl;
}

void ProjectViewer::displayBrowseMenu()
{
	std::cout << std::endl;
	std::cout << "Browse Menu" << std::endl;
	std::cout << "Use < and > to go previous or next" << std::endl;
	std::cout << "Would you like to view    1)Projects or 2)Materials" << std::endl;
}

void ProjectViewer::displayProjectFieldsToEdit()
{
	std::cout << std::endl;
	std::cout << "Project fields : " << std::endl;
	std::cout << "1)Title" << std::endl;
	std::cout << "2)Summary" << std::endl;
	std::cout << "3)Genre" << std::endl;
	std::cout << "4)ReleaseDate" << std::endl;
	std::cout << "5)Filming locations" << std::endl;
	std::cout << "6)key words" << std::endl;
	std::cout << "7)Ticket Sales" << std::endl;
	std::cout << "8)Add a ticket sales week" << std::endl;
	std::cout << "9)Crew" << std::endl;
}

void ProjectViewer::displayInteractiveSearchMenu()
{
	std::cout << std::endl;
	std::cout << "Project fields : " << std::endl;
	std::cout << "1)Title" << std::endl;
	std::cout << "2)Summary" << std::endl;
	std::cout << "3)Genre" << std::endl;
	std::cout << "4)ReleaseDate" << std::endl;
	std::cout << "5)Filming locations" << std::endl;
	std::cout << "6)key words" << std::endl;
	std::cout << "7)Crew" << std::endl;
	std::cout << "8)Material Format" << std::endl;
}

void ProjectViewer::displayMaterialFieldsToEdit(Material * material)
{
	std::cout << std::endl;
	std::cout << "1)Title" << std::endl;
	std::cout << "2)AudioFormat" << std::endl;
	std::cout << "3)runTime" << std::endl;
	std::cout << "4)Language" << std::endl;
	std::cout << "5)RetailPrice" << std::endl;
	std::cout << "6)Subtitles" << std::endl;
	std::cout << "7)Aspect Ratio" << std::endl;
	std::cout << "8)Set Content" << std::endl;

	if (toLower(material->getFormat()) == "bluray")
	{
		std::cout << "9)Bonus Features" << std::endl;
		std::cout << "10)Audio Tracks" << std::endl;
		std::cout << "11)Language Tracks" << std::endl;
		std::cout << "12)Subtitle Track" << std::endl;
	}
	else if (toLower(material->getFormat()) == "singledvd")
	{
		std::cout << "9)Bonus Features" << std::endl;
		std::cout << "10)Audio Tracks" << std::endl;
		std::cout << "11)Language Tracks" << std::endl;
		std::cout << "12)Subtitle Track" << std::endl;

	}
	else if (toLower(material->getFormat()) == "doubledvd")
	{
		std::cout << "9)Bonus Features" << std::endl;
		std::cout << "10)Audio Tracks" << std::endl;
		std::cout << "11)Language Tracks" << std::endl;
		std::cout << "12)Subtitle Track" << std::endl;

	}
	else if (toLower(material->getFormat()) == "vhs")
	{
		std::cout << "9)Language Track" << std::endl;
		std::cout << "10)Audio Track" << std::endl;
	}
}

void ProjectViewer::clearScreen()
{
	system("cls");
}

void ProjectViewer::viewAllBaseMaterial(Material * material)
{
	std::cout << "TITLE: " << material->getFilmTitle() << "  ";
	std::cout << "FORMAT: " << material->getFormat() << "  ";
	std::cout << "AUDIOFORMAT: " << material->getAudioFormat() << "  ";
	std::cout << "RUNTIME: " << std::to_string(material->getRunTime()) << "  ";
	std::cout << "LANGUAGE: " << material->getLanguage() << "  ";
	std::cout << "RETAILPRICE: " << std::to_string(material->getRetailPrice()) << "  ";
	std::cout << "SUBTITLES: " << material->getSubtitles() << "  ";
	std::cout << "ASPECT RATIO: " << material->getAspectRatio().first << ":" << material->getAspectRatio().second << "  ";
}

void ProjectViewer::viewFullBlu(BlueRay * blu)
{
	viewAllBaseMaterial(blu);
	
	std::stringstream ss;
	for (std::string str : blu->getLanguagetracks())
	{
		ss << str << "|";
	}
	std::cout << "LANGUAGE TRACKS: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : blu->getsubtitleTracks())
	{
		ss << str << "|";
	}
	std::cout << "SUBTITLE TRACKS: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : blu->getAudioTracks())
	{
		ss << str << "|";
	}
	std::cout << "AUDIO TRACKS: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : blu->getContent())
	{
		ss << str << "|";
	}
	std::cout << "CONTENT: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : blu->getBonusFeatures())
	{
		ss << str << "|";
	}
	std::cout << "BONUS FEATURES: " << ss.str() << "  ";

	std::cout << "PACKAGE TYPE: " << blu->getPackageType() << "  ";

	std::string packageDimString = std::to_string(std::get<0>(blu->getPackageSize()))
		.append("|")
		.append(std::to_string(std::get<0>(blu->getPackageSize())))
		.append("|")
		.append(std::to_string(std::get<0>(blu->getPackageSize())));

	std::cout << "PACKAGE SIZE: " << packageDimString << std::endl;
}

void ProjectViewer::viewFullDVD(SingleDVD * dvd)
{
	viewAllBaseMaterial(dvd);
	std::stringstream ss;
	for (std::string str : dvd->getLanguagetracks())
	{
		ss << str << "|";
	}
	std::cout << "LANGUAGE TRACKS: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : dvd->getsubtitleTracks())
	{
		ss << str << "|";
	}
	std::cout << "SUBTITLE TRACKS: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : dvd->getAudioTracks())
	{
		ss << str << "|";
	}
	std::cout << "AUDIO TRACKS: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : dvd->getContent())
	{
		ss << str << "|";
	}
	std::cout << "CONTENT: " << ss.str() << "  ";

	ss.clear();
	for (std::string str : dvd->getBonusFeatures())
	{
		ss << str << "|";
	}
	std::cout << "BONUS FEATURES: " << ss.str() << "  ";

	std::cout << "PACKAGE TYPE: " << dvd->getPackageType() << "  ";

	std::string packageDimString = std::to_string(std::get<0>(dvd->getPackageSize()))
		.append("|")
		.append(std::to_string(std::get<0>(dvd->getPackageSize())))
		.append("|")
		.append(std::to_string(std::get<0>(dvd->getPackageSize())));

	std::cout << "PACKAGE SIZE: " << packageDimString << std::endl;
}

void ProjectViewer::viewFullDouble(DoubleDVD * dvd)
{
	viewAllBaseMaterial(dvd);
	
	std::stringstream ss;
	std::map<int, std::vector<std::string>>::iterator it;
	std::cout << "LANGUAGE TRACKS: ";
	for (it = dvd->getLanguagetracks().begin(); it != dvd->getLanguagetracks().end(); ++it)
	{
		std::cout << "side: " << std::to_string(it->first) << " ";
		for (std::string str : it->second)
		{
			ss << str << "|";
		}
		std::cout << ss.str();
	}

	ss.clear();
	std::cout << "SUBTITLE TRACKS: ";
	for (it = dvd->getsubtitleTracks().begin(); it != dvd->getsubtitleTracks().end(); ++it)
	{
		std::cout << "side: " << std::to_string(it->first) << " ";
		for (std::string str : it->second)
		{
			ss << str << "|";
		}
		std::cout << ss.str();
	}

	ss.clear();
	std::cout << "AUDIO TRACKS: ";
	for (it = dvd->getAudioTracks().begin(); it != dvd->getAudioTracks().end(); ++it)
	{
		std::cout << "side: " << std::to_string(it->first) << " ";
		for (std::string str : it->second)
		{
			ss << str << "|";
		}
		std::cout << ss.str();
	}

	ss.clear();
	std::cout << "CONTENT: ";
	for (it = dvd->getAllContent().begin(); it != dvd->getAllContent().end(); ++it)
	{
		std::cout << "side: " << std::to_string(it->first) << " ";
		for (std::string str : it->second)
		{
			ss << str << "|";
		}
		std::cout << ss.str();
	}

	ss.clear();
	std::cout << "BONUS: ";
	for (it = dvd->getBonusFeatures().begin(); it != dvd->getBonusFeatures().end(); ++it)
	{
		std::cout << "side: " << std::to_string(it->first) << " ";
		for (std::string str : it->second)
		{
			ss << str << "|";
		}
		std::cout << ss.str();
	}

	std::cout << "PACKAGE TYPE: " << dvd->getPackageType() << "  ";

	std::string packageDimString = std::to_string(std::get<0>(dvd->getPackageSize()))
		.append("|")
		.append(std::to_string(std::get<0>(dvd->getPackageSize())))
		.append("|")
		.append(std::to_string(std::get<0>(dvd->getPackageSize())));

	std::cout << "PACKAGE SIZE: " << packageDimString << std::endl;
}

void ProjectViewer::viewFullCombo(ComboBox * combo)
{
	viewAllBaseMaterial(combo);

	std::cout << "MATERIALS: " << std::endl;
	for (Material* mat : combo->getContent())
	{
		std::string format = toLower(mat->getFormat());

		if (format == "bluray")
		{
			viewFullBlu((BlueRay*)mat);
		}
		else if (format == "singledvd")
		{
			viewFullDVD((SingleDVD*)mat);
		}
		else if (format == "doubledvd")
		{
			viewFullDouble((DoubleDVD*)mat);
		}
		else if (format == "vhs")
		{
			viewFullVHS((VHS*)mat);
		}
	}

	std::cout << "PACKAGE TYPE: " << combo->getPackageType() << "  ";

	std::string packageDimString = std::to_string(std::get<0>(combo->getPackageSize()))
		.append("|")
		.append(std::to_string(std::get<0>(combo->getPackageSize())))
		.append("|")
		.append(std::to_string(std::get<0>(combo->getPackageSize())));

	std::cout << "PACKAGE SIZE: " << packageDimString << std::endl;
}

void ProjectViewer::viewFullVHS(VHS * vhs)
{
	viewAllBaseMaterial(vhs);
	
	std::cout << "LANGUAGE TRACK: " << vhs->getLanguageTrack() << "  ";

	std::cout << "AUDIO TRACK: " << vhs->getAudioTrack() << "  ";

	std::stringstream ss;
	for (std::string str : vhs->getContent())
	{
		ss << str << "|";
	}
	std::cout << "CONTENT: " << ss.str() << "  ";

	std::cout << "PACKAGE TYPE: " << vhs->getPackageType() << "  ";

	std::string packageDimString = std::to_string(std::get<0>(vhs->getPackageSize()))
		.append("|")
		.append(std::to_string(std::get<0>(vhs->getPackageSize())))
		.append("|")
		.append(std::to_string(std::get<0>(vhs->getPackageSize())));

	std::cout << "PACKAGE SIZE: " << packageDimString << std::endl;
}

void ProjectViewer::viewFullMaterial(Material * material)
{
	std::string format = toLower(material->getFormat());

	if (format == "bluray")
	{
		viewFullBlu((BlueRay*)material);
	}
	else if (format == "singledvd")
	{
		viewFullDVD((SingleDVD*)material);
	}
	else if (format == "doubledvd")
	{
		viewFullDouble((DoubleDVD*)material);
	}
	else if (format == "combo")
	{
		viewFullCombo((ComboBox*)material);
	}
	else if (format == "vhs")
	{
		viewFullVHS((VHS*)material);
	}
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
	std::cout << std::endl;
	std::cout << "TITLE : " + project->getTitle()+ "   ";
	std::cout << "SUMMARY : " + project->getSummary() + "   ";
	std::cout << "GENRE : " + project->getGenre() + "   " << std::endl;
}

void ProjectViewer::displayPartialMaterial(Material * material)
{
	std::cout << std::endl;
	std::cout << "TITLE : " + material->getFilmTitle() + "   ";
	std::cout << "FORMAT : " + material->getFormat() + "   ";
	std::cout << "LANGIAGE : " + material->getLanguage() + "   " << std::endl;
}

void ProjectViewer::allMaterials(std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials)
{
	std::cout << std::endl;
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
	std::cout << std::endl;
	std::map<Project*, bool>::iterator it;
	for (it = projects.begin(); it != projects.end(); ++it)
	{
		std::cout << "TITLE:" << it->first->getTitle() << " SUMMARY: " << it->first->getSummary() << "  GENRE: " << it->first->getGenre() << std::endl;
		std::cout << "Avaliable on : ";

		std::stringstream ss;
		for (Material* material : it->first->getMaterials())
		{
			ss << material->getFormat() << " And ";
		}
		std::cout << ss.str().substr(0, ss.str().length() - 4) << std::endl;
	}
}

void ProjectViewer::displayProjects(std::vector<Project*> projects)
{
	std::cout << std::endl;
	for (Project* proj : projects)
	{
		std::cout << "TILTE: " + proj->getTitle() + " SUMMARY:" + proj->getSummary() << std::endl;
	}
}

void ProjectViewer::displayMaterialVector(std::vector<Material*> materials)
{
	std::cout << std::endl;
	std::cout << "ID :	TITLE : FORMAT" << std::endl;
	for (Material* mat : materials)
	{
		if (mat != nullptr)
		{
			std::cout << std::to_string(mat->getId()) + " : " + mat->getFilmTitle() + " : " + mat->getFormat() << std::endl;
		}
	}
}

void ProjectViewer::displayProjectMap(std::map<Project*, bool> projects)
{
	std::cout << std::endl;
	int index = 0;
	std::map<Project*, bool>::iterator it;
	for (it = projects.begin(); it != projects.end(); ++it)
	{
		std::cout << std::to_string(index) + " : " + it->first->getTitle() + " : " + it->first->getSummary() + " : " + it->first->getGenre() << std::endl;
		index++;
	}
}

std::string ProjectViewer::toLower(std::string & input)
{
	std::cout << std::endl;
	for (int i = 0; i < input.length(); i++)
	{
		input[i] = tolower(input[i]);
	}
	return input;
}

#endif 