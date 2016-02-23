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



#endif // !DISC_CPP
