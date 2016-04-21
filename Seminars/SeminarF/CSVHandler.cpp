#define _CRT_SECURE_NO_WARNINGS // Used for strtok doesn't compile with out

#include "stdafx.h"
#include "CSVHandler.h"



CSVHandler* CSVHandler::INSTANCE;

CSVHandler::CSVHandler(std::string fileName, MaterialFactory* factory)
{
	INSTANCE = this;
	this->fileName_ = fileName;
	this->factory_ = factory;
}


CSVHandler::~CSVHandler()
{
}

CSVHandler* CSVHandler::getCVSInstance()
{
	if (CSVHandler::INSTANCE == nullptr)
	{
		CSVHandler::INSTANCE = new CSVHandler("default.csv", new MaterialFactory());
	}
	return CSVHandler::INSTANCE;
}

void CSVHandler::readLinesFromFile(std::string fileName)
{
	std::string line;
	std::ifstream cvsFile(fileName);
	if (!cvsFile.is_open())
	{
		cvsFile.open(fileName_);
	}
	while (std::getline(cvsFile, line))
	{
		lines_.push_back(line);
	}
	cvsFile.close();
}

std::vector<std::string> CSVHandler::getLines()
{
	return lines_;
}

void CSVHandler::addLineToFile(std::string fileName, std::string line)
{
	std::ofstream cvsFile(fileName, std::ofstream::app | std::ofstream::out);
	
	if (!cvsFile.is_open())
	{
		cvsFile.open(fileName_, std::ofstream::app | std::ofstream::out);
	}
	cvsFile << line << std::endl;
	cvsFile.close();
}

void CSVHandler::generateClassesFromLines()
{
	for (int i = 0; i < lines_.size(); i++)
	{
		std::string type = split(lines_[i], ",")[2];
		generate(lines_[i], type);
	}
}

void CSVHandler::generateClassFromLine(std::string line)
{
	std::string type = split(line, ",")[2];
	generate(line, type);
}

void CSVHandler::writeToFile(Material* material)
{
	std::vector<std::string> materialArray = material->toArray();
	std::stringstream ss;
	for (int i = 0; i < materialArray.size(); i++)
	{
		ss << materialArray[i];
		if (i < materialArray.size() - 1)
		{
			ss << ",";
		}
	}

	addLineToFile(fileName_, ss.str());
	
}

void CSVHandler::writeToFile(Project* project, bool nowPlaying)
{
	
}

std::vector<Material*> CSVHandler::getMaterialsFromFile()
{
	readLinesFromFile(fileName_);
	generateClassesFromLines();
	return this->materials_;
}

std::map<Project*, bool> CSVHandler::getProjectsFromFile()
{
	readLinesFromFile(fileName_);
	generateClassesFromLines();
	return this->projects_;
}

std::vector<Material*> CSVHandler::getMaterials()
{
	return this->materials_;
}

std::map<Project*, bool> CSVHandler::getProjects()
{
	return this->projects_;
}


void CSVHandler::generate(std::string string, std::string type)
{
	if (type == "BluRay" || type == "SingleDVD" || type == "DoubleDVD" || type == "Combo" || type == "VHS")
	{
		materials_.push_back(factory_->createMaterial(type, string));
	}
	else //Project
	{
		std::string nowPlayingString = string.substr(string.find_last_of(",") + 1);
		string = string.substr(0, string.find_last_of(",") + 1);
		bool nowPlaying = nowPlayingString == "true" ? true : false;
		projects_.insert(std::pair<Project*, bool>(factory_->createProject(string), nowPlaying));
		//projects_.push_back(factory_->createProject(string));
	}

}

std::vector<std::string> CSVHandler::split(std::string string, std::string del)
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
