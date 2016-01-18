#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "Logger.h"

namespace SDI
{
	/*
	 * Default log location and name
	 */
	Logger::Logger(bool incLogging, bool deleteFile)
	{
		if (incLogging)
		{
			incrementalLogging();
		}
		if (std::fstream(logPath_) && !incLogging, deleteFile)
		{
			std::remove(logPath_.c_str());
		}
	}

	/*
	 * Copy all traits of logger except previous log messages
	 */
	Logger::Logger(Logger &cpy)
	{
		loggingLevel_		= cpy.loggingLevel_;
		logPath_			= cpy.logPath_;

		//I could loop though the map and copy everything manually
		// However it seems conter productive having duplicates of the logs
		//loggingMap_			= cpy.loggingMap_
		//arrayOrder_			= cpy.arrayOrder_;
		enumStrings_		= cpy.enumStrings_;
		timeLogging_		= cpy.timeLogging_;
		timeFormat_			= cpy.timeFormat_;
		logPrefixes_		= cpy.logPrefixes_;
		logToConsole_       = cpy.logToConsole_;
		incrementalLogging_ = cpy.incrementalLogging_;
		
	}

	/*
	 * Initalise Logger with path to log file
	 * Incremental logging false by default
	 * Delete existing file false by default
	 */
	Logger::Logger(std::string logPath, bool incLogging, bool deleteFile)
	{
		logPath_ = logPath;

		if (incLogging)
		{
			incrementalLogging();
		}
		if (std::fstream(logPath_) && !incLogging && deleteFile)
		{
			std::remove(logPath_.c_str());
		}
	}

	/*
	 * Constructor with commandLine args and option to delete existing file
	 * Delete file false by default
	 */
	Logger::Logger(int argc, char * argv[], bool deleteFile)
	{
		// Instance of line parser
		SDI::LineParse lineparse;

		// Set of all command line flags
		std::set<char> argFlags = lineparse.parseArgsFlags(argc, argv);
		std::set<char>::iterator iterator;
		// Only include flags that are in the default flagSet
		argFlags = removeInvalidFlags(iterator, argFlags);
		processFlags(iterator, argFlags);
		
		std::map<char, std::string>::iterator mapIt;
		std::map<char, std::string> argFlagValues = lineparse.parseArgsValues(argc, argv);
		processFlagValues(mapIt, lineparse.parseArgsValues(argc, argv));

		if (std::fstream(logPath_) && !incrementalLogging_ && deleteFile)
		{
			std::remove(logPath_.c_str());
		}
		if (!logFile_.is_open())
		{
			if (incrementalLogging_)
			{
				incrementalLogging();
			}
		}

	}


	/*
	 * Deconstruct Logger
	 */
	Logger::~Logger()
	{
		if (logFile_.is_open())
		{
			logFile_.close();
		}
	}


	/*
	 * ===========================
	 * Different types of logging
	 * ===========================
	 */

	void Logger::log(Logger::LogLevel level, std::string message)
	{
		// Do not log if the level has been set to a non-logging level
		if (level != Logger::LogLevel::ALL || level != Logger::LogLevel::NONE)
		{
			logAtLevel(level, message);
		}
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
	 * Format string that takes variable args and fills in string
	 * useful for for loops
	 */
	void Logger::logFormatted(Logger::LogLevel level, const char * format, ...)
	{
		char log[256];
		va_list arguments;
		va_start(arguments, format);
		vsprintf(log, format, arguments);
		logAtLevel(level, log);
		va_end(arguments);
	}

	/*
	 * Override insertion operator 
	 */
	Logger & Logger::operator<<(const std::string message)
	{
		logAtLevel(Logger::LogLevel::INFO, message);
		return *this;
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
	Logger::LogLevel Logger::getLogLevel() const
	{
		return loggingLevel_;
	}

	/*
	 * returns the loggingLevel as a string
	 */
	const std::string Logger::getLogLevelString()
	{
		if (enumStrings_.count(loggingLevel_) > 0)
		{
			return enumStrings_[loggingLevel_].first;
		}

		return "[ERROR] Could not convert logging level to string";
	}

	/*
	 * Return if messages are getting prefixed with log level
	 */
	bool Logger::isPrefixing() const
	{
		return logPrefixes_;
	}

	/*
	 * Set if messages are getting prefixed with log level
	 */
	void Logger::setPrefixing(const bool prefix)
	{
		logPrefixes_ = prefix;
	}

	/*
	 * Return the logLevel Prefix
	 */
	std::string Logger::getLevelPrefix(const Logger::LogLevel level)
	{
		return enumStrings_[level].second;
	}

	/*
	 * Return if messages are getting prefixed with the time
	 */
	bool Logger::isTimestamping() const 
	{
		return timeLogging_;
	}

	/*
	 * Setter to enable time stamps
	 */
	void Logger::setTimestamping(bool enabled)
	{
		timeLogging_ = enabled;
	}

	/*
	 * Return the time format string
	 */
	char * Logger::getTimeStampsString() const
	{
		return timeFormat_;
	}

	/*
	 * Setter to set time format
	 */
	void Logger::setTimeStampsString(char * timeFormat)
	{
		timeFormat_ = timeFormat;
	}

	/*
	 * Return if log messages are being printed to console
	 */
	bool Logger::isConsoleOutputting() const
	{
		return logToConsole_;
	}

	/*
	 * set if log mesages should be printed to the console
	 */
	void Logger::setConsleOutput(const bool console)
	{
		logToConsole_ = console;
	}

	/*
	 * Return if incremental logging is enabled
	 * Incremental logging append number at the end of log file
	 */
	bool Logger::isIncrementalLogging() const
	{
		return incrementalLogging_;
	}

	/*
	 * Set if we want to enable incremental logging
	 */
	void Logger::setIncrementalLogging(const bool incLogging)
	{
		incrementalLogging_ = incLogging;
	}

	/*
	 * Return if we are printing debug messages in debug mode
	 */
	bool Logger::getDebugLoggingMode() const
	{
		return debugLogging;
	}

	/*
	 * Set if we should output debug messages in debug mode
	 */
	void Logger::setDebugLoggingMode(const bool mode)
	{
		debugLogging = mode;
	}

	/*
	 * Returns the current path for the logger
	 * Cannot be set outside of constructor
	 */
	std::string Logger::getPath() const
	{
		return logPath_;
	}



	/*
	 * Dumps all logs of specific level
	 * Defaults to Logger::LogLevel::ALL
	 */
	void Logger::dumpLogs(Logger::LogLevel level, std::string path)
	{
		std::ofstream dumpFile_;
		if (!dumpFile_.is_open())
		{
			dumpFile_.open(path);
		}

		if (level == loggingLevel_ || level != Logger::LogLevel::ALL)
		{
			for (int i = 0; i < loggingMap_[level].size(); i++)
			{
				dumpFile_ << loggingMap_[level][i].second << std::endl;
			}
		}
		else if (level == Logger::LogLevel::ALL)
		{
			std::map<Logger::LogLevel, Logger::orderArray>::iterator it;
			for (it = loggingMap_.begin(); it != loggingMap_.end(); ++it)
			{
				for (int i = 0; i < loggingMap_[it->first].size(); i++)
				{
					dumpFile_ << loggingMap_[it->first][i].second << std::endl;
				}
			}
		}
		dumpFile_.close();
	}

	/*
	 * Sorts all of the logs depending on the order they were entered
	 * Prints them to a dump file
	 */
	void Logger::dumpAllOrdered(std::string path)
	{
		std::ofstream dumpFile_;
		SDI::DynArray<Logger::messagePosition> allLogs;
		
		std::map<Logger::LogLevel, Logger::orderArray>::iterator it;
		for (it = loggingMap_.begin(); it != loggingMap_.end(); ++it)
		{
			for (int i = 0; i < loggingMap_[it->first].size(); i++)
			{
				allLogs.push_back(loggingMap_[it->first][i]);
			}
		}
		sortArray(allLogs);

		if (!dumpFile_.is_open())
		{
			dumpFile_.open(path);
		}

		for (int j = 0; j < allLogs.size(); j++)
		{
			dumpFile_ << allLogs[j].second << std::endl;
		}
		dumpFile_.close();
	}

	/*
	 * Sort all of the logs into order they were recieved in
	 * May want to replace with a quick sort if time available
	 */
	void Logger::sortArray(SDI::DynArray<Logger::messagePosition> &dynArray)
	{
		for (int i = 0; i < dynArray.size(); i++)
		{
			for (int j = 0; j < dynArray.size(); j++)
			{
				if (j + 1 < dynArray.size())
				{
					if (dynArray[j].first > dynArray[j + 1].first)
					{
						Logger::messagePosition temp = dynArray[j + 1];
						dynArray[j + 1] = dynArray[j];
						dynArray[j] = temp;
					}
				}
			}
		}
	}

	/*
	 * Remove invalid flags from command line args
	 */
	std::set<char> Logger::removeInvalidFlags(std::set<char>::iterator it, std::set<char> argFlags)
	{
		// Set of flags that the logger can accept
		std::set<char> flagSet_ =
		{
			'a', // Set logging state to all //Done
			'i', // Set logging state to INFO //Done
			'd', // Set logging state to DEBUG //Done
			'w', // Set logging state to WARNING //Done
			'e', // Set logging state to ERROR //Done
			'n', // Set logging state to NONE //Done

			't', // Enable time prefixes //Done
			'p', // Enable logging prefixes //Done
			'c', // Incremental log files 
			'o', // Should output to console //Done
			'b', // Enable debugging mode

			'I', // Set message prefix for INFO //Done
			'D', // Set message prefix for DEBUG //Done
			'W', // Set message prefix for WARNING //Done
			'E', // Set message prefix for ERRO //Done

			'L', // Log path //Done
			'T'  // Time format //Done
		};

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

	/*
	 * Remove invalid flag values drom command lines
	 */
	std::map<char, std::string> Logger::removeInvalidFlagValues(std::map<char, std::string>::iterator it, std::map<char, std::string> argFlagValues)
	{
		for (it = argFlagValues.begin(); it != argFlagValues.end(); ++it)
		{
			if (it->second[0] == '-')
			{
				argFlagValues.erase(it);
			}
		}

		return argFlagValues;
	}

	/*
	 * Set logger variables from command line
	 */
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
			else if (*it == 'c')
			{
				// Enable increamental / concurrent file name
				incrementalLogging_ = true;
			}
			else if (*it == 'o')
			{
				// Enable printing to console
				logToConsole_ = true;
			}
			else if (*it == 'p')
			{
				// Enable logging prefixes
				logPrefixes_ = true;
			}
			else if (*it == 't')
			{
				// Enable time stamps
				timeLogging_ = true;
			}
			else if (*it == 'b')
			{
				debugLogging = true;
			}
		}
	}

	/*
	 * Set logger values from commandLine 
	 */
	void Logger::processFlagValues(std::map<char, std::string>::iterator it, std::map<char, std::string> flagValues)
	{
		// Map of values to levels
		std::map<char, Logger::LogLevel> prefixFlags =
		{
			{ 'I', Logger::LogLevel::INFO },
			{ 'D', Logger::LogLevel::DEBUG },
			{ 'W', Logger::LogLevel::WARNING },
			{ 'E', Logger::LogLevel::ERROR }
		};

		for (it = flagValues.begin(); it != flagValues.end(); ++it)
		{
			// Prefixes
			if (prefixFlags.count(it->first) > 0)
			{
				setLevelPrefixString(prefixFlags[it->first], flagValues[it->first]);
			}
			// Log file path
			else if (it->first == 'L')
			{
				if (it->second != "")
				{
					logPath_ = it->second;
				}
			}
			// Time stamp format
			else if (it->first == 'T')
			{
				timeFormat_ = strdup(it->second.c_str());
			}
		}
	}



	/*
	 * Writes message at specified LogLevel
	 */
	void Logger::logAtLevel(LogLevel level, std::string message)
	{
		// Insert message into the dynamic array

		loggingMap_[level].push_back({arrayOrder_, message});
		arrayOrder_++;

		// If the current logging level is the same as loggingLevel
		if (shouldLog(level))
		{
			// Do not prefix if we are returning a new line
			if (message != "\n")
			{
				if (logPrefixes_)
				{
					message = enumStrings_[level].second + message;
				}
				if (timeLogging_)
				{
					message = currentDateTime() + message;
				}
			}
			printLineToLog(message);
			if (logToConsole_)
			{
				printToConsole(message);
			}
		}


	}

	/*
	 * Set prefix for a specific log level 
	 * defaults to INFO
	 * [INFO]
	 */
	void Logger::setLevelPrefixString(Logger::LogLevel level, std::string prefix)
	{
		if (enumStrings_.count(level) > 0)
		{
			enumStrings_[level].second = prefix;
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
		if (!logFile_.is_open())
		{
			// Open in append to prevent loss of data
			logFile_.open(logPath_, std::ios::app | std::ios::out);
		}
		//logFile_.write(line.c_str(), line.length());
		//logFile_.write("\n", 1);
		logFile_ << line << std::endl;

		/*
		 * File not closed after each print to keep logger thread safe
		 * close function should be used when finished with the logger
		 */
		//logFile_.close();
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
		#if _DEBUG
			if (debugLogging == true && level == LogLevel::DEBUG)
			{
				return true;
			}
		#endif
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

	/*
	 * Handles how many times we have run the logger with incremental mode on
	 * Appends run number to end of logfile
	 */
	void Logger::incrementalLogging()
	{
		std::string logVersion;

		// File already exists
		std::fstream versionTrack;
		if (std::fstream(logPath_ + "-Verson.conf"))
		{
			if (!versionTrack.is_open())
			{
				versionTrack.open(logPath_ + "-Verson.conf", std::ios::in);
			}
			std::string line;
			std::getline(versionTrack, line);
			logVersion = line;
			versionTrack.close();
		}
		else // Create version track file
		{
			if (!versionTrack.is_open())
			{
				versionTrack.open(logPath_ + "-Verson.conf", std::ios::out);
			}
			versionTrack << "0" << std::endl;
			logVersion = "0";
			versionTrack.close();
		}
		// Increment file
		if (!versionTrack.is_open())
		{
			versionTrack.open(logPath_ + "-Verson.conf", std::ios::out);
		}
		int version = std::stoi(logVersion);
		version++;
		versionTrack << version;
		versionTrack.close();
		if (logVersion != "0")
		{
			logPath_ += logVersion;
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



} // Namespace

#endif // LOGGER_CPP