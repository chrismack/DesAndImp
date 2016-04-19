#include "stdafx.h"
#include "MaterialFactoryUserCreate.h"

#include "SingleDVD.h"
#include "DoubleDVD.h"
#include "BlueRay.h"
#include "ComboBox.h"
#include "VHS.h"

#include <time.h>


MaterialFactoryUserCreate::MaterialFactoryUserCreate(ProjectViewer* projectViewer)
{
	this->projectViewer = projectViewer;
}


MaterialFactoryUserCreate::~MaterialFactoryUserCreate()
{
	/*
	 * Deleteing project viewer and discs handled by other classes
	 */
}

Material * MaterialFactoryUserCreate::userInsertIntoMaterial(int materialCount, std::vector<Disc*> discs, const bool mustBeDisc /* false */)
{
	Material* material = nullptr;

	std::string type;

	bool invalid = false;
	do
	{
		if (mustBeDisc)
		{
			projectViewer->displayMessage("Please enter valid type; BluRay, SingleDVD, DoubleDVD");
		}
		else
		{
			projectViewer->displayMessage("Please enter valid type; BluRay, SingleDVD, DoubleDVD, Combo, VHS");
		}
		type = messageReturnInput("Set Type");
		type = toLower(type);

		invalid = false;
		if (type == "bluray")
		{
			material = new BlueRay();
			userInsertBaseMaterials(material, "BluRay", materialCount);

			BlueRay *blu = dynamic_cast<BlueRay*> (material);
			blu->setContent(messageReturnUserVector("Set content"));
			blu->setBonusFeatures(messageReturnUserVector("Set bonus features"));
			blu->setAudioTracks(messageReturnUserVector("Set audio tacks"));
			blu->setLanguageTracks(messageReturnUserVector("Set language tracks"));
			blu->setSubtitleTracks(messageReturnUserVector("Set subtitles tracks"));

			setMaterialPackage(blu);
		}
		else if (type == "singledvd")
		{
			material = new SingleDVD();
			userInsertBaseMaterials(material, "SingleDVD", materialCount);

			SingleDVD *dvd = dynamic_cast<SingleDVD*> (material);
			dvd->setContent(messageReturnUserVector("Set content"));
			dvd->setBonusFeatures(messageReturnUserVector("Set bonus features"));
			dvd->setAudioTracks(messageReturnUserVector("Set audio tacks"));
			dvd->setLanguageTracks(messageReturnUserVector("Set language tracks"));
			dvd->setSubtitleTracks(messageReturnUserVector("Set subtitles tracks"));

			setMaterialPackage(dvd);
		}
		else if (type == "doubledvd")
		{
			material = new DoubleDVD();
			userInsertBaseMaterials(material, "DoubleDVD", materialCount);

			DoubleDVD *dvd = dynamic_cast<DoubleDVD*> (material);
			dvd->setContent(setVectorSideMap("Set content"));
			dvd->setBonusFeatures(setVectorSideMap("Set bonus features"));
			dvd->setAudioTracks(setVectorSideMap("Set audio tacks"));
			dvd->setLanguageTracks(setVectorSideMap("Set language tracks"));
			dvd->setSubtitleTracks(setVectorSideMap("Set subtitles tracks"));
		}
		else if (type == "combo" && !mustBeDisc)
		{
			material = new ComboBox();
			userInsertBaseMaterials(material, "Combo", materialCount);

			ComboBox *combo = dynamic_cast<ComboBox*> (material);
			combo->setContent(getDiscMaterialsFromUser(materialCount, "Set Materials", discs));

			setMaterialPackage(combo);			// Set package spec
		}
		else if (type == "vhs" && !mustBeDisc)
		{
			material = new VHS();
			userInsertBaseMaterials(material, "VHS", materialCount);

			VHS *vhs = dynamic_cast<VHS*> (material);
			vhs->setContent(messageReturnUserVector("Set content"));
			vhs->setlanguageTrack(messageReturnInput("Set language track"));
			vhs->setAudioTrack(messageReturnInput("Set audio track"));

			setMaterialPackage(vhs);			// Set package spec
		}
		else
		{
			invalid = true;
		}
	} while (invalid);

	return material;
}

Project * MaterialFactoryUserCreate::createProject()
{
	Project* project = new Project();
	// title, summary, genre, releasedate, filminglocation, language, keywords, ticketSale
	project->setTitle(messageReturnInput("Set Title"));
	project->setSummary(messageReturnInput("Set Summary"));
	project->setGenre(messageReturnInput("Set Genre"));
	project->setReleaseDate(messageGetDate("Set release date"));
	project->setFilmingLocations(messageReturnUserVector("Set Filming Locations"));
	project->setLanguage(messageReturnInput("Set Language"));
	project->setKeywords(messageReturnUserVector("Set keywords"));

	return project;
}

void MaterialFactoryUserCreate::userInsertBaseMaterials(Material * material, const std::string& type, int materialCount)
{
	materialCount += 1;
	material->setID(materialCount);
	material->setFilmTitle(messageReturnInput("Set Title"));
	material->setFormat(type);
	material->setAudioFormat(messageReturnInput("Set Audio Format"));
	material->setRunTime(messageReturnInt("Set Runtime"));
	material->setLanguage(messageReturnInput("Set Language"));
	material->setRetailPrice(messageReturnFloat("Set Retail Price"));
	material->setSubtitles(messageReturnInput("Set Subtitles"));
	material->setAspectRation(messageGetAspect("Set Aspect Ratio"));
}

void MaterialFactoryUserCreate::setMaterialPackage(IPackagable * material)
{
	material->setPackageType(messageReturnInput("Set package type"));
	material->setPackageDimensions(std::tuple<int, int, int>(messageReturnInt("Set package width"), messageReturnInt("Set package height"), messageReturnInt("Set package depth")));
}

/*
* display user with a message and return a non null input
*/
const std::string MaterialFactoryUserCreate::messageReturnInput(const std::string & message)
{
	projectViewer->displayMessage(message);
	projectViewer->displayMessage("Please enter your input");

	std::string input = getUserInput();
	while ((input == "") && (input.find_first_of(" ") == std::string::npos))  // Ensure user input is not null or only spaces
	{
		projectViewer->displayMessage("Your input cannot be nothing. Please try again");
		input = getUserInput();
	}

	return input;
}



std::map<int, std::vector<std::string>> MaterialFactoryUserCreate::setVectorSideMap(const std::string & message)
{
	projectViewer->displayMessage(message);
	std::map<int, std::vector<std::string>> discAttributeMap;

	discAttributeMap.insert(std::pair<int, std::vector<std::string>>(0, messageReturnUserVector("Set side one data", true)));
	discAttributeMap.insert(std::pair<int, std::vector<std::string>>(1, messageReturnUserVector("Set side two data", true)));

	return discAttributeMap;
}

/*
* Display message on screen and get multiple user input and return in a vector
*/
const std::vector<std::string> MaterialFactoryUserCreate::messageReturnUserVector(const std::string & message, const bool canBeNull /*false*/)
{
	projectViewer->displayMessage(message);
	if (!canBeNull)
		projectViewer->displayMessage("Atleast one value needs to be entered");
	projectViewer->displayMessage("enter : exit---loop to finish");

	std::vector<std::string> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || (userData.empty() && !canBeNull))
	{
		projectViewer->displayMessage("Please enter a value. Or exit---loop to finish");
		input = getUserInput();
		if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
		{
			userData.push_back(input);
		}
	}

	return userData;
}

/*
* Display a message on screen and get user entered integers and return a vector of ints
*/
const std::vector<int> MaterialFactoryUserCreate::messageReturnUserVectorInt(const std::string & message)
{

	projectViewer->displayMessage(message);

	projectViewer->displayMessage("Atleast one value needs to be entered");
	projectViewer->displayMessage("enter : exit---loop to finish");

	std::vector<int> userData = {};
	std::string input = "";

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		projectViewer->displayMessage("Please enter a value. Or exit---loop to finish");
		projectViewer->displayMessage("This is data set : " + userData.size() + 1);
		input = getUserInput();
		if (toLower(input) != "exit---loop")
		{
			try
			{
				userData.push_back(std::stoi(input));
			}
			catch (std::invalid_argument ia)
			{
				projectViewer->displayMessage("Could not convert " + input + " to an integer");
			}
		}
	}


	return userData;
}

/*
* Return a pair of ints
*/
const std::pair<int, int> MaterialFactoryUserCreate::messageGetAspect(const std::string & message)
{
	projectViewer->displayMessage(message);

	std::pair<int, int> aspectratio;
	bool invalid = true;
	while (invalid)
	{
		try
		{
			aspectratio.first = std::stoi(messageReturnInput("Please enter width"));
			aspectratio.second = std::stoi(messageReturnInput("Please enter height"));
			invalid = false;
		}
		catch (std::invalid_argument ia)
		{
			projectViewer->displayMessage("Invalid input entered! please try again (must be an integer)");
		}
	}

	return aspectratio;
}

/*
* Displays a message and converts input to an integer
*/
const int MaterialFactoryUserCreate::messageReturnInt(const std::string & message)
{
	projectViewer->displayMessage(message);
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
			projectViewer->displayMessage("Not a valid input plese try again");
		}
	}
	return i;
}


/*
* Gets a user input and converts to a float
*/
const float MaterialFactoryUserCreate::messageReturnFloat(const std::string & message)
{
	projectViewer->displayMessage(message);
	bool invalid = true;

	float f;

	while (invalid)
	{
		try
		{
			f = std::stof(messageReturnInput("Enter decimal"));
			invalid = false;
		}
		catch (std::invalid_argument)
		{
			projectViewer->displayMessage("Not a valid input plese try again");
		}
	}
	return f;
}

std::string MaterialFactoryUserCreate::getUserInput()
{
	std::string userInput = "";
	std::getline(std::cin, userInput);
	//std::cin >> userInput;
	return userInput;
}

std::vector<Disc*> MaterialFactoryUserCreate::getDiscMaterialsFromUser(int materialCount, const std::string & message, std::vector<Disc*> discs)
{
	//projectViewer.displayMessage(message);

	//projectViewer.displayMessage("Atleast one value needs to be entered");
	//projectViewer.displayMessage("enter : exit---loop to finish");

	std::vector<int> validID;
	std::vector<int> selectedId;
	std::vector<Disc*> userData = {};
	std::string input = "";

	projectViewer->displayMessage("ID :	TITLE : FORMAT");
	for (Material* mat : discs)
	{
		if (mat != nullptr)
		{
			std::string materialInfo = "ID: " + std::to_string(mat->getId()) + "   TITLE: " + mat->getFilmTitle() + "   FORMAT: " + mat->getFormat();
			projectViewer->displayMessage(materialInfo);
			validID.push_back(mat->getId());
			newMaterials++;
		}
	}

	while ((toLower(input) != "exit---loop") || userData.empty())
	{
		if (yesNoBool("Would you like to create a material (must be disc)? enter no to add existing material"))
		{
			Disc* discMaterial = (Disc*)userInsertIntoMaterial(materialCount, discs, true);
			userData.push_back(discMaterial);
			selectedId.push_back(discMaterial->getId());
		}
		else // Pick existing material
		{
			projectViewer->displayMessage("Please enter material index. Or exit---loop to finish");
			try
			{
				input = getUserInput();
				if (input != "" && input.find_first_of(" ") == std::string::npos && toLower(input) != "exit---loop")
				{
					int id = std::stoi(input);
					if (std::find(validID.begin(), validID.end(), id) != validID.end())		//Input is a valid ID to select from
					{
						if (std::find(selectedId.begin(), selectedId.end(), id) != selectedId.end())
						{
							if (yesNoBool("you have already added this material do you want to add it again?"))
							{
								userData.push_back(discs[id]);
								selectedId.push_back(id);
							}
						}
						else
						{
							userData.push_back(discs[id]);
							selectedId.push_back(id);
						}
					}
				}
			}
			catch (std::invalid_argument ia)
			{
				projectViewer->displayMessage("Please enter a valid id (integer)");
			}
		}
	}

	return userData;
}

const bool MaterialFactoryUserCreate::yesNoBool(const std::string & message)
{
	projectViewer->displayMessage(message);

	std::string input = "";
	while (toLower(input) != "yes" && toLower(input) != "no")
	{
		projectViewer->displayMessage("please enter a valid option. Yes or No");
		input = getUserInput();
		if (toLower(input) == "yes" || toLower(input) == "no")
		{
			return input == "yes" ? true : false;
		}
	}

	return false;
}

int MaterialFactoryUserCreate::getNewMaterialCount()
{
	return newMaterials;
}

/*
* Converts the input string to all lower case characters
*/
std::string MaterialFactoryUserCreate::toLower(std::string & input)
{
	for (int i = 0; i < input.length(); i++)
	{
		input[i] = tolower(input[i]);
	}
	return input;
}

/*
* Heavily based on:
* http://www.cplusplus.com/reference/ctime/mktime/
*/
const long MaterialFactoryUserCreate::messageGetDate(const std::string & message)
{

	projectViewer->displayMessage(message);

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
			projectViewer->displayMessage("Enter Year: ", false); year = stoi(getUserInput());
			projectViewer->displayMessage("Enter Month: ", false); month = stoi(getUserInput());
			projectViewer->displayMessage("Enter Day: ", false); day = stoi(getUserInput());
		}
		catch (std::invalid_argument ia)
		{
			validInput = false;
			projectViewer->displayMessage("Invalid input please re enter");
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
				projectViewer->displayMessage("invalid date please re enter");
		}
	}

	return timestamp;
}
