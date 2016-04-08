#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#pragma once

#include <string>
#include "Logger.h"

class LogHandler
{
private:

	/*
	* commandLine args that can be passed to loggers
	*/
	int argc;
	char ** argv;

	/*
	* Path name that can be passed to the loggers
	*/
	std::string  path;

public:
	static LogHandler* INSTANCE;

	/*
	* instances of loggers that will be accessable from the global instance;
	*/
	SDI::Logger* logger;
	
	/*
	* Constructors
	*/
	LogHandler();
	LogHandler(int argc, char * argv[]);
	~LogHandler();

	/*
	 * Setters for command line args
	 */

	void setArgc(int argc);
	void setArgv(char* argv[]);

	/*
	* returns a singleton instance of the logger
	*/
	static LogHandler* getHandler();
};

#endif // !LOGHANDLER
