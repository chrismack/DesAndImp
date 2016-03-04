#pragma once

#include <vector>
#include <string>

#include "BlueRay.h"
#include "SingleDVD.h"
#include "DoubleDVD.h"
#include "ComboBox.h"
#include "VHS.h"
#include "Project.h"

#include <iostream>
#include <fstream>

#include <sstream>

class CSVHandler
{
private:
	std::string fileName_;
	std::vector<std::string> lines_;
	std::vector<std::string> split(std::string line, std::string del);

	std::vector<Material*> materials_;
	std::vector<Project*> projects_;

	void generate(std::string string, std::string type);
	void readLinesFromFile(std::string fileName);
	void addLineToFile(const std::string fileName, const std::string line);

public:
	
	static CSVHandler* INSTANCE;
	
	CSVHandler(std::string fileName);
	~CSVHandler();

	static CSVHandler* getCVSInstance();

	std::vector<std::string> getLines();

	void generateClassesFromLines();
	void generateClassFromLine(const std::string line);

	void writeToFile(Material* material);
	void writeToFile(Project* project);

	std::vector<Material*> getMaterialsFromFile();
	std::vector<Project*> getProjectsFromFile();

	std::vector<Material*> getMaterials();
	std::vector<Project*> getProjects();

};

