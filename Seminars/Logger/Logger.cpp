#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "Logger.h"

#include <iostream>

namespace SDI
{

	/*
	 * Default log location and name
	 */
	Logger::Logger()
	{
		if (!logFile_.is_open())
		{
			logFile_.open("Log.log");
		}
	}

	/*
	 * Initalise Logger with path to log file
	 */
	Logger::Logger(std::string logPath)
	{
		if (!logFile_.is_open())
		{
			logFile_.open(logPath);
		}
	}

	Logger::Logger(int argc, char * argv[])
	{
		// Instance of line parser
		SDI::LineParse lineparse;

		// All of the commandLine arguments
		std::vector<std::string> arguments = lineparse.parseArgs(argc, argv);

		// Set of all command line flags
		std::set<char> argFlags = lineparse.parseArgsFlags(argc, argv);
		std::set<char>::iterator iterator;
		// Only include flags that are in the default flagSet
		argFlags = removeInvalidFlags(iterator, argFlags);
		processFlags(iterator, argFlags);

		std::cout << currentDateTime() << std::endl;

		if (!logFile_.is_open())
		{
			logFile_.open("Log.log");
		}

		/*
			Logger::startEndIndex argumentBounds;
				// Check if command line contains Logger

			if ((argumentBounds.first = getStartEndArgsIndex(arguments).first > -1) && (argumentBounds.second = getStartEndArgsIndex(arguments).second > -1))
			{
				for (int i = argumentBounds.first; i < argumentBounds.second; i++)
				{
				}
			}
		*/

	}



	/*
	 * Deconstruct Logger
	 */
	Logger::~Logger()
	{
		if (logFile_.is_open())
			logFile_.close();
	}

	/*
	 * ===========================
	 * Different types of logging
	 * ===========================
	 */

	void Logger::log(Logger::LogLevel level, std::string message)
	{
		logAtLevel(level, message);
	}

	void Logger::info(std::string message)
	{
		logAtLevel(LogLevel::INFO, message);
	}

	void Logger::debug(std::string message)
	{
		logAtLevel(LogLevel::DEBUG, message);
	}

	void Logger::warning(std::string message)
	{
		logAtLevel(LogLevel::WARNING, message);
	}

	void Logger::error(std::string message)
	{
		logAtLevel(LogLevel::ERROR, message);
	}

	/*
	 * ===============================
	 * End different types of logging
	 * ===============================
	 */

	 /*
	  * Set the logLevel to a specified LogLevel
	  */
	void Logger::setLogLevel(LogLevel logLevel)
	{
		loggingLevel_ = logLevel;
	}


	/*
	 * Returns the loggingLevel as enum type
	 */
	Logger::LogLevel Logger::getLogLevel()
	{
		return loggingLevel_;
	}

	/*
	 * returns the loggingLevel as a string
	 */
	std::string Logger::getLogLevelString()
	{
		if (enumStrings_.count(loggingLevel_) > 0)
		{
			return enumStrings_[loggingLevel_].first;
		}

		return "[ERROR] Could not convert logging level to string";
	}

	void Logger::enableTimeStamps(bool enabled)
	{
		timeLogging_ = enabled;
	}

	void Logger::setTimeStampsString(char * timeFormat)
	{
		timeFormat_ = timeFormat;
	}

	std::set<char> Logger::removeInvalidFlags(std::set<char>::iterator it, std::set<char> argFlags)
	{
		std::set<char> validFlags;

		for (it = argFlags.begin(); it != argFlags.end(); ++it)
		{
			if (flagSet_.find(*it) != flagSet_.end())
			{
				validFlags.insert(*it);
			}
		}
		return validFlags;
	}

	void Logger::processFlags(std::set<char>::iterator it, std::set<char> args)
	{
		// Logging level flags
		std::map<char, Logger::LogLevel> flagLevel =
		{
			{'a', Logger::LogLevel::ALL},
			{'i', Logger::LogLevel::INFO},
			{'d', Logger::LogLevel::DEBUG},
			{'w', Logger::LogLevel::WARNING},
			{'e', Logger::LogLevel::ERROR},
			{'n', Logger::LogLevel::NONE}
		};


		for (it = args.begin(); it != args.end(); ++it)
		{
			// If the flag is an uppercase char wait until we process flagValues

			if (*it < 97)
				continue;

			if (flagLevel.count(*it) > 0)
			{
				setLogLevel(flagLevel[*it]);
			}
			else if (*it == 74) //t
			{
				// Enable time stamps
				timeLogging_ = true;
			}
			else if (*it == 70) //p
			{
				// Enable logging prefixes
				logPrefixes_ = true;
			}
			else if (*it == 63) //c
			{
				// Enable increamental / concurrent file name
			}
			else if (*it == 78) //x
			{
				// Split logging states into different files
			}
		}
	}

	/*

	Logger::startEndIndex Logger::getStartEndArgsIndex(std::vector<std::string> arguments)
	{
		Logger::startEndIndex startingEndingIndex = { -1,-1 };

		for (int i = 0; i < arguments.size(); i++)
		{
			if (arguments[i] == "Logger")
			{
				startingEndingIndex.first = i;
			}
			if (startingEndingIndex.first > -1 && i > startingEndingIndex.first && arguments[i][0] != '-')
			{
				startingEndingIndex.second = i;
			}
		}
		return startingEndingIndex;
	}
	*/

	/*
	 * Initalises map with LogLevel and Array to log messages too
	 */
	void Logger::setUpMapArray(LogLevel level)
	{
		// Create array to hold messages
		SDI::DynArray<std::string> messageArray;
		// Inset loggingLevel and array to map
		loggingMap_.insert(std::pair<LogLevel, SDI::DynArray<std::string>>(level, messageArray));
	}

	/*
	 * Writes message at specified LogLevel
	 */
	void Logger::logAtLevel(LogLevel level, std::string message)
	{
		// Check if logLevel array has been setup in map
		if (loggingMap_.count(level) > 0)
		{
			setUpMapArray(level);
		}
		// Insert message into the dynamic array
		loggingMap_[level].push_back(message);

		// If the current logging level is the same as loggingLevel
		if (shouldLog(level))
		{
			if (logPrefixes_)
			{
				message = enumStrings_[level].second + message;
			}
			if (timeLogging_)
			{
				message = currentDateTime() + message;
			}

			printLineToLog(message);
			if (logToConsole_)
			{
				printToConsole(message);
			}
		}
	}

	/*
	 * Prints messages to the console
	 */
	void Logger::printToConsole(std::string message)
	{
		std::cout << message << std::endl;
	}

	/*
	 * Writes messages to the logFile
	 */
	void Logger::printLineToLog(std::string line)
	{
		if (logFile_.is_open())
		{
			logFile_ << line << std::endl;
		}
	}

	/*
	 * If the level of logging allows the message to be logged
	 */
	bool Logger::shouldLog(LogLevel level)
	{
		/*
		 * Check if logged message is at correct level to log
		 * Or the logger is set to log everything
		 * And the Logger isn't set to not log anything
		 */

		if ((loggingLevel_ == level || loggingLevel_ == LogLevel::ALL) && loggingLevel_ != LogLevel::NONE)
		{
			return true;
		}
		return false;
	}

	/*
	 * returns formatted time
	 */

	std::string Logger::currentDateTime()
	{
		time_t currentTime = time(0);
		tm *timeStruct = localtime(&currentTime);
		char buffer[256];

		std::strftime(buffer, sizeof(buffer), timeFormat_, timeStruct);
		return buffer;
	}

} // Namespace

#endif // LOGGER_CPP