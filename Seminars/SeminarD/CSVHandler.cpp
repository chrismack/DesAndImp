#include "stdafx.h"
#include "SVHandler.h"

#include <iostream>
#include <fstream>


CSVHandler::CSVHandler()
{
}


CSVHandler::~CSVHandler()
{
}

void CSVHandler::readLinesFromFile(std::string fileName)
{
	std::string line;
	std::ifstream cvsFile(fileName);
	if (cvsFile.is_open)
	{
		while (std::getline(cvsFile, line))
		{
			lines_.push_back(line);
		}
		cvsFile.close();
	}
}

SDI::DynArray<std::string> CSVHandler::getLines()
{
	return lines_;
}

void CSVHandler::addLineToFile(std::string fileName, std::string line)
{
	std::ofstream cvsFile(fileName);
	if (cvsFile.is_open)
	{
		cvsFile << line << std::endl;
		cvsFile.close();
	}
}

void CSVHandler::generateClassesFromLines()
{
}

void CSVHandler::generateClassFromLine(std::string line)
{
}
