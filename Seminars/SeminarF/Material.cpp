#ifndef MATERIAL_CPP
#define MATERIAL_CPP

#define _CRT_SECURE_NO_WARNINGS // Used for strtok doesn't compile with out

#include "stdafx.h"
#include "Material.h"

#include <sstream>


Material::Material()
{
}


Material::~Material()
{
}

int Material::getId() const
{
	return id;
}

std::string Material::getFilmTitle() const
{
	return filmTitle;
}

std::string Material::getFormat() const
{
	return format;
}

std::string Material::getAudioFormat() const
{
	return audioFormat;
}

unsigned int Material::getRunTime() const
{
	return runTime;
}

std::string Material::getLanguage() const
{
	return language;
}

float Material::getRetailPrice() const
{
	return retailPrice;
}

std::string Material::getSubtitles() const
{
	return subtitles;
}

std::pair<int, int> Material::getAspectRatio() const
{
	return frameAspect;
}

void Material::setID(const int id)
{
	this->id = id;
}

void Material::setFilmTitle(const std::string filmTitle)
{
	this->filmTitle = filmTitle;
}

void Material::setFormat(const std::string format)
{
	this->format = format;
}

void Material::setAudioFormat(std::string audioFormat)
{
	this->audioFormat = audioFormat;
}

void Material::setRunTime(const unsigned int runTime)
{
	this->runTime = runTime;
}

void Material::setLanguage(const std::string language)
{
	this->language = language;
}

void Material::setRetailPrice(const float retialPrice)
{
	this->retailPrice = retialPrice;
}

void Material::setSubtitles(const std::string subtitles)
{
	this->subtitles = subtitles;
}

void Material::setAspectRation(const std::pair<int, int> aspectRatio)
{
	this->frameAspect = aspectRatio;
}

void Material::populate(const std::vector<std::string> elements)
{
	id = stoi(elements[0]);
	filmTitle = elements[1];
	format = elements[2];
	audioFormat = elements[3];
	runTime = stoi(elements[4]);
	language = elements[5];
	retailPrice = stof(elements[6]);
	subtitles = elements[7];
	frameAspect.first = stoi(split(elements[8], ":")[0]);
	frameAspect.second = stoi(split(elements[8], ":")[1]);
}

std::vector<std::string> Material::split(std::string string, std::string del)
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

std::vector<std::string> Material::toArray()
{
	std::vector<std::string> materialArray;

	materialArray.push_back(std::to_string(id));
	materialArray.push_back(filmTitle != "" ? filmTitle : " ");
	materialArray.push_back(format != "" ? format : " ");
	materialArray.push_back(audioFormat != "" ? audioFormat : " ");
	materialArray.push_back(std::to_string(runTime));
	materialArray.push_back(language != "" ? language : " ");
	materialArray.push_back(std::to_string(retailPrice));
	materialArray.push_back(subtitles != "" ? subtitles : " ");
	materialArray.push_back(std::to_string(frameAspect.first) + ":" + std::to_string(frameAspect.second));

	return materialArray;
}

#endif // !MATERIAL_CPP
