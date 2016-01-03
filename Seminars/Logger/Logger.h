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

		/*
		 * Current level of logs that are written to file
		 */
		LogLevel loggingLevel_ = LogLevel::NONE;

		std::ofstream logFile_;

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


		/*
		 * Map of different logging levels and their arrays
		 */
		std::map<LogLevel, SDI::DynArray<std::string>> loggingMap_;

		// Set of flags for logger
		std::set<char> flagSet_ =
		{
			'a', // Set logging state to all
			'i', // Set logging state to INFO
			'd', // Set logging state to DEBUG
			'w', // Set logging state to WARNING
			'e', // Set logging state to ERROR
			'n', // Set logging state to NONE

			't',
			'p',
			'c',
			'x',
			'o',

			'I', // Set message prefix for INFO
			'D', // Set message prefix for DEBUG
			'W', // Set message prefix for WARNING
			'E', // Set message prefix for ERRO

			'S',
			'L',
			'F',
			'T'
		};

		SDI::DynArray<Logger::LogLevel> conjoinedLevels;

		bool timeLogging_ = true;
		char * timeFormat_ = "[%d:%m:%y-%T]";

		bool logPrefixes_ = true;
		bool logToConsole_ = true;

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
		void setLogLevel(LogLevel);

		/*
		 * Returns the current logging level of the logger
		 * By default set to NONE
		 */
		LogLevel getLogLevel();

		/*
		 * Returns the current logging level as a string
		 * Returns NONE as default
		 */
		std::string getLogLevelString();

		void enableTimeStamps(bool);
		void setTimeStampsString(char *);



	private: // Functions

		/*
		 * Check that command line contains "Logger" to enable command flags
		 */
		 //startEndIndex getStartEndArgsIndex(std::vector<std::string>);

		std::set<char> removeInvalidFlags(std::set<char>::iterator, std::set<char>);

		void processFlags(std::set<char>::iterator, std::set<char>);


		/*
		 * Used to initalise map of different logging levels and their dynamic arrays
		 */
		void setUpMapArray(LogLevel);

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

