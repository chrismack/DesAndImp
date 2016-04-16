#pragma once

#include <vector>
#include <string>

#include "BlueRay.h"
#include "SingleDVD.h"
#include "DoubleDVD.h"
#include "ComboBox.h"
#include "VHS.h"
#include "Project.h"

#include "MaterialFactory.h"

#include <iostream>
#include <fstream>

#include <sstream>

class CSVHandler
{
private:
	/*
	 * File name to write strings to
	 */
	std::string fileName_;
	/*
	 * Line from the file
	 */
	std::vector<std::string> lines_;

	/*
	 * Split string into vector around specified delemeters
	 */
	std::vector<std::string> split(std::string line, std::string del);

	/*
	 * List of materials that have been loaded
	 */
	std::vector<Material*> materials_;

	/*
	 * List of projects that have been loaded from the file
	 */
	//std::vector<Project*> projects_;
	std::map<Project*, bool> projects_;

	/*
	 * Create classes from specified string and type
	 */
	void generate(std::string string, std::string type);

	/*
	 * read the content from the specified file and load them into lines_
	 */
	void readLinesFromFile(std::string fileName);

	/*
	 * Write line into specified file
	 */
	void addLineToFile(const std::string fileName, const std::string line);

	MaterialFactory* factory_;

public:
	
	static CSVHandler* INSTANCE;
	
	CSVHandler(std::string fileName, MaterialFactory* factory);
	~CSVHandler();

	/*
	 * Singleton instance of handler class
	 */
	static CSVHandler* getCVSInstance();

	/*
	 * get instance of lines_
	 */
	std::vector<std::string> getLines();

	/*
	 * Read and generate classes lines_
	 */
	void generateClassesFromLines();

	/*
	 * generate classes from string
	 */
	void generateClassFromLine(const std::string line);

	/*
	 * Write material classes to the file
	 */
	void writeToFile(Material* material);

	/*
	 * Write Project classes to the file
	 */
	void writeToFile(Project* project, bool nowPlaying);

	/*
	 * read file and generate only materials
	 */
	std::vector<Material*> getMaterialsFromFile();

	/*
	 * read file and generate only projects
	 */
	std::map<Project*, bool> getProjectsFromFile();

	/*
	 * return materials_
	 */
	std::vector<Material*> getMaterials();
	/*
	 * return projects_
	 */
	std::map<Project*, bool> getProjects();

};

