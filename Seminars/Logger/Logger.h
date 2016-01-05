#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <vector>
#include <map>
#include <set>
#include <list>

#include <ctime>
#include <fstream>

#include "../SeminarB/DynArray.h"
#include "LineParse.h"

namespace SDI
{
	class Logger
	{
	public: // Vasriables

		/*
		 * Different logging levels
		 */
		const enum class LogLevel
		{
			NONE, // Does not write to log
			INFO,
			DEBUG,
			WARNING,
			ERROR,
			ALL // Writes all logs to file
		};


	private: // Variables
		typedef std::pair<std::string, std::string> stringLevelPrefix;

		typedef std::pair<int, std::string> messagePosition;
		typedef SDI::DynArray<messagePosition> orderArray;
		//typedef std::pair<int, SDI::DynArray<std::string>> orderArray;

		/*
		 * Current level of logs that are written to file
		 */
		LogLevel loggingLevel_ = LogLevel::NONE;

		std::ofstream logFile_;
		std::ofstream dumpFile_;

		/*
		 * Map of corrosponding (Enums, String)
		 */
		std::map<LogLevel, stringLevelPrefix> enumStrings_ =
		{
			{Logger::LogLevel::ALL,     {"ALL",     ""         } },
			{Logger::LogLevel::INFO,    {"INFO",    "[INFO]"   } },
			{Logger::LogLevel::DEBUG,   {"DEBUG",   "[DEBUG]"  } },
			{Logger::LogLevel::WARNING, {"WARNING", "[WARNING]"} },
			{Logger::LogLevel::ERROR,   {"ERROR",   "[ERROR]"  } },
			{Logger::LogLevel::NONE,    {"NONE",    ""         } }
		};

		int arrayOrder = 0;

		/*
		 * Map of different logging levels and their arrays
		 */
		std::map<LogLevel, orderArray> loggingMap_;

		bool timeLogging_ = false;
		char * timeFormat_ = "[%d:%m:%y-%T]";

		bool logPrefixes_ = false;
		bool logToConsole_ = false;
		bool incrementalLogging_ = false;
		
		std::string logVersion;
		std::string logPath_;

	public: // Fucntions

		//Default log config
		Logger();
		// Log with log path
		Logger(std::string);
		// Log with commandLine args
		Logger(int argc, char * argv[]);
		// Deconstructor
		~Logger();

		/*
		 * Logging states
		 */
		void log(Logger::LogLevel, std::string);
		void info(std::string);
		void debug(std::string);
		void warning(std::string);
		void error(std::string);

		/*
		 * Select what level of logging should be written to file
		 */
		void setLogLevel(const LogLevel);

		/*
		 * Returns the current logging level of the logger
		 * By default set to NONE
		 */
		LogLevel getLogLevel() const;

		/*
		 * Returns the current logging level as a string
		 * Returns NONE as default
		 */
		const std::string getLogLevelString();

		void enableTimeStamps(bool);
		void setTimeStampsString(char *);

		void dumpLogs(Logger::LogLevel = Logger::LogLevel::ALL);
		void dumpAllOrdered();



	private: // Functions

		/*
		 * Check that command line contains "Logger" to enable command flags
		 */
		 //startEndIndex getStartEndArgsIndex(std::vector<std::string>);

		std::set<char> removeInvalidFlags(std::set<char>::iterator, std::set<char>);

		std::map<char, std::string> removeInvalidFlagValues(std::map<char, std::string>::iterator, std::map<char, std::string>);

		void processFlags(std::set<char>::iterator, std::set<char>);

		void processFlagValues(std::map<char, std::string>::iterator, std::map<char, std::string>);

		void sortArray(SDI::DynArray<Logger::messagePosition>&);

		/*
		 * write to array in map at specic logging level
		 */
		void logAtLevel(LogLevel, std::string);

		void setLogPrefix(Logger::LogLevel, std::string);

		/*
		 * Prints message to console
		 */
		void printToConsole(std::string);

		/*
		 * Prints line to log file
		 */
		void printLineToLog(std::string);

		/*
		 * If the logged message should be written to the log file
		 */
		bool shouldLog(LogLevel);

		/*
		 * Return date and time with custom format
		 * format dictated by timeFormat_
		 */
		std::string currentDateTime();

	};
}

#endif

