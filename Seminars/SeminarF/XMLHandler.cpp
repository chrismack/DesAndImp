#include "stdafx.h"
#include "XMLHandler.h"


using namespace tinyxml2;

XMLHandler::XMLHandler(const char * fileName, MaterialFactory* materialFactory)
{

	this->fileName = fileName;
	this->materialfactory = materialFactory;

	XMLDocument document;
	document.Parse(fileName);
	XMLElement* titleElement = document.FirstChildElement("poetry")->FirstChildElement("verse");
}


XMLHandler::~XMLHandler()
{
}

std::map<Project*, bool> XMLHandler::getProjects()
{
	return projects_;
}

std::map<Project*, bool> XMLHandler::getProjectsFromFile()
{
	return projects_;
}

std::vector<Material*> XMLHandler::getMaterials()
{
	return this->materials_;
}

std::vector<Material*> XMLHandler::getMaterialsFromFile()
{
	return this->materials_;
}