#pragma once

#ifndef DISC_H
#define DISC_H

#include "Material.h"

#include "../SeminarB/DynArray.h"
#include <string>

class Disc : public Material
{
private:
	SDI::DynArray<std::string> languageTracks;

public:
	Disc();
	~Disc();
	virtual SDI::DynArray<std::string> getLanguagetracks();
};

#endif // !DISC_H
