#pragma once

#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include "Logger.h"
#include <string>


class TestCode_LoggerHandler
{
public:

	/*
	 * Static instance of this class 
	 */
	static TestCode_LoggerHandler* instance;

	/*
	 * commandLine args that can be passed to loggers 
	 */
	int argc;
	char ** argv;

	/*
	 * Path name that can be passed to the loggers
	 */
	std::string  path;

	/*
	 * instances of loggers that will be accessable from the global instance;
	 */
	SDI::Logger* logger;
	SDI::Logger* logger2;
	SDI::Logger* everyFunction;

	/*
	 * Constructors
	 */
	TestCode_LoggerHandler();
	TestCode_LoggerHandler(int argc, char * argv[]);
	~TestCode_LoggerHandler();

	/*
	 * returns a singleton instance of the logger
	 */
	static TestCode_LoggerHandler* getHandler();
};

#endif // LOGGERHANDLER