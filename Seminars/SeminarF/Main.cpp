// SeminarF.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>

#include "stdafx.h"

#include "LogHandler.h"
#include "ProjectController.h"

int main(int argc, char* argv[])
{
	LogHandler::getHandler()->logger = new SDI::Logger(argc, argv, false);
	ProjectController projectController(LogHandler::getHandler()->logger);
	//ProjectManager projectManager(LogHandler::getHandler()->logger);

	return 0;
}

