#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include "../SeminarB/DynArray.h"

#include <string>
#include <map>

#include <fstream>

class Logger
{
public: // Vasriables

	/*
	 * Different logging levels
	 */
	enum class LogLevel 
	{
		NONE, // Does not write to log
		INFO, 
		DEBUG,
		WARNING,
		ERROR,
		ALL // Writes all logs to file
	};

private: // Variables

	/*
	 * Current level of logs that are written to file
	 */
	LogLevel loggingLevel = LogLevel::NONE;

	std::ofstream logFile;

	/*
	 * Map of corrosponding (Enums, String)
	 */
	std::map<LogLevel, std::string> enumStrings =
	{
		{Logger::LogLevel::ALL,     "ALL"    },
		{Logger::LogLevel::INFO,    "INFO"   },
		{Logger::LogLevel::DEBUG,   "DEBUG"  },
		{Logger::LogLevel::WARNING, "WARNING"},
		{Logger::LogLevel::ERROR,   "ERROR"  },
		{Logger::LogLevel::ALL,     "ALL"    }
	};

	/*
	 * Map of different logging levels and their arrays
	 */
	std::map<LogLevel, SDI::DynArray<std::string>> loggingMap;

public: // Fucntions

	Logger();
	Logger(std::string);
	Logger(int argc, char * argv[]);
	Logger(int argc, char * argv[], std::string);
	~Logger();

	/* 
	 * Logging states
	 */
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


private: // Functions
	
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

};

#endif

