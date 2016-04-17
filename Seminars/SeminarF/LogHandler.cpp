#pragma once

#ifndef LOGHANDLER_CPP
#define LOGHANDLER_CPP

#include "LogHandler.h"

LogHandler* LogHandler::INSTANCE;

LogHandler::LogHandler()
{
	LogHandler::INSTANCE = this;
}

LogHandler::LogHandler(int argc, char * argv[])
{
	LogHandler::INSTANCE = this;
	this->argc = argc;
	this->argv = argv;
}


LogHandler::~LogHandler()
{
	delete logger;
}

void LogHandler::setArgc(int argc)
{
	this->argc = argc;
}

void LogHandler::setArgv(char* argv[])
{
	this->argv = argv;
}

/*
* Return this class
* If this class has not been initalised create a new instance;
*/
LogHandler* LogHandler::getHandler()
{
	if (LogHandler::INSTANCE == nullptr)
	{
		LogHandler::INSTANCE = new LogHandler();
	}
	return LogHandler::INSTANCE;
}

#endif // TestCode_LoggerHandler