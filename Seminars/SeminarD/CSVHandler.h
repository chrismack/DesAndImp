#pragma once

#include <string>
#include "../SeminarB/DynArray.h"

class CSVHandler
{
private:
	static CSVHandler* INSTANCE;
	SDI::DynArray<std::string> lines_;
public:
	CSVHandler();
	~CSVHandler();

	static CSVHandler* getCVSInstance();

	void readLinesFromFile(std::string fileName);
	SDI::DynArray<std::string> getLines();
	void addLineToFile(const std::string fileName, const std::string line);

	void generateClassesFromLines();
	void generateClassFromLine(const std::string line);
};

