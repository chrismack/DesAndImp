#ifndef MATERIALFACTORY_CPP
#define MATERIALFACTORY_CPP

#define _CRT_SECURE_NO_WARNINGS // Used for strtok doesn't compile with out


#include "stdafx.h"
#include "MaterialFactory.h"

#include "BlueRay.h"
#include "SingleDVD.h"
#include "DoubleDVD.h"
#include "ComboBox.h"
#include "VHS.h"
#include "Project.h"

MaterialFactory::MaterialFactory()
{
}


MaterialFactory::~MaterialFactory()
{
}

Material * MaterialFactory::createMaterial(std::string type, std::string data)
{
	Material* mat = nullptr;
	
	std::vector<std::string> tmpLine = split(data, ",");

	if (type == "BluRay")
	{
		mat = new BlueRay;
	}
	else if (type == "SingleDVD")
	{
		mat = new SingleDVD;
	}
	else if (type == "DoubleDVD")
	{
		mat = new DoubleDVD;
	}
	else if (type == "Combo")
	{
		mat = new ComboBox;
		std::string dvds = data.substr(data.find('['), data.length());
		data = data.substr(0, data.find('['));
		data.append(dvds);
		tmpLine = split(data, ",");
	}
	else if (type == "VHS")
	{
		mat = new VHS;
	}
	else //Project
	{
		return nullptr;
	}

	if (mat != nullptr)
	{
		mat->populate(tmpLine);
	}
}

Project * MaterialFactory::createProject(std::string data)
{
	std::vector<std::string> tmpLine = split(data, ",");
	Project* project = new Project();
	project->populate(tmpLine);
	return project;
}

std::vector<std::string> MaterialFactory::split(std::string string, std::string del)
{

	/* http://stackoverflow.com/questions/16286095/similar-function-to-javas-string-split-in-c */

	char* cstr = const_cast<char*>(string.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, del.c_str());
	while (current != NULL)
	{
		arr.push_back(current);
		current = strtok(NULL, del.c_str());
	}

	return arr;
}

#endif // !MATERIALFACTORY_CPP
