#pragma once

#ifndef PROJECTCONTROLLER_CPP
#define PROJECTCONTROLLER_CPP

#include "stdafx.h"
#include "ProjectController.h"
#include "MaterialFactoryUserCreate.h"
#include "XMLHandler.h"

#include <string>

ProjectController::ProjectController(SDI::Logger * logger)
{
	this->logger = logger;
	if (!projectManager.setupSaveFile())
	{
		projectViewer.displayMessage("You do not have any existing projects or materials");
		projectViewer.displayMessage("Would you like to import from an existing file? Yes or No");

		std::string userImport = toLower(getUserInput());
		if (userImport == "yes" || userImport == "y")
		{
			projectViewer.displayMessage("What file would you like to import?");
			projectManager.importFile(getUserInput());
		}
	}
	XMLHandler handler("XMLFile.xml", new MaterialFactory());
	start();
}


ProjectController::~ProjectController()
{
}

void ProjectController::start()
{
	while (!exit_)
	{
		projectViewer.displayMenuOptions();
		processUserInput(getUserInput());
		if(!exit_)		// Ignore if we are leaving
			userContinueOption();
	}
}

void ProjectController::userContinueOption()
{
	if (exit_ == false) // Skip this step if we are already leaving the application
	{
		// Display message to the user
		projectViewer.displayMessage(" ");
		projectViewer.displayMessage("Would you like to continue?");
		projectViewer.displayMessage("Yes or No");

		std::string userContinue = toLower(getUserInput());
		if (userContinue == "no")
			exit_ = true;

		projectViewer.clearScreen();
	}
}

void ProjectController::processUserInput(const std::string & message)
{

	std::string input = message;

	if (input == "exit" || input == "0")
	{
		exit_ = true;
	}
	else if (input == "1" || input == "import")
	{
		projectViewer.displayMessage("Please enter a path to the file you would like to import : ");
		projectManager.importFile(getUserInput());
	}
	else if (input == "2" || input == "save")
	{
		projectManager.save();
	}
	else if (input == "3" || input == "view")
	{
		projectViewer.displayViewOptions();// displayViewOptions();
		processViewOptions();
	}
	else if (input == "4" || input == "create")
	{
		projectViewer.displayCreateMenu();// displayCreateMenu();
		processCreateOptions();
	}
	else if (input == "5" || input == "search")
	{
		projectViewer.displaySearchMenu();//displaySearchMenu();
		processSearchOptions();
	}
	else if (input == "6" || input == "delete")
	{
		projectViewer.displayDeleteMenu();
		processDeleteOptions();
	}
	else if (input == "7" || input == "edit")
	{
		projectViewer.displayEditMenu();
		processEditOptions();
	}
	else if (input == "8" || input == "browse")
	{
		projectViewer.displayBrowseMenu();
		processBrowseOptions();
	}
	else if (input == "9" || input == "interactivly")
	{
		processInteractiveSearch();
	}
	else			// No valid option has been entered
	{
		projectViewer.displayMessage("You didn't enter a valid option");
	}
}

void ProjectController::processViewOptions()
{
	std::string viewOption = toLower(getUserInput());
	if (viewOption == "1" || viewOption == "projects")
	{
		projectViewer.allProjects(projectManager.getProjectMap());

		if (yesNoBool("Would you like to view projects in full?"))
		{
			for (Project* project : projectManager.getProjects())
			{
				projectViewer.viewFullProject(project);
			}
		}
	}
	else if (viewOption == "2" || viewOption == "materials")
	{
		projectViewer.allMaterials(projectManager.getAllMaterials());
		if (yesNoBool("Would you like to view materials in full?"))
		{
			for (Material* material : projectManager.getAllMaterials().first)
			{
				projectViewer.viewFullMaterial(material);
			}

			for (Material* material : projectManager.getAllMaterials().second)
			{
				projectViewer.viewFullMaterial(material);
			}
		}
	}
	else		// No valid option has been entered for view option
	{
		projectViewer.displayMessage("You didn't enter a valid option for view");
	}
}

void ProjectController::processCreateOptions()
{
	std::string input = toLower(getUserInput());
	if (input == "1" || input == "create project")
	{
		MaterialFactoryUserCreate userCreateProject(&projectViewer);
		Project* project = userCreateProject.createProject();
		bool nowPlaying = yesNoBool("Is this project now playing?");
		if (nowPlaying || (projectManager.isReleased(project) && yesNoBool("The project has been released would you like to set ticket sales?")))
		{
			project->setTicketSales(messageReturnUserVectorInt("Enter weekly ticket sales"));
		}
		if (projectManager.isReleased(project))
		{
			if (yesNoBool("Would you like to link materials to the project?"))
			{
				projectManager.addMaterialToProject(project, getMaterialsFromUser("Select a material"));
			}
		}
		projectManager.addProject(project, nowPlaying);
	}
	else if (input == "2" || input == "create material")
	{
		MaterialFactoryUserCreate userCreateMaterial(&projectViewer);
		Material* material = userCreateMaterial.userInsertIntoMaterial(projectManager.getMaterialCount(), projectManager.getExistingDiscs());
		projectManager.addMaterial(material);
		projectManager.incrementMaterialCount();
		projectManager.setMaterialCounter(projectManager.getMaterialCount() + userCreateMaterial.getNewMaterialCount());
	}
	else if (input == "3" || input == "link media")
	{
		linkMedia();
	}
}

void ProjectController::processSearchOptions()
{
	std::string input;
	
	projectViewer.displayMessage("Please enter your option. 1 or 2");
	input = getUserInput();

	if (input == "1")
	{
		Project* project = getProjectFromUser("Pick a project");
		for (Material* material : project->getMaterials())
		{
			projectViewer.displayPartialMaterial(material);
		}
	}
	else if (input == "2")
	{
		Material* material = getAssociatedMaterial("Pick a material");
		std::vector<Project*> projects = projectManager.materialFindProject(material);
		projectViewer.displayProjects(projects);
	}
	else
	{
		projectViewer.displayMessage("You didn't enter a valid option for view");
	}
}

void ProjectController::processDeleteOptions()
{

	std::string input;

	projectViewer.displayMessage("Please enter your option. 1 or 2");
	input = getUserInput();

	if (input == "1" || input == "delete project")
	{
		Project* project = getProjectFromUser("Please select a project to delete");
		projectManager.deleteProject(project);
	}
	else if (input == "2" || input == "delete material")
	{
		std::pair<std::vector<Material*>, std::vector<Material*>> allMaterials = projectManager.getAllMaterials();
		projectViewer.allMaterials(allMaterials);		// Display all materials

		int id = messageReturnInt("Select a material index");
		projectManager.deleteMaterial(allMaterials, id);
	}
	else
	{
		projectViewer.displayMessage("You didn't enter a valid option for view");
	}
}

void ProjectController::processEditOptions()
{
	std::string input = messageReturnInput("Please enter an option");

	if (toLower(input) == "1" || toLower(input) == "edit project")
	{
		Project* project = getProjectFromUser("Select a project");
		projectViewer.displayProjectFieldsToEdit();
		processProjectEditFields(project);
	}
	else if(toLower(input) == "2" || toLower(input) == "edit material")
	{
		std::vector<Material*> materials = getMaterialsFromUser("Select a material", true);
		if (!materials.empty())
		{
			Material* material = materials[0];
			if (material != nullptr)
			{
				projectViewer.displayMaterialFieldsToEdit(material);
				processMaterialEditFields(material);
			}
		}
	}
	else
	{
		projectViewer.displayMessage("Not a valid optoin");
	}
}

void ProjectController::processProjectEditFields(Project* project)
{
	std::string input = messageReturnInput("Select field to edit");
	if (input == "1")
	{
		project->setTitle(messageReturnInput("Enter new title"));
	} 
	else if (input == "2")
	{
		project->setSummary(messageReturnInput("Enter new summary"));
	}
	else if (input == "3")
	{
		project->setGenre(messageReturnInput("Enter new genre"));
	}
	else if (input == "4")
	{
		project->setReleaseDate(messageGetDate("Enter new release date"));
	}
	else if (input == "5")
	{
		project->setFilmingLocations(messageReturnUserVector("Enter new Filming locations"));
	}
	else if (input == "6")
	{
		project->setKeywords(messageReturnUserVector("Enter new key words"));
	}
	else if (input == "7")
	{
		if (projectManager.isReleased(project))
		{
			project->setTicketSales(messageReturnUserVectorInt("Enter new ticket sales"));
		}
		else
		{
			projectViewer.displayMessage("Project is not released");
		}
	}
	else if(input == "8")
	{
		if (projectManager.isReleased(project))
		{
			project->getTicketSales().push_back(messageReturnInt("Enter ticket sales"));
		}
		else
		{
			projectViewer.displayMessage("Project is not released");
		}
	}
	else if (input == "9")
	{
		project->setCrew(messageReturnUserVector("Set crew"));
	}
}

void ProjectController::processMaterialEditFields(Material * material)
{
	MaterialFactoryUserCreate mf(&projectViewer);
	mf.editMaterial(material);
}

void ProjectController::processBrowseOptions()
{
	std::string input = messageReturnInput("Please enter an option");

	if (toLower(input) == "1" || toLower(input) == "projects")
	{
		sequentialBrowseProjects();
	}
	else if (toLower(input) == "2" || toLower(input) == "materials")
	{
		sequentialBrowseMaterials();
	}
}

void ProjectController::processInteractiveSearch()
{
	std::string input;

	std::map<int, std::string> searchCritera;

	do
	{
		projectViewer.displayInteractiveSearchMenu();
		input = messageReturnInput("Please enter a field to seach for or enter exit---loop to finish");

		if (input == "1")	//Title
		{
			searchCritera.insert(std::pair<int, std::string>(1, messageReturnInput("Enter a title")));
		}
		else if (input == "2")	//Summary
		{
			searchCritera.insert(std::pair<int, std::string>(2, messageReturnInput("Enter a Summary")));
		}
		else if (input == "3")  //Genre
		{
			searchCritera.insert(std::pair<int, std::string>(3, messageReturnInput("Enter a Genre")));
		}
		else if (input == "4")	//Release date
		{
			searchCritera.insert(std::pair<int, std::string>(4, std::to_string(messageGetDate("Enter a date"))));
		}
		else if (input == "5")	//Filming location
		{
			searchCritera.insert(std::pair<int, std::string>(5, messageReturnInput("Enter a location")));
		}
		else if (input == "6")	//Key words
		{
			searchCritera.insert(std::pair<int, std::string>(6, messageReturnInput("Enter a key word")));
		}
		else if (input == "7")	//crew
		{
			searchCritera.insert(std::pair<int, std::string>(7, messageReturnInput("Enter a crew member")));
		}
		else if (input == "8")	//Mateial Format
		{
			searchCritera.insert(std::pair<int, std::string>(8, messageReturnInput("Enter a material format")));
		}

	} while (toLower(input) != "exit---loop");

	std::vector<Project*> projects = projectManager.findProjects(searchCritera);

	if (!projects.empty())
	{
		projectViewer.displayMessage("Found projects!");
		for (int i = 0; i < projects.size(); i++)
		{
			projectViewer.displayPartialProject(projects[i]);
			if (yesNoBool("Would you like to view the full project?"))
			{
				projectViewer.viewFullProject(projects[i]);
			}
		}
	}
}

void ProjectController::sequentialBrowseProjects()
{
	int count = 0;
	std::string input;
	do
	{
		projectViewer.displayPartialProject(projectManager.getProjects()[count]);
		if (yesNoBool("Would you like to view the full project?"))
		{
			projectViewer.viewFullProject(projectManager.getProjects()[count]);
		}
		input = getUserInput();

		if (projectManager.getProjects().size() > 1)
		{
			if (input == "<")
			{
				if (count - 1 < 0)
				{
					count = projectManager.getProjects().size() - 1;
				}
				count--;
			}
			else if (input == ">")
			{
				if (count + 1 > projectManager.getProjects().size() - 1)
				{
					count = 0;
				}
				count++;
			}
			else
			{
				break;
			}
		}
		else
		{
			if (input != "<" || input != ">")
			{
				break;
			}
		}

	} while (1);
}

void ProjectController::sequentialBrowseMaterials()
{
	int count = 0;
	std::string input;
	do
	{
		projectViewer.displayPartialMaterial(projectManager.getMaterials()[count]);
		if (yesNoBool("Would you like to view the full project?"))
		{
			projectViewer.viewFullMaterial(projectManager.getMaterials()[count]);
		}
		input = getUserInput();

		if (projectManager.getMaterials().size())
		{
			if (input == "<")
			{
				if (count - 1 < 0)
				{
					count = projectManager.getMaterials().size() - 1;
				}
				count--;
			}
			else if (input == ">")
			{
				if (count + 1 > projectManager.getMaterials().size() - 1)
				{
					count = 0;
				}
				count++;
			}
			else
			{
				break;
			}
		}
		else
		{
			if (input != "<" || input != ">")
			{
				break;
			}
		}

	} while (1);
}

std::string ProjectController::getUserInput()
{
	std::string userInput = "";
	std::getline(std::cin, userInput);
	logger->debug("user input == : " + userInput);
	return userInput;
}



const bool ProjectController::yesNoBool(const std::string & message)
{
	
	projectViewer.displayMessage(message);

	std::string input = "";
	while (toLower(input) != "yes" && toLower(input) != "no")
	{
		projectViewer.displayMessage("please enter a valid option. Yes or No");
		input = getUserInput();
		if (toLower(input) == "yes" || toLower(input) == "no")
		{
			return input == "yes" ? true : false;
		}
	}

	return false;
}

std::vector<Material*> ProjectController::getMaterialsFromUser(const std::string & message, const bool oneExisting /* false */)
{
	projectViewer.displayMessage(message);

	projectViewer.displayMessage("Atleast one value needs to be entered");
	projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<int> selectedId;
	std::vector<Material*> userData = {};
	std::string input = "";

	projectViewer.displayMaterialVector(projectManager.getMaterials());

	if (!oneExisting)
	{
		while ((toLower(input) != "exit---loop") || userData.empty())
		{
			if (yesNoBool("Would you like to create a material? enter no to add existing material"))
			{
				MaterialFactoryUserCreate userCreateMaterial(&projectViewer);
				Material* newMaterial = userCreateMaterial.userInsertIntoMaterial(projectManager.getMaterialCount(), projectManager.getExistingDiscs());
				projectManager.addMaterial(newMaterial);
				projectManager.incrementMaterialCount();
				projectManager.setMaterialCounter(projectManager.getMaterialCount() + userCreateMaterial.getNewMaterialCount());

				//Material* newMaterial = createMaterial();
				userData.push_back(newMaterial);
				selectedId.push_back(newMaterial->getId());
			}
			else
			{
				projectViewer.displayMessage("Please enter material index. Or exit---loop to finish");
				try
				{
					input = getUserInput();
					if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
					{
						int id = messageReturnInt("Please enter index");

						if (std::find(selectedId.begin(), selectedId.end(), id) != selectedId.end())
						{
							if (yesNoBool("you have already added this material do you want to add it again?"))
							{
								userData.push_back(projectManager.getMaterials()[id]);
								selectedId.push_back(id);
							}
						}
						else
						{
							Material* material = projectManager.getMaterialFromId(id);
							if (material != nullptr)
							{
								userData.push_back(material);
								selectedId.push_back(id);
							}
						}
					}
				}
				catch (std::invalid_argument ia)
				{
					projectViewer.displayMessage("Please enter a valid id (integer)");
				}
			}
		}
	}
	else			// Only select one existing material
	{
		if (!projectManager.getMaterials().empty())
		{
			bool valid = true;
			do
			{
				try
				{
					int id = messageReturnInt("Please enter material index");;

					Material* material = projectManager.getMaterialFromId(id);
					if (material != nullptr)
					{
						userData.push_back(material);
						selectedId.push_back(id);
						valid = true;
					}
				}
				catch (std::invalid_argument ia)
				{
					valid = false;
				}

			} while (!valid);
		}
		else
		{
			projectViewer.displayMessage("No materials exist");
		}
	}
	return userData;
}

Project * ProjectController::getProjectFromUser(const std::string & message)
{
	projectViewer.displayMessage(message);

	Project* project = nullptr;
	std::vector<Project*> tmpProjects;

	std::map<Project*, bool> projects_ = projectManager.getProjectMap();

	if (!projects_.empty())
	{
		projectViewer.displayMessage("INDEX : TITLE : SUMMARY : GENRE");
		projectViewer.displayProjectMap(projects_);
		tmpProjects = projectManager.getProjects();

		int selectedIndex;
		do
		{
			selectedIndex = messageReturnInt("Enter Project index");
			if (selectedIndex > -1 && selectedIndex <= projects_.size() - 1)  // if valid selection
			{
				return tmpProjects[selectedIndex];
			}
		} while (selectedIndex < 0 || selectedIndex > projects_.size() - 1);
	}
	else		// No projects are loaded to memory
	{
		projectViewer.displayMessage("Their are no loaded projects! Import or create one");
		return nullptr;
	}

	return project;
}

const int ProjectController::messageReturnInt(const std::string & message)
{

	projectViewer.displayMessage(message);
	bool invalid = true;

	int i;

	while (invalid)
	{
		try
		{
			i = std::stoi(messageReturnInput("Enter Integer"));
			invalid = false;
		}
		catch (std::invalid_argument)
		{
			projectViewer.displayMessage("Not a valid input plese try again");
		}
	}
	return i;
}

const std::string ProjectController::messageReturnInput(const std::string & message)
{
	projectViewer.displayMessage(message);
	projectViewer.displayMessage("Please enter your input");

	std::string input = getUserInput();
	while ((input == "") && (input.find_first_of(" ") == std::string::npos))  // Ensure user input is not null or only spaces
	{
		projectViewer.displayMessage("Your input cannot be nothing. Please try again");
		input = getUserInput();
	}

	return input;
}

void ProjectController::linkMedia()
{
	projectViewer.displayMessage("Please select a project and material to link");
	if (!projectManager.getMaterials().empty() && !projectManager.getProjectMap().empty())
	{
		Project* project = getProjectFromUser("Please select a project");
		if (project != nullptr)
		{
			if (projectManager.isReleased(project))
			{
				std::vector<Material*> materials = getMaterialsFromUser("Please select materials to link");
				if (!materials.empty())
				{
					for (Material* projMat : materials)
					{
						project->addMaterial(projMat);
					}

					int materialIndex = -1;
					for (Material* material : projectManager.getMaterials())
					{
						if (material != nullptr)
						{
							materialIndex++;
							for (Material* localMaterial : materials)
							{
								if (localMaterial != nullptr)
								{
									if (material->getId() == localMaterial->getId())
									{
										projectManager.getProjectAssociatedMaterials().push_back(localMaterial);
										std::vector<Material*> materialsList = projectManager.getMaterials();
										materialsList.erase(materialsList.begin() + materialIndex);
										projectManager.setMaterialsList(materialsList);
									}
								}
							}
						}
						if (materialIndex + 1 >= projectManager.getMaterials().size())
						{
							break;
						}
					}
				}
			}
			else
			{
				projectViewer.displayMessage("Project has not been released. Materials cannot be added");
			}
		}
	}
	else		// Missing either a project or material
	{
		projectViewer.displayMessage("You need to have atleast one project and one material to make a link");
	}
}

Material * ProjectController::getAssociatedMaterial(const std::string & message)
{
	projectViewer.displayMessage(message);
	Material* material = nullptr;
	std::string input;
	std::vector<int> validIndex;
	for (Material* mat : projectManager.getProjectAssociatedMaterials())
	{
		if (mat != nullptr)
		{
			projectViewer.displayMessage(std::to_string(mat->getId()) + " : " + mat->getFilmTitle() + " : " + mat->getFormat());
			validIndex.push_back(mat->getId());
		}
	}

	bool valid = false;
	do
	{
		
		int id = messageReturnInt("Please enter material index");

		for (int i : validIndex)
		{
			if (id == i)
			{
				valid = true;
			}
		}

		if (valid)
		{
			if (projectManager.getProjectAssociatedMaterials()[id] != nullptr)
			{
				material = projectManager.getProjectAssociatedMaterials()[id];
				valid = true;
			}
			else
			{
				valid = false;
			}
		}
		else
		{
			valid = false;
		}

	} while (!valid);
	
	return material;
}

std::string ProjectController::toLower(std::string & input)
{
	for (int i = 0; i < input.length(); i++)
	{
		input[i] = tolower(input[i]);
	}
	return input;
}

/*
* Display a message on screen and get user entered integers and return a vector of ints
*/
const std::vector<int> ProjectController::messageReturnUserVectorInt(const std::string & message)
{
	projectViewer.displayMessage(message);

	projectViewer.displayMessage("Atleast one value needs to be entered");

	std::vector<int> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		projectViewer.displayMessage("Please enter a value. Or exit---loop to finish");
		projectViewer.displayMessage("This is data set : " + userData.size() + 1);
		input = getUserInput();
		if (toLower(input) != "exit---loop")
		{
			try
			{
				userData.push_back(std::stoi(input));
			}
			catch (std::invalid_argument ia)
			{
				projectViewer.displayMessage("Could not convert " + input + " to an integer");
			}
		}
	}


	return userData;
}

const long ProjectController::messageGetDate(const std::string & message)
{
	projectViewer.displayMessage(message);

	time_t rawTime;
	struct tm timeInfo;
	int year, month, day;
	long timestamp = -1;

	bool validInput = true;

	while (timestamp == -1)
	{
		/*
		* Get user input date
		*/
		try
		{
			projectViewer.displayMessage("Enter Year: ", false); year = stoi(getUserInput());
			projectViewer.displayMessage("Enter Month: ", false); month = stoi(getUserInput());
			projectViewer.displayMessage("Enter Day: ", false); day = stoi(getUserInput());
			validInput = true;
		}
		catch (std::invalid_argument ia)
		{
			validInput = false;
			projectViewer.displayMessage("Invalid input please re enter");
		}

		if (validInput)
		{
			time(&rawTime);
			localtime_s(&timeInfo, &rawTime);				// Init timeInfo struct

			timeInfo.tm_year = year - 1900;					// Setup timeInfo struct
			timeInfo.tm_mon = month - 1;
			timeInfo.tm_mday = day;
			timeInfo.tm_hour = 1;
			timeInfo.tm_min = 0;
			timeInfo.tm_sec = 0;

			timestamp = mktime(&timeInfo);					// COnvert to unix

			if (timestamp == -1)							// Invalid date set entered
				projectViewer.displayMessage("invalid date please re enter");
		}
	}

	return timestamp;
}

const std::vector<std::string> ProjectController::messageReturnUserVector(const std::string & message, const bool canBeNull)
{
	projectViewer.displayMessage(message);
	if (!canBeNull)
		projectViewer.displayMessage("Atleast one value needs to be entered");
	projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<std::string> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || (userData.empty() && !canBeNull))
	{
		projectViewer.displayMessage("Please enter a value. Or exit---loop to finish");
		input = getUserInput();
		if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
		{
			userData.push_back(input);
		}
	}

	return userData;
}

#endif // !PROJECTCONTROLLER