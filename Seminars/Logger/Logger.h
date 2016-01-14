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
	public: // Variables

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
		 * Map of corrosponding (Enums, String, LogLevelPrefix)
		 */
		std::map<LogLevel, stringLevelPrefix> enumStrings_ = std::map<LogLevel, stringLevelPrefix>
		{
			{Logger::LogLevel::ALL,     {"ALL",     ""         } },
			{Logger::LogLevel::INFO,    {"INFO",    "[INFO]"   } },
			{Logger::LogLevel::DEBUG,   {"DEBUG",   "[DEBUG]"  } },
			{Logger::LogLevel::WARNING, {"WARNING", "[WARNING]"} },
			{Logger::LogLevel::ERROR,   {"ERROR",   "[ERROR]"  } },
			{Logger::LogLevel::NONE,    {"NONE",    ""         } }
		};


		std::string logVersion;
		std::string logPath_;

		/*
		 * Order in which logs are recieved
		 * each log increments this by one after logging 
		 */
		int arrayOrder_ = 0;

		/*
		 * Map of different logging levels and their arrays
		 */
		std::map<LogLevel, orderArray> loggingMap_;

		/*
		 * Time stamp prefixes
		 */
		bool timeLogging_ = false;

		/*
		 * Format for the prefixes
		 * Does not support %T or %F on some machines
		 */
		char * timeFormat_ = "[%d:%m:%y]";

		/*
		 * Should log prefixes
		 */
		bool logPrefixes_ = false;

		/*
		 * Should print to console
		 */
		bool logToConsole_ = false;

		/*
		 * Shoudl append log count at the end of the log file
		 */
		bool incrementalLogging_ = false;
		

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

		// ====================================
		//		Getters and Setters

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

		bool isPrefixing() const;

		void setPrefixing(const bool);

		std::string getLevelPrefix(const Logger::LogLevel) const;

		void setLevelPrefixString(const Logger::LogLevel, const std::string);

		bool isTimestamping() const;

		void setTimestamping(const bool);

		void setTimeStampsString(char *);

		bool isConsoleOutputting() const;

		void setConsleOutput(const bool);

		bool isIncrementalLogging() const;

		void setIncrementalLogging(const bool);

		//		End getters and setters
		//=============================================

		// Dumps all the logs defaults to all, logs are unordered
		void dumpLogs(Logger::LogLevel = Logger::LogLevel::ALL);

		// Dumps all the logs in correct order
		// Slower than dumpLogs
		void dumpAllOrdered();



	private: // Functions

		/*
		 * Check that command line contains "Logger" to enable command flags
		 */
		 //startEndIndex getStartEndArgsIndex(std::vector<std::string>);

		std::set<char> removeInvalidFlags(std::set<char>::iterator, std::set<char>);

		/*
		 * Removes flags the the logger doesn't support
		 */
		std::map<char, std::string> removeInvalidFlagValues(std::map<char, std::string>::iterator, std::map<char, std::string>);

		/*
		 * process flags without values
		 */
		void processFlags(std::set<char>::iterator, std::set<char>);

		/*
		 * Process flags that do contain values
		 */
		void processFlagValues(std::map<char, std::string>::iterator, std::map<char, std::string>);

		/*
		 * Sorts all of the arrays regardless of level to the order they recieved
		 * Uses bubble sort to order logs
		 */
		void sortArray(SDI::DynArray<Logger::messagePosition>&);

		/*
		 * write to array in map at specic logging level
		 */
		void logAtLevel(LogLevel, std::string);

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

