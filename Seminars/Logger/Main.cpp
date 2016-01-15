// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#include "Test.h"
#include <iostream>
#include <ctime>

using namespace SDI;

int main(int argc, char * argv[])
{
	//Test(argc, argv);
	
	Logger logger(argc, argv);
		
	logger.setConsleOutput(true);
	logger.error("This is a Error");
	logger.setLogLevel(Logger::LogLevel::INFO);
	logger.error("This shouldn't print");
	logger.info("This is info");
	logger.log(Logger::LogLevel::INFO, "This is a info log");
	logger.logFormatted(Logger::LogLevel::INFO, "Message is:%s number is: %d", "Test", 6);
	std::cout << logger.getLogLevelString() << std::endl;

	//logger.info("Hello");
	//logger.warning("This is second!");
	////logger.setLogLevel(Logger::LogLevel::INFO);
	//std::cout << logger.getLogLevelString() << std::endl;
	//logger.info("This is info");
	//logger.warning("This shouldn't appear!");
	//logger.setLogLevel(Logger::LogLevel::ALL);
	//logger.warning("This is a warning");
	//logger.dumpLogs(Logger::LogLevel::INFO);
	////logger.dumpAllOrdered();
	system("pause");
    return 0;
}

