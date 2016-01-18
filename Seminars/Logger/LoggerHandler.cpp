#pragma once

#ifndef LOGGERHANDLER_CPP
#define LOGGERHANDLER_CPP

#include "LoggerHandler.h"

LoggerHandler* LoggerHandler::instance;

LoggerHandler::LoggerHandler()
{
	LoggerHandler::instance = this;
}

LoggerHandler::LoggerHandler(int argc, char * argv[])
{
	LoggerHandler::instance = this;
	this->argc = argc;
	this->argv = argv;
}


LoggerHandler::~LoggerHandler()
{
}

/*
 * Return this class
 * If this class has not been initalised create a new instance;
 */
LoggerHandler* LoggerHandler::getHandler()
{
	if (LoggerHandler::instance == nullptr)
	{
		LoggerHandler::instance = new LoggerHandler();
	}
	return LoggerHandler::instance;
}

#endif // LOGGERHANDLER