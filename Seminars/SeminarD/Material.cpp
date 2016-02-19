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
	return 0;
}

std::string Material::getFilmTitle() const
{
	return std::string();
}

std::string Material::getFormat() const
{
	return std::string();
}

std::string Material::getAudioFormat() const
{
	return std::string();
}

unsigned int Material::getRunTime() const
{
	return 0;
}

std::string Material::getLanguage() const
{
	return std::string();
}

float Material::retailPrice() const
{
	return 0.0f;
}

std::string Material::getSubtitles() const
{
	return std::string();
}

std::pair<int, int> Material::getAspectRatio() const
{
	return std::pair<int, int>();
}

#endif // !MATERIAL_CPP
