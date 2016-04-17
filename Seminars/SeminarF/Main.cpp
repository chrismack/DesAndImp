// SeminarF.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>

#include "stdafx.h"

#include "LogHandler.h"
#include "ProjectManager.h"


int main(int argc, char* argv[])
{
	LogHandler::getHandler()->logger = new SDI::Logger(argc, argv, false);
	ProjectManager projectManager(LogHandler::getHandler()->logger);

	return 0;
}

