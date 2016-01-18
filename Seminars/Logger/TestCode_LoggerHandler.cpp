#pragma once

#ifndef TestCode_LoggerHandler_CPP
#define TestCode_LoggerHandler_CPP

#include "TestCode_LoggerHandler.h"

TestCode_LoggerHandler* TestCode_LoggerHandler::instance;

TestCode_LoggerHandler::TestCode_LoggerHandler()
{
	TestCode_LoggerHandler::instance = this;
}

TestCode_LoggerHandler::TestCode_LoggerHandler(int argc, char * argv[])
{
	TestCode_LoggerHandler::instance = this;
	this->argc = argc;
	this->argv = argv;
}


TestCode_LoggerHandler::~TestCode_LoggerHandler()
{
}

/*
 * Return this class
 * If this class has not been initalised create a new instance;
 */
TestCode_LoggerHandler* TestCode_LoggerHandler::getHandler()
{
	if (TestCode_LoggerHandler::instance == nullptr)
	{
		TestCode_LoggerHandler::instance = new TestCode_LoggerHandler();
	}
	return TestCode_LoggerHandler::instance;
}

#endif // TestCode_LoggerHandler