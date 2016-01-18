#pragma once

#include "Logger.h"
#include "TestCode_LoggerHandler.h"
#include "TestCode_EveryFunction.h"

class TestCode_ApplicationMain
{
private :
	/*
	 * Local copies of the loggers do not need to be used
	 * just here for convenience 
	 */
	SDI::Logger* logger;
	SDI::Logger* copiedLogger;

public:
	TestCode_ApplicationMain();
	~TestCode_ApplicationMain();

	/*
	 * Thread task to show logger is thread safe
	 */
	void taskTest();
};

