#ifndef MATERIAL_CPP
#define MATERIAL_CPP


#include "stdafx.h"
#include "Material.h"


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

void Material::setRetailPrice(const float runTime)
{
	this->runTime = runTime;
}

void Material::setSubtitles(const std::string subtitles)
{
	this->subtitles = subtitles;
}

void Material::setAspectRation(const std::pair<int, int> aspectRatio)
{
	this->frameAspect = aspectRatio;
}

#endif // !MATERIAL_CPP
