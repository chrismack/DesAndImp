#pragma once
#include "Logger.h"
#include "LoggerHandler.h"
class EveryFunction
{
private:
	SDI::Logger* localLogger;

	void callAllLogs();
	void everyFunction();

public:
	EveryFunction();
	~EveryFunction();
};

