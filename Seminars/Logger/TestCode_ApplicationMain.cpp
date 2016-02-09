#include "TestCode_ApplicationMain.h"

#include <thread>
#include <chrono>

TestCode_ApplicationMain::TestCode_ApplicationMain()
{
	bool breakLoop = true;

	TestCode_LoggerHandler::getHandler()->logger = new SDI::Logger(TestCode_LoggerHandler::getHandler()->argc, TestCode_LoggerHandler::getHandler()->argv, true);
	
	logger = TestCode_LoggerHandler::getHandler()->logger;

	logger->info("PRE TEST");

	logger->setConsleOutput(true);
	logger->setPrefixing(true);
	
	logger->setLogLevel(SDI::Logger::LogLevel::ALL);

	logger->info(" < Info prefix before");
	logger->setLevelPrefixString(SDI::Logger::LogLevel::INFO, "[NewInfo]");
	logger->setTimestamping(true);
	logger->info(" < Prefixes can be changed");

	system("pause");

	// Debug messages will only show up if the debug level is set or if the IDE is in debug mode
	logger->debug("This is a debug message");
	
	// Copy constructor for Logger using handler
	TestCode_LoggerHandler::getHandler()->logger2 = new SDI::Logger(false, (logger->getPath() != "Log.log"));
	copiedLogger = TestCode_LoggerHandler::getHandler()->logger2;
	copiedLogger->setConsleOutput(true);
	copiedLogger->setLogLevel(SDI::Logger::LogLevel::WARNING);

	// Creating a new thread to show logger is thread safe
	std::thread t1(&TestCode_ApplicationMain::taskTest, this);
	t1.detach();

	for (int i = 0; i < 20; i++)
	{
		if (breakLoop && i == 10)
		{
			// Warning messages
			logger->warning("break loop is enabled!");
			logger->setTimestamping(!logger->isTimestamping());
			break;
		}
		logger->info("The loop number is " + std::to_string(i));
		std::this_thread::sleep_for(std::chrono::milliseconds(450));
	}

	copiedLogger->warning("copied logger : warning test");

	try
	{
		int userEnter = 0;
		std::cout << "enter 10" << std::endl;
		std::cin >> userEnter;

		if (userEnter != 10)
		{
			throw std::exception("Number entered != 10");
		}

		copiedLogger->debug("10 was entered");

	}
	catch (std::exception e)
	{
		logger->error(e.what());
	}

	logger->debug("Calling everyfunction!");

	TestCode_EveryFunction every;
	TestCode_Calculator calc;

	logger->error("Main thread ended! dumping logs");
	logger->dumpLogs(SDI::Logger::LogLevel::INFO);
	logger->dumpAllOrdered();

}

TestCode_ApplicationMain::~TestCode_ApplicationMain()
{
}

void TestCode_ApplicationMain::taskTest()
{
	logger->info("This is a thread test");

	for (int i = 0; i < 20; i++)
	{
		logger->logFormatted(SDI::Logger::LogLevel::INFO, "This is a test of thread : %d", i);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}