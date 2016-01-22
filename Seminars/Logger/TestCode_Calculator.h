#pragma once

#include <string>

#include "TestCode_LoggerHandler.h"
#include "Logger.h"

class TestCode_Calculator
{
public:
	TestCode_Calculator();
	~TestCode_Calculator();

private:

	SDI::Logger* logger = TestCode_LoggerHandler::getHandler()->logger2;

	int add(int, int);
	int subtract(int, int);
	int multiply(int, int);
	int divide(int, int);

	int stringToInt(std::string);
};

