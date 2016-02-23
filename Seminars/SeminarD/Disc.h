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
	virtual SDI::DynArray<std::string> getLanguagetracks();
	virtual void setLanguageTracks(const SDI::DynArray<std::string> languageTracks);
	virtual void addLanguageTrack(std::string);

	virtual void setBonusFeatures(const SDI::DynArray<std::string> bonusFeatures);
	virtual SDI::DynArray<std::string> setBonusFeatures() const;


};

#endif // !DISC_H
