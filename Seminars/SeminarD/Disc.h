#pragma once

#ifndef DISC_H
#define DISC_H

#include "Material.h"

#include "../SeminarB/DynArray.h"
#include <string>

class Disc : public Material
{
private:
	SDI::DynArray<std::string> languageTracks_;
	SDI::DynArray<std::string> bounsFeatures_;

public:
	Disc();
	~Disc();
	
	SDI::DynArray<std::string> getLanguagetracks();
	void setLanguageTracks(const SDI::DynArray<std::string> languageTracks);
	void addLanguageTrack(std::string);

	void setBonusFeatures(const SDI::DynArray<std::string> bonusFeatures);
	SDI::DynArray<std::string> getBonusFeatures();


};

#endif // !DISC_H
