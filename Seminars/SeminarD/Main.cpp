// Main.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS // Used for strtok doesn't compile with out

#include "stdafx.h"

#include <iostream>
#include <tuple>
#include <vector>

#include "BlueRay.h"
#include "Singledvd.h"
#include "ComboBox.h"
#include "VHS.h"
#include "DoubleDVD.h"
#include "ComboBox.h"

#include "CSVHandler.h"

#include "MaterialFactory.h"

#include "Project.h"

int main(int argc, char * argv[])
{
	//Material* mat = new BlueRay;
	//BlueRay* b1 = static_cast<BlueRay*>(mat);
	//
	//

	//BlueRay* dvd = new BlueRay();
	//
	//b1->setID(1);
	//b1->setFilmTitle("Test");
	//b1->setFormat("BluRay");
	//b1->setAudioFormat("DTS");
	//b1->setRunTime(3600);
	//
	//std::vector<std::string> langauages;
	//langauages.push_back("english");
	//langauages.push_back("french");
	//b1->setLanguage("english");
	//b1->setSubtitles("english");
	//b1->setLanguageTracks(langauages);
	//b1->setRetailPrice(10.00);

	//std::vector<std::string> subs;
	//subs.push_back("english");
	//subs.push_back("french");
	//b1->setSubtitleTracks(subs);
	//b1->setAspectRation(std::make_pair<int, int>(16, 9));
	//
	//std::vector<std::string> audio;
	////audio.push_back("audio 1");
	////audio.push_back("audio 2");
	//b1->setAudioTracks(audio);
	//
	//b1->setPackageType("plastic");
	//b1->setPackageDimensions(std::tuple<int, int, int>(1000, 20, 100));

	//std::vector<std::string> content;
	//content.push_back("chap1");
	//content.push_back("chap2");
	//content.push_back("chap3");
	//b1->setContent(content);

	//std::vector<std::string> bonus;
	//bonus.push_back("BHS1");
	//bonus.push_back("BHS2");
	//bonus.push_back("BHS3");
	//b1->setBonusFeatures(bonus);
	//std::cout << b1->getId() << std::endl;
	//std::cout << std::get<0>(b1->getPackageSize()) << std::endl;
	//b1->getBonusFeatures();


	Material* mat1 = new DoubleDVD;
	DoubleDVD* d1 = static_cast<DoubleDVD*>(mat1);

	d1->setID(1);
	d1->setFilmTitle("Test");
	d1->setFormat("BluRay");
	d1->setAudioFormat("DTS");
	d1->setRunTime(3600);

	std::map<int, std::vector<std::string>> langauagesMap;
	langauagesMap[0].push_back("english");
	langauagesMap[0].push_back("french");
	langauagesMap[1].push_back("english1");
	langauagesMap[1].push_back("french1");
	d1->setLanguageTracks(langauagesMap);
	d1->setRetailPrice(10.00);
	d1->setLanguage("english");
	d1->setSubtitles("english");

	std::map<int, std::vector<std::string>> subsMap;
	subsMap[0].push_back("english");
	subsMap[0].push_back("french");
	subsMap[1].push_back("english1");
	subsMap[1].push_back("french1");
	d1->setSubtitleTracks(subsMap);
	d1->setAspectRation(std::make_pair<int, int>(16, 9));

	std::map<int, std::vector<std::string>> audioMap;
	audioMap[0].push_back("audio 1");
	audioMap[0].push_back("audio 2");
	audioMap[0].push_back("audio 3");
	audioMap[1].push_back("audio 4");
	d1->setAudioTracks(audioMap);

	d1->setPackageType("plastic");
	d1->setPackageDimensions(std::tuple<int, int, int>(1000, 20, 100));

	std::map<int, std::vector<std::string>> contentMap;
	contentMap[0].push_back("chap1");
	contentMap[0].push_back("chap2");
	contentMap[0].push_back("chap3");
	d1->setContent(contentMap);

	std::map<int, std::vector<std::string>> bonusMap;
	bonusMap[1].push_back("BHS1");
	bonusMap[1].push_back("BHS2");
	bonusMap[1].push_back("BHS3");
	d1->setBonusFeatures(bonusMap);


	//Material* mat2 = new ComboBox;
	//ComboBox* c1 = static_cast<ComboBox*>(mat2);

	//c1->setID(1);
	//c1->setFilmTitle("Test");
	//c1->setFormat("BluRay");
	//c1->setAudioFormat("DTS");
	//c1->setRunTime(3600);
	//c1->setLanguage("english");
	//c1->setRetailPrice(10.00);
	//c1->setSubtitles("french");
	//c1->setAspectRation(std::make_pair<int, int>(16, 9));
	//c1->setPackageType("cardboard");
	//c1->setPackageDimensions(std::tuple<int, int, int>(1000, 20, 100));
	//

	//std::vector<Disc*> dvdList;
	//dvdList.push_back(b1);
	//dvdList.push_back(b1);
	//dvdList.push_back(b1);
	//c1->setContent(dvdList);

	//for (int i = 0; i < c1->toArray().size(); i++)
	//{
	//	std::cout << c1->toArray()[i] << std::endl;
	//}
	//for (int i = 0; i < d1->toArray().size(); i++)
	//{
	//	std::cout << d1->toArray()[i] << std::endl;
	//}

	//// 1,Test,BluRay,DTS,3600,english,10.000000,english,16:9,english|french,english|french,,plastic,1000|20|100,chap1|chap2|chap3,BHS1|BHS2|BHS3


	//std::vector<std::string> stringArray;

	///* http://stackoverflow.com/questions/16286095/similar-function-to-javas-string-split-in-c */

	//std::string s = "1,Test,Combo,DTS,3600,english,10.000000,french,16:9,cardboard,1000 | 20 | 100,[1, Test, BluRay, DTS, 3600, english, 10.000000, english, 16:9, english | french, english | french, , plastic, 1000 | 20 | 100, chap1 | chap2 | chap3, BHS1 | BHS2 | BHS3_1, Test, BluRay, DTS, 3600, english, 10.000000, english, 16 : 9, english | french, english | french, , plastic, 1000 | 20 | 100, chap1 | chap2 | chap3, BHS1 | BHS2 | BHS3_1, Test, BluRay, DTS, 3600, english, 10.000000, english, 16 : 9, english | french, english | french, , plastic, 1000 | 20 | 100, chap1 | chap2 | chap3, BHS1 | BHS2 | BHS3]";
	//std::string dvds = s.substr(s.find('['), s.length());
	//s = s.substr(0, s.find('['));
	//std::string d = ",";

	//char* cstr = const_cast<char*>(s.c_str());
	//char* current;
	//std::vector<std::string> arr;
	//current = strtok(cstr, d.c_str());
	//while (current != NULL)
	//{
	//	arr.push_back(current);
	//	current = strtok(NULL, d.c_str());
	//}
	//arr.push_back(dvds);
	//for (int i = 0; i < arr.size(); i++)
	//{
	//	std::cout << "FROM STRING : ";
	//	std::cout << arr[i] << std::endl;
	//}

	//Material* matt = new ComboBox;
	////ComboBox* b9 = static_cast<ComboBox*>(matt);
	//matt->populate(arr);
	//std::cout << "-----------------------------" << std::endl;
	//for (int i = 0; i < matt->toArray().size(); i++)
	//{
	//	std::cout << matt->toArray()[i] << std::endl;
	//}
	//
	//Project p;
	//p.setTitle("Title");
	//p.setSummary("Sum");
	//p.setGenre("Genre");
	//p.setReleaseDate(1000000000L);
	//std::vector<std::string> filmLocs{ "FilmLoc1", "FilmLoc2" };
	//p.setFilmingLocations(filmLocs);
	//p.setLanguage("language");
	//std::vector<std::string> keyWords{ "keyWords 2", "keyWords 2" };
	//p.setKeywords(keyWords);
	//std::vector<int> weekSales = {1, 4, 6};
	//p.setTicketSales(weekSales);
	//std::vector<Material*> projMats = { b1, d1, matt };
	//p.setMaterials(projMats);

	//for (int i = 0; i < p.toArray().size(); i++)
	//{
	//	std::cout << "PORJECT" << std::endl;
	//	std::cout << p.toArray()[i] << std::endl;
	//}



	std::vector<std::string> projectString;
	
	projectString.push_back("Title");
	projectString.push_back("Sum");
	projectString.push_back("Genre");
	projectString.push_back("1000000000");
	projectString.push_back("FilmLoc1 | FilmLoc2");
	projectString.push_back("language");
	projectString.push_back("keyWords 1 | keyWords 2");
	projectString.push_back("1 | 4 | 6");
	projectString.push_back("{ 1,Test,BluRay,DTS,3600,english,10.000000,english,16:9,english | french,english | french, ,plastic,1000 | 20 | 100,chap1 | chap2 | chap3,BHS1 | BHS2 | BHS3~1,Test,BluRay,DTS,3600,english,10.000000,english,16 : 9,english | french - english1 | french1,english | french - english1 | french1,audio 1 | audio 2 | audio 3 - audio 4,plastic,1000 | 20 | 100,chap1 | chap2 | chap3,-BHS1 | BHS2 | BHS3~1,Test,Combo,DTS,3600,english,10.000000,french,16 : 9,cardboard,1000 | 20 | 100,[1, Test, BluRay, DTS,3600, english,10.000000, english,16:9, english | french, english | french, , plastic,1000 | 20 | 100, chap1 | chap2 | chap3, BHS1 | BHS2 | BHS3_1, Test, BluRay, DTS,3600, english,10.000000, english,16 : 9, english | french, english | french, , plastic,1000 | 20 | 100, chap1 | chap2 | chap3, BHS1 | BHS2 | BHS3_1, Test, DoubleDVD, DTS,3600, english,10.000000, english,16 : 9, english | french, english | french, , plastic,1000 | 20 | 100, chap1 | chap2 | chap3, - BHS1 | BHS2 | BHS3]}");

	Project* project = new Project();
	project->populate(projectString);

	//std::vector<std::string> projectArrayLocal = project->toArray();
	//for (int i = 0; i < projectArrayLocal.size(); i++)
	//{
	//	std::cout << projectArrayLocal[i] << std::endl;
	//}

	CSVHandler csvHandler("sdf.csv", new MaterialFactory());
	//csvHandler.writeToFile(project);
	csvHandler.writeToFile(d1);
	std::vector<Material*> materialsFromFile =  csvHandler.getMaterialsFromFile();

	system("pause");
	return 0;
}

