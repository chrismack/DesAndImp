#pragma once
#include "tinyxml2.h"

#include "MaterialFactory.h"
#include "Project.h"
#include "Material.h"

#include <string>
#include <map>

class XMLHandler
{
private:
	const char * fileName;
	MaterialFactory* materialfactory;

	std::map<Project*, bool> projects_;
	std::vector<Material*> materials_;

public:
	XMLHandler(const char * filename, MaterialFactory* materialFactory);
	~XMLHandler();

	std::vector<Material*> getMaterialsFromFile();
	std::map<Project*, bool> getProjectsFromFile();

	std::vector<Material*> getMaterials();
	std::map<Project*, bool> getProjects();
};

