#pragma once
#include "Material.h"
#include "IPackagable.h"
#include "Disc.h"

#include "ProjectViewer.h"

#include <map>

class MaterialFactoryUserCreate
{

private :
	ProjectViewer* projectViewer;

	int newMaterials = 0;

public:
	MaterialFactoryUserCreate(ProjectViewer* projectViewer);
	~MaterialFactoryUserCreate();

	Material* userInsertIntoMaterial(int materialCount, std::vector<Disc*>, const bool mustBeDisc = false);

	Project* createProject();


	int getNewMaterialCount();

	/*
	* Set package attributes for a material
	*/
	void setMaterialPackage(IPackagable* material);

private: /* function */

	void userInsertBaseMaterials(Material* material, const std::string& type, int materialCount);

		 /*
		 * Display a message and get a non null user input
		 */
	const std::string messageReturnInput(const std::string& message);

	/*
	* Display a message to the user
	* Get their input and put their input
	*/
	std::map<int, std::vector<std::string>> setVectorSideMap(const std::string & message);

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
	* Converts a string to all lower case
	*/
	std::string toLower(std::string &input);

	/*
	* Get input from the user
	*
	* Return std::cin (what they have entered)
	*/
	std::string getUserInput();

	/*
	* prints message to display
	* gets a list of materials defined by the users
	* Presents user with list of materials loaded into memory for them to select from
	*/
	std::vector<Disc*> getDiscMaterialsFromUser(int materialCount, const std::string& message, std::vector<Disc*> discs);

	const bool yesNoBool(const std::string & message);

	const long MaterialFactoryUserCreate::messageGetDate(const std::string & message);

};

