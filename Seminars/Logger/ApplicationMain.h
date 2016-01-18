#pragma once

#include "Logger.h"

class ApplicationMain
{
private :
	/*
	 * Local copies of the loggers do not need to be used
	 * just here for convenience 
	 */
	SDI::Logger* logger;
	SDI::Logger* copiedLogger;

public:
	ApplicationMain();
	~ApplicationMain();

	/*
	 * Thread task to show logger is thread safe
	 */
	void taskTest();
};

