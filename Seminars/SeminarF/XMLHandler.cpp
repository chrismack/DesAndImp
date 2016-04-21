#define _CRT_SECURE_NO_WARNINGS // Used for strtok doesn't compile with out

#include "stdafx.h"
#include "XMLHandler.h"

#include <sstream>


using namespace tinyxml2;


XMLHandler::XMLHandler(std::string fileName, MaterialFactory* materialFactory)
{

	this->fileName = fileName;
	this->materialfactory = materialFactory;
	/*std::string dvd = "0,213,DoubleDVD,12,3123,123,123.000000,123,123:23,23134-123,123- ,324324-123123, ,0|0|0,123|123|123|123- ,-12312|123|123";
	std::vector<std::string> dvdV = split(dvd, ",");
	write(dvdV);*/
}


XMLHandler::~XMLHandler()
{
}

std::map<Project*, bool> XMLHandler::getProjects()
{
	return projects_;
}

void XMLHandler::writeToFile(Project * project, bool nowPlaying)
{
	std::vector<std::string> projectArray = project->toArray();
	projectArray.push_back(nowPlaying ? "true" : "false");
	
	write(projectArray);
}

void XMLHandler::writeToFile(Material * material)
{
	write(material->toArray());
}

std::map<Project*, bool> XMLHandler::getProjectsFromFile()
{
	readProjectsFromFile();
	return projects_;
}

std::vector<Material*> XMLHandler::getMaterials()
{
	return this->materials_;
}

std::vector<Material*> XMLHandler::getMaterialsFromFile()
{
	readMaterialsFromFile();
	return this->materials_;
}

std::map<Project*, bool> XMLHandler::readProjectsFromFile()
{
	std::map<Project*, bool> fileProjects;

	XMLDocument doc;
	doc.LoadFile("test.xml");

	if (doc.ErrorID() == 0)
	{
		std::stringstream ss;

		XMLElement* root = doc.FirstChildElement("media");

		for (XMLElement* projects = root->FirstChildElement("projects"); projects != NULL; projects = projects->NextSiblingElement("projects"))			//Get projects
		{
			std::string v1 = projects->Value();
			for (XMLElement* project = projects->FirstChildElement("project"); project != NULL; project = project->NextSiblingElement("project"))
			{
				std::string v2 = project->Value();

				for (XMLElement* element = project->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
				{

					bool att = element->Attribute("vector");
					std::string elementValue = element->Value();
					bool mat = elementValue == "materials";
					if (att)
					{
						for (XMLElement* item = element->FirstChildElement("item"); item != NULL; item = item->NextSiblingElement("item"))
						{
							if (item->GetText())
							{
								std::string items = item->GetText();
								bool isLast = item->NextSiblingElement("item") == nullptr;
								ss << items << (isLast ? "" : "|");
							}
							else
							{
								ss << " ";
							}
						}

						if (element->FirstChildElement("item") == nullptr)
						{
							ss << " ";
						}
					}
					else if (mat)
					{
						ss << "{";
						for (XMLElement* material = element->FirstChildElement("material"); material != NULL; material = material->NextSiblingElement("material"))
						{
							ss << processMaterialTag(material);
							ss << "~";
						}
						ss << "}";
					}
					else
					{
						if (element->GetText())
						{
							std::string elementValue = element->GetText();
							ss << elementValue;
						}
						else
						{
							ss << " ";
						}
					}
					ss << ",";
				}
				std::string projectString = ss.str().substr(0, ss.str().length() - 1);
				Project* projectClass = new Project();
				projectClass->populate(split(projectString.substr(0, projectString.find_last_of(",") - 1), ","));

				bool nowPlaying = projectString.substr(projectString.find_last_of(","), projectString.length()) == "true" ? true : false;
				fileProjects.insert(std::pair<Project*, bool>(projectClass, nowPlaying));
			}
		}
	}
	return fileProjects;
}

std::vector<Material*> XMLHandler::readMaterialsFromFile()
{
	std::vector<Material*> materialsVec;
	XMLDocument doc;
	doc.LoadFile("test.xml");
	if (doc.ErrorID() == 0)
	{
		XMLElement* root = doc.FirstChildElement("media");
		std::string materialString;
		if (root->FirstChildElement())
		{
			for (XMLElement* materials = root->FirstChildElement("materials"); materials != NULL; materials = materials->NextSiblingElement("materials"))			//Get materials
			{
				for (XMLElement* material = materials->FirstChildElement("material"); material != NULL; material = material->NextSiblingElement("material"))
				{
					Material* materialClass = new Material();
					materialString = processMaterialTag(material);
					std::vector<std::string> materialElements = split(materialString.substr(0, materialString.length() - 1), ",");
					materialClass = materialfactory->createMaterial(materialElements[2], materialString);
					materialsVec.push_back(materialClass);
				}
			}
		}
	}
	materials_ = materialsVec;
	return materialsVec;
}

std::string XMLHandler::processMaterialTag(XMLElement * rootMaterial)
{
	std::stringstream ss;
	
	for (XMLElement* element = rootMaterial->FirstChildElement(); element != NULL; element = element->NextSiblingElement())
	{
		bool att = element->Attribute("vector");
		std::string elementValue = element->Value();
		bool mat = elementValue == "materials";
		bool comboMat = elementValue == "comboMaterials";
		if (att)
		{
			bool setSplit = false;
			for (XMLElement* item = element->FirstChildElement("item"); item != NULL; item = item->NextSiblingElement("item"))
			{
				if (item->Attribute("side") != NULL)
				{
					if (item->Attribute("side", "1"))
					{
						for (XMLElement* side = item->FirstChildElement("side"); side != NULL; side = side->NextSiblingElement("side"))
						{
							if (side->GetText())
							{
								ss << side->GetText() << "|";
							}
							else
							{
								ss << " ";
							}
						}
						ss << "-";
						setSplit = true;
					}
					else if (item->Attribute("side", "2"))
					{
						if(!setSplit)
							ss << "-";
						for (XMLElement* side = item->FirstChildElement("side"); side != NULL; side = side->NextSiblingElement("side"))
						{
							if (side->GetText())
							{
								ss << side->GetText() << "|";
							}
							else
							{
								ss << " ";
							}
						}
					}
				}
				else  //Not a double sided
				{
					if (item->GetText())
					{
						ss << item->GetText() << "|";
					}
					else
					{
						ss << " ";
					}
				}
			}
		}
		else if (mat)
		{
			ss << "{";
			for (XMLElement* material = element->FirstChildElement("material"); material != NULL; material = material->NextSiblingElement("material"))
			{
				ss << processMaterialTag(material);
				ss << "~";
			}
			ss << "}";
		}
		else if (comboMat)
		{
			ss << "[";
			for (XMLElement* material = element->FirstChildElement("material"); material != NULL; material = material->NextSiblingElement("material"))
			{
				ss << processMaterialTag(material);
				ss << "_";
			}
			ss << "]";
		}
			
		else
		{
			if (element->GetText())
			{
				ss << element->GetText();
			}
			else
			{
				ss << " ";
			}
		}
		ss << ",";
	}

	std::string material = ss.str();
	return material;
}

std::vector<std::string> XMLHandler::split(std::string string, std::string del)
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

void XMLHandler::write(std::vector<std::string> elements)
{
	XMLDocument document;
	document.LoadFile("test.xml");

	XMLNode * pRoot;

	if (document.FirstChildElement("media") == nullptr)
	{
		XMLNode * pRoot = document.NewElement("media");
		
		document.InsertFirstChild(pRoot);	//Insert Media tag
		XMLElement * projects = document.NewElement("projects");	//Insert project tag
		projects->SetText("\n");
		pRoot->InsertEndChild(projects);							//End projects

		XMLElement * materials = document.NewElement("materials");
		materials->SetText("\n");
		pRoot->InsertEndChild(materials);

		document.InsertEndChild(pRoot);
	}
	


	if (document.FirstChildElement("media") == nullptr)
	{
	}

	if (elements[2] == "BluRay" || elements[2] == "SingleDVD")
	{
		writeSingleDisc(elements, &document);
	}
	else if (elements[2] == "DoubleDVD")
	{
		writeDouble(elements, &document);
	}
	else if (elements[2] == "Combo")
	{
		writeCombo(elements, &document);
	}
	else if (elements[2] == "VHS")
	{
		writeVHS(elements, &document);
	}
	else		// Project
	{
		writeProject(elements, &document);
	}
	document.SaveFile("test.xml");
}

void XMLHandler::writeBaseMaterial(std::vector<std::string> elements, tinyxml2::XMLElement* parent, tinyxml2::XMLDocument * doc)
{
	insertElement(doc, parent, "id", elements[0]);
	insertElement(doc, parent, "title", elements[1]);
	insertElement(doc, parent, "format", elements[2]);
	insertElement(doc, parent, "audioFormat", elements[3]);
	insertElement(doc, parent, "runtime", elements[4]);
	insertElement(doc, parent, "language", elements[5]);
	insertElement(doc, parent, "retailPrice", elements[6]);
	insertElement(doc, parent, "subtitles", elements[7]);
	insertElement(doc, parent, "aspectRatio", elements[8]);
}

void XMLHandler::writeProject(std::vector<std::string> elements, XMLDocument * doc)
{
	XMLElement* projects = doc->FirstChildElement("media")->FirstChildElement("projects");


	XMLElement* project = doc->NewElement("project");
	projects->InsertFirstChild(project);

	insertElement(doc, project, "title", elements[0]);
	insertElement(doc, project, "summary", elements[1]);
	insertElement(doc, project, "genre", elements[2]);
	insertElement(doc, project, "releaseDate", elements[3]);
	insertVectorElement(doc, project, "filmingLocations", elements[4]);
	insertElement(doc, project, "language", elements[5]);
	insertVectorElement(doc, project, "keywords", elements[6]);
	insertVectorElement(doc, project, "weeklyTicketSales", elements[7]);
	insertVectorElement(doc, project, "crew", elements[8]);
	writeProjectMaterials(doc, project, "materials", elements[9]);
	//WriteMaterial
	insertElement(doc, project, "nowPlaying", elements[10]);

	projects->InsertEndChild(project);

	
}

void XMLHandler::writeSingleDisc(std::vector<std::string> elements, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* parent /*nullptr*/)
{
	XMLElement* materials = doc->FirstChildElement("media")->FirstChildElement("materials");
	XMLElement* material = doc->NewElement("material");
	if (parent != nullptr)
	{
		materials = parent;
	}
	materials->InsertFirstChild(material);

	writeBaseMaterial(elements, material, doc);
	
	insertVectorElement(doc, material, "languageTrack", elements[9]);
	insertVectorElement(doc, material, "subtitlesTrack", elements[10]);
	insertVectorElement(doc, material, "audioTrack", elements[11]);
	insertElement(doc, material, "packageType", elements[12]);
	insertVectorElement(doc, material, "packageSize", elements[13]);
	insertVectorElement(doc, material, "content", elements[14]);
	insertVectorElement(doc, material, "bonus", elements[15]);

	materials->InsertEndChild(material);

	
}

void XMLHandler::writeVHS(std::vector<std::string> elements, tinyxml2::XMLDocument * doc, tinyxml2::XMLElement* parent)
{
	XMLElement* materials = doc->FirstChildElement("media")->FirstChildElement("materials");
	XMLElement* material = doc->NewElement("material");
	if (parent != nullptr)
	{
		materials = parent;
	}
	materials->InsertFirstChild(material);

	writeBaseMaterial(elements, material, doc);

	insertElement(doc, material, "packageType", elements[9]);
	insertVectorElement(doc, material, "packageSize", elements[10]);
	insertVectorElement(doc, material, "content", elements[11]);

	materials->InsertEndChild(material);

	
}

void XMLHandler::writeCombo(std::vector<std::string> elements, tinyxml2::XMLDocument * doc, tinyxml2::XMLElement* parent)
{
	XMLElement* materials = doc->FirstChildElement("media")->FirstChildElement("materials");
	XMLElement* material = doc->NewElement("material");
	if (parent != nullptr)
	{
		materials = parent;
	}
	materials->InsertFirstChild(material);

	writeBaseMaterial(elements, material, doc);

	insertElement(doc, material, "packageType", elements[9]);
	insertVectorElement(doc, material, "packageSize", elements[10]);

	std::stringstream ss;
	for (int i = 11; i < elements.size(); i++)
	{
		ss << elements[i] << ",";
	}
	elements[11] = ss.str().substr(0, ss.str().length() - 1);
	writeComboMaterial(doc, material, "comboMaterials", elements[11]);

	materials->InsertEndChild(material);

	
}

void XMLHandler::writeDouble(std::vector<std::string> elements, tinyxml2::XMLDocument * doc, tinyxml2::XMLElement* parent /*nullptr*/)
{
	
	XMLElement* materials = doc->FirstChildElement("media")->FirstChildElement("materials");
	XMLElement* material = doc->NewElement("material");
	if (parent != nullptr)
	{
		materials = parent;
	}
	materials->InsertFirstChild(material);

	writeBaseMaterial(elements, material, doc);

	insertMapElement(doc, material, "languageTrack", elements[9]);
	insertMapElement(doc, material, "subtitlesTrack", elements[10]);
	insertMapElement(doc, material, "audioTrack", elements[11]);
	insertElement(doc, material, "packageType", elements[12]);
	insertVectorElement(doc, material, "packageSize", elements[13]);
	insertMapElement(doc, material, "content", elements[14]);
	insertMapElement(doc, material, "bonus", elements[15]);

	materials->InsertEndChild(material);

	
}

void XMLHandler::writeComboMaterial(tinyxml2::XMLDocument * doc, tinyxml2::XMLElement * parent, std::string elementName, std::string value)
{
	XMLElement* newElement = doc->NewElement(elementName.c_str());
	parent->InsertFirstChild(newElement);

	value = value.substr(value.find_first_of("[") + 1, value.find_last_of("]") - 1);
	std::vector<std::string> cMaterials = split(value, "_");
	for (std::string stringElements : cMaterials)
	{
		std::vector<std::string> elements = split(stringElements, ",");
		if (elements[2] == "BluRay" || elements[2] == "SingleDVD")
		{
			writeSingleDisc(elements, doc, newElement);
		}
		else if (elements[2] == "DoubleDVD")
		{
			writeDouble(elements, doc, newElement);
		}
	}
	parent->InsertEndChild(newElement);
}

void XMLHandler::insertElement(XMLDocument* doc, tinyxml2::XMLElement* parent, std::string elementName, std::string value)
{
	XMLElement* newElement = doc->NewElement(elementName.c_str());
	parent->InsertFirstChild(newElement);
	if (value == "")
	{
		value = " ";
	}
	newElement->SetText(value.c_str());
	parent->InsertEndChild(newElement);
}

void XMLHandler::insertVectorElement(tinyxml2::XMLDocument * doc, tinyxml2::XMLElement * parent, std::string elementName, std::string value)
{
	std::vector<std::string> itemsVec = split(value, "|");
	XMLElement* newElement = doc->NewElement(elementName.c_str());
	newElement->SetAttribute("vector", "true");
	parent->InsertFirstChild(newElement);
	
	for (std::string item : itemsVec)
	{
		XMLElement* itemElement = doc->NewElement("item");
		newElement->InsertFirstChild(itemElement);
		if (item == "")
		{
			item = " ";
		}
		itemElement->SetText(item.c_str());
		newElement->InsertEndChild(itemElement);

	}
	parent->InsertEndChild(newElement);

}

void XMLHandler::insertMapElement(tinyxml2::XMLDocument * doc, tinyxml2::XMLElement * parent, std::string elementName, std::string value)
{
	std::vector<std::string> sides = split(value, "-");
	
	XMLElement* newElement = doc->NewElement(elementName.c_str());
	newElement->SetAttribute("vector", "true");
	parent->InsertFirstChild(newElement);

	for (int i = 0; i < sides.size(); i++)
	{
		std::vector<std::string> items = split(sides[i], "|");
		XMLElement* itemElement = doc->NewElement("item");
		itemElement->SetAttribute("side", std::to_string(i + 1).c_str());	// set side attribute
		newElement->InsertFirstChild(itemElement);
		for (std::string item : items)
		{
			if (item == "")
			{
				item = " ";
			}
			XMLElement* sideElement = doc->NewElement("side");
			itemElement->InsertFirstChild(sideElement);
			sideElement->SetText(item.c_str());
			itemElement->InsertEndChild(sideElement);
		}
		newElement->InsertEndChild(itemElement);
	}
	parent->InsertEndChild(newElement);
}

void XMLHandler::writeProjectMaterials(tinyxml2::XMLDocument * doc, tinyxml2::XMLElement * parent, std::string elementName, std::string value)
{
	value = value.substr(value.find_first_of("{") + 1, value.find_last_of("}") - 1);
	if (value == "")
	{
		XMLElement* newElement = doc->NewElement(elementName.c_str());
		newElement->SetText(" ");
		parent->InsertFirstChild(newElement);
		parent->InsertEndChild(newElement);
	}
	else
	{
		std::vector<std::string> materialStrings = split(value, "~");
		for (std::string materialString : materialStrings)
		{
			std::vector<std::string> materialElements = split(materialString, ",");
			if (materialElements[2] == "BluRay" || materialElements[2] == "SingleDVD")
			{
				writeSingleDisc(materialElements, doc);
			}
			else if (materialElements[2] == "DoubleDVD")
			{
				writeDouble(materialElements, doc);
			}
			else if (materialElements[2] == "Combo")
			{
				writeCombo(materialElements, doc);
			}
			else if (materialElements[2] == "VHS")
			{
				writeSingleDisc(materialElements, doc);
			}
		}
	}
}

