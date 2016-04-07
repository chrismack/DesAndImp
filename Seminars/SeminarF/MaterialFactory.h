#pragma once

#ifndef MATERIALFACTORY_H
#define MATERIALFACTORY_H

#include <string>
#include <vector>

#include "Material.h"
#include "Project.h"

class MaterialFactory
{
private:
	/*
	* Split string into vector around specified delemeters
	*/
	std::vector<std::string> split(std::string line, std::string del);

public:
	MaterialFactory();
	~MaterialFactory();

	Material* createMaterial(std::string type, std::string data);
	Project* createProject(std::string data);
};

#endif // !MATERIALFACTORY_H
