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

		typedef std::pair<const std::string, std::string> stringLevelPrefix;

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
		std::map<const LogLevel, stringLevelPrefix> enumStrings_ = std::map<const LogLevel, stringLevelPrefix>
		{
			{Logger::LogLevel::ALL,     {"ALL",     ""         } },
			{Logger::LogLevel::INFO,    {"INFO",    "[INFO]"   } },
			{Logger::LogLevel::DEBUG,   {"DEBUG",   "[DEBUG]"  } },
			{Logger::LogLevel::WARNING, {"WARNING", "[WARNING]"} },
			{Logger::LogLevel::ERROR,   {"ERROR",   "[ERROR]"  } },
			{Logger::LogLevel::NONE,    {"NONE",    ""         } }
		};

		std::string logPath_;

		/*
		 * Order in which logs are recieved
		 * each log increments this by one after logging 
		 */
		int arrayOrder_ = 0;

		/*
		 * Map of different logging levels and their arrays
		 */
		std::map<const LogLevel, orderArray> loggingMap_;

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
		// Copy
		Logger(Logger&);
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

		void logFormatted(Logger::LogLevel, const char * format, ...);

		/*
		 * Insert op logs as Info 
		 */
		Logger& operator<<(const std::string);

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

		/*
		 * Get if the logger should prefix logging level
		 */
		bool isPrefixing() const;

		/*
		* Set if the logger should prefix logging level
		*/
		void setPrefixing(const bool);

		/*
		 * return a string of the prefix for logging level passed 
		 */
		std::string getLevelPrefix(const Logger::LogLevel);

		/*
		 * Sets the prefix message for a specific level
		 */
		void setLevelPrefixString(const Logger::LogLevel, const std::string);

		/*
		 * Get if time stamps are being prefixed to the log string 
		 */
		bool isTimestamping() const;

		/*
		 * Set if time stamps should be prefixed to log strings 
		 */
		void setTimestamping(const bool);

		/*
		 * Set the time stamp format for prefixes
		 * requires setTimestamping(true);
		 */
		void setTimeStampsString(char *);

		/*
		 * Gets if logs are being printed to the console 
		 */
		bool isConsoleOutputting() const;

		/*
		 * Set if logs should be sent to the console
		 */
		void setConsleOutput(const bool);

		/*
		 * get if incremental logging mode is enables 
		 */
		bool isIncrementalLogging() const;

		/*
		 * Set incremental logging mode
		 * appends run number to end of log file
		 */
		void setIncrementalLogging(const bool);

		/*
		 * Gets the current path of the logger
		 * Cannot be set requires new instance of logger 
		 */
		std::string getLogPath() const;

		//		End getters and setters
		//=============================================

		/*
		 * Dumps all the logs defaults to all, logs are unordered
		 */
		void dumpLogs(Logger::LogLevel = Logger::LogLevel::ALL);
		
		/*
		 * Slower than dumpLogs
		 * Dumps all the logs in correct order
		 */
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

