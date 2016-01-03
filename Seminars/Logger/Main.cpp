// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#include <iostream>
#include <ctime>

using namespace SDI;

int main(int argc, char * argv[])
{
	Logger logger(argc, argv);
	
	logger.info("Hello");
	//logger.setLogLevel(Logger::LogLevel::INFO);
	std::cout << logger.getLogLevelString() << std::endl;
	logger.info("This is info");
	logger.setLogLevel(Logger::LogLevel::ALL);
	logger.warning("This is a warning");
	system("pause");
    return 0;
}

