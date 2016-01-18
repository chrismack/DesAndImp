#pragma once

#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include "Logger.h"
#include <string>


class LoggerHandler
{
public:

	/*
	 * Static instance of this class 
	 */
	static LoggerHandler* instance;

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
	LoggerHandler();
	LoggerHandler(int argc, char * argv[]);
	~LoggerHandler();

	/*
	 * returns a singleton instance of the logger
	 */
	static LoggerHandler* getHandler();
};

#endif // LOGGERHANDLER