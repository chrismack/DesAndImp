#ifndef DISC_CPP
#define DISC_CPP

#include "stdafx.h"
#include "Disc.h"

Disc::Disc()
{
}


Disc::~Disc()
{
}

SDI::DynArray<std::string> Disc::getLanguagetracks()
{
	return this->languageTracks_;
}

void Disc::setLanguageTracks(const SDI::DynArray<std::string> languageTracks)
{
	this->languageTracks_ = languageTracks;
}

void Disc::addLanguageTrack(std::string languageTrack)
{
	languageTracks_.append(languageTrack);
}

void Disc::setBonusFeatures(const SDI::DynArray<std::string> bonusFeatures)
{
	bounsFeatures_ = bonusFeatures;
}

SDI::DynArray<std::string> Disc::getBonusFeatures()
{
	return this->bounsFeatures_;
}



#endif // !DISC_CPP
