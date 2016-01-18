#pragma once
#include "Logger.h"
#include "TestCode_LoggerHandler.h"
class TestCode_EveryFunction
{
private:
	SDI::Logger* localLogger;

	void callAllLogs();
	void everyFunction();

public:
	TestCode_EveryFunction();
	~TestCode_EveryFunction();
};

