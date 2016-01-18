#include "TestCode_EveryFunction.h"

TestCode_EveryFunction::TestCode_EveryFunction()
{

	TestCode_LoggerHandler::getHandler()->everyFunction = new SDI::Logger("everyFunction.log", false, true);
	localLogger = TestCode_LoggerHandler::getHandler()->everyFunction;
	localLogger->setConsleOutput(true);
	localLogger->setLogLevel(SDI::Logger::LogLevel::ALL);

	localLogger->info("Every Function logger init!");
	everyFunction();
}


TestCode_EveryFunction::~TestCode_EveryFunction()
{
}

void TestCode_EveryFunction::callAllLogs()
{
	localLogger->info("\n");
	localLogger->log(SDI::Logger::LogLevel::INFO, "log functions at info level");
	localLogger->info("Info function");
	localLogger->debug("Debug function");
	localLogger->warning("Warning function");
	localLogger->error("Error function");
}

void TestCode_EveryFunction::everyFunction()
{
	// All logging functions
	callAllLogs();


	// Prefixes!
	localLogger->info("is Prefixing Enabled? : " + std::to_string(localLogger->isPrefixing()));
	if (!localLogger->isPrefixing())
	{
		// Set logging to the opposite of it's current prefix logging state
		localLogger->setPrefixing(!localLogger->isPrefixing());
	}

	//Prefixes should be enabled now!
	callAllLogs();

	//Modify Prefixes
	localLogger->setLevelPrefixString(SDI::Logger::LogLevel::INFO, "[NewInfoPrefix]");
	localLogger->setLevelPrefixString(SDI::Logger::LogLevel::DEBUG, "[NewDebugPrefix]");
	localLogger->setLevelPrefixString(SDI::Logger::LogLevel::WARNING, "[NewWarningPrefix]");
	localLogger->setLevelPrefixString(SDI::Logger::LogLevel::ERROR, "[NewErrorPrefix]");

	localLogger->getLevelPrefix(SDI::Logger::LogLevel::INFO);
	localLogger->getLevelPrefix(SDI::Logger::LogLevel::DEBUG);
	localLogger->getLevelPrefix(SDI::Logger::LogLevel::WARNING);
	localLogger->getLevelPrefix(SDI::Logger::LogLevel::ERROR);

	if (localLogger->getLevelPrefix(SDI::Logger::LogLevel::INFO) == "[NewInfoPrefix]")
	{
		localLogger->info("New logging level has been set!");
	}

	callAllLogs();

	//Time stamping 
	localLogger->info("is Timestamping Enabled? : " + std::to_string(localLogger->isTimestamping()));
	if (!localLogger->isTimestamping())
	{
		// Set logging to the opposite of it's current prefix logging state
		localLogger->setTimestamping(!localLogger->isTimestamping());
	}

	callAllLogs();

	localLogger->info("Change time stamp string");

	localLogger->setTimeStampsString("<%y-%d-%m>");

	callAllLogs();

	*localLogger << "Test" << "\n";

	localLogger->info("Example of formatted logging");
	for (int i = 0; i < 10; i++)
	{
		localLogger->logFormatted(SDI::Logger::LogLevel::INFO, "Formatted logging is good for loops. Loop count : %d", i);
	}

	localLogger->setLogLevel(SDI::Logger::LogLevel::INFO);
	localLogger->debug("debug with debugging mode enabled");
	localLogger->setDebugLoggingMode(false);
	localLogger->debug("Debug messages wont show in debug unless log level is set to debug and DebugLogging mode is true");

	if (localLogger->getLogLevelString() != "ALL")
	{
		localLogger->setLogLevel(SDI::Logger::LogLevel::ALL);
	}
	

	localLogger->~Logger();
}