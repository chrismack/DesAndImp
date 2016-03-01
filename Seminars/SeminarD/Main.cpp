// Main.cpp : Defines the entry point for the console application.
//

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

int main(int argc, char * argv[])
{
	Material* mat = new SingleDVD;
	SingleDVD* b1 = static_cast<SingleDVD*>(mat);
	
	

	//BlueRay* dvd = new BlueRay();
	
	b1->setID(1);
	b1->setFilmTitle("Test");
	b1->setFormat("BluRay");
	b1->setAudioFormat("DTS");
	b1->setRunTime(3600);
	
	std::vector<std::string> langauages;
	langauages.push_back("english");
	langauages.push_back("french");
	b1->setLanguage("english");
	b1->setSubtitles("english");
	b1->setLanguageTracks(langauages);
	b1->setRetailPrice(10.00);

	std::vector<std::string> subs;
	subs.push_back("english");
	subs.push_back("french");
	b1->setSubtitleTracks(subs);
	b1->setAspectRation(std::make_pair<int, int>(16, 9));
	
	std::vector<std::string> audio;
	//audio.push_back("audio 1");
	//audio.push_back("audio 2");
	b1->setAudioTracks(audio);
	
	b1->setPackageType("plastic");
	b1->setPackageDimensions(std::tuple<int, int, int>(1000, 20, 100));

	std::vector<std::string> content;
	content.push_back("chap1");
	content.push_back("chap2");
	content.push_back("chap3");
	b1->setContent(content);

	std::vector<std::string> bonus;
	bonus.push_back("BHS1");
	bonus.push_back("BHS2");
	bonus.push_back("BHS3");
	b1->setBonusFeatures(bonus);
	std::cout << b1->getId() << std::endl;
	std::cout << std::get<0>(b1->getPackageSize()) << std::endl;
	std::cout << b1->toString() << std::endl;
	b1->getBonusFeatures();


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

	std::cout << d1->toString() << std::endl;

	Material* mat2 = new ComboBox;
	ComboBox* c1 = static_cast<ComboBox*>(mat2);

	c1->setID(1);
	c1->setFilmTitle("Test");
	c1->setFormat("BluRay");
	c1->setAudioFormat("DTS");
	c1->setRunTime(3600);
	c1->setLanguage("english");
	c1->setRetailPrice(10.00);
	c1->setSubtitles("french");
	c1->setAspectRation(std::make_pair<int, int>(16, 9));
	c1->setPackageType("cardboard");
	c1->setPackageDimensions(std::tuple<int, int, int>(1000, 20, 100));
	

	std::vector<Disc*> dvdList;
	dvdList.push_back(b1);
	dvdList.push_back(b1);
	dvdList.push_back(b1);
	c1->setContent(dvdList);

	std::cout << c1->toString() << std::endl;

	system("pause");
	return 0;
}

