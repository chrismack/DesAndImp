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
	std::string fileName;
	MaterialFactory* materialfactory;

	std::map<Project*, bool> projects_;
	std::vector<Material*> materials_;

	std::map<Project*, bool> readProjectsFromFile();
	std::vector<Material*> readMaterialsFromFile();
	std::string processMaterialTag(tinyxml2::XMLElement* rootMaterials);

	std::vector<std::string> split(std::string string, std::string del);

	void write(std::vector <std::string>);

	void writeBaseMaterial(std::vector<std::string> elements, tinyxml2::XMLElement* parent, tinyxml2::XMLDocument* doc);

	void writeProject(std::vector <std::string> elements, tinyxml2::XMLDocument* doc);
	void writeSingleDisc(std::vector<std::string> elements, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent = nullptr);
	void writeVHS(std::vector<std::string> elements, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent = nullptr);
	void writeCombo(std::vector<std::string> elements, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent = nullptr);
	void writeDouble(std::vector<std::string> elements, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent = nullptr);

	void writeComboMaterial(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent, std::string elementName, std::string value);

	void insertElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent, std::string elementName, std::string value);
	void insertVectorElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent, std::string elementName, std::string value);
	void insertMapElement(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent, std::string elementName, std::string value);

	void writeProjectMaterials(tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent, std::string elementName, std::string value);
public:
	XMLHandler(std::string fileName, MaterialFactory* materialFactory);
	~XMLHandler();

	std::vector<Material*> getMaterialsFromFile();
	std::map<Project*, bool> getProjectsFromFile();

	std::vector<Material*> getMaterials();
	std::map<Project*, bool> getProjects();

	void writeToFile(Project*, bool);
	void writeToFile(Material*);
};

