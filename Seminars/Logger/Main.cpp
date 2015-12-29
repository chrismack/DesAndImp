// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"
#include <iostream>

int main(int argc, char * argv[])
{
	Logger logger;

	logger.info("Hello");
	logger.setLogLevel(Logger::LogLevel::INFO);
	std::cout << logger.getLogLevelString() << std::endl;
	logger.warning("This is a warning");
	logger.info("This is info");
	system("pause");
    return 0;
}

