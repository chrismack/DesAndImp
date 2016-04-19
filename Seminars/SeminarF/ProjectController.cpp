#include "stdafx.h"
#include "ProjectController.h"
#include "MaterialFactoryUserCreate.h"

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
		for (Project* project : projectManager.getProjects())
		{
			projectViewer.allProjects(projectManager.getProjectMap());
			//projectManager.viewProjects();
		}
	}
	else if (viewOption == "2" || viewOption == "materials")
	{
		//projectManager.viewMaterials();
		projectViewer.allMaterials(projectManager.getAllMaterials());
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
		//projectManager.createAndAddProject();
		MaterialFactoryUserCreate userCreateProject(&projectViewer);
		Project* project = userCreateProject.createProject();
		bool nowPlaying = yesNoBool("Is this project now playing?");
		
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
		//projectManager.createAndAddMaterial();
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
		projectManager.deleteProject();
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

std::string ProjectController::getUserInput()
{
	std::string userInput = "";
	std::getline(std::cin, userInput);
	//std::cin >> userInput;
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

		int index = 0;
		std::map<Project*, bool>::iterator it;
		for (it = projects_.begin(); it != projects_.end(); ++it)
		{
			projectViewer.displayMessage(std::to_string(index) + " : " + it->first->getTitle() + " : " + it->first->getSummary() + " : " + it->first->getGenre());
			index++;
			tmpProjects.push_back(it->first);
		}

		int selectedIndex;
		do
		{
			selectedIndex = messageReturnInt("Enter Project index");
			if (selectedIndex > -1 && selectedIndex < projects_.size())  // if valid selection
			{
				return tmpProjects[selectedIndex];
			}
		} while (selectedIndex > -1 && selectedIndex < projects_.size());
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
					project->setMaterials(materials);

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
		projectViewer.displayMessage("Please enter material index");
		try
		{
			input = getUserInput();
			if (input != "" && input.find_first_of(" ") == std::string::npos)
			{
				int id = std::stoi(input);

				for (int i : validIndex)
				{
					if (id == i)
					{
						valid = true;
					}
				}

				if (valid)
				{

					for (Material* localMaterial : projectManager.getProjectAssociatedMaterials())
					{
						if (localMaterial != nullptr)
						{
							if (localMaterial->getId() == id)
							{
								material = localMaterial;
							}
						}
					}
				}
				else
				{
					valid = false;
				}
			}
		}
		catch (std::invalid_argument ia)
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
