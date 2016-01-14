#ifndef LOGGER_CPP
#define LOGGER_CPP

#include "Logger.h"

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

		// Set of all command line flags
		std::set<char> argFlags = lineparse.parseArgsFlags(argc, argv);
		std::set<char>::iterator iterator;
		// Only include flags that are in the default flagSet
		argFlags = removeInvalidFlags(iterator, argFlags);
		processFlags(iterator, argFlags);
		

		std::map<char, std::string>::iterator mapIt;
		std::map<char, std::string> argFlagValues = lineparse.parseArgsValues(argc, argv);
		processFlagValues(mapIt, lineparse.parseArgsValues(argc, argv));
		
		std::string filePath = "Log.log";
		
		if (!logFile_.is_open())
		{
			// Remove file name if one has been set.
			if (logPath_ != "")
			{
				filePath = logPath_;
			}

			if (incrementalLogging_)
			{
				try
				{
					std::string logVersion;

					// File already exists
					std::fstream versionTrack;
					if (std::fstream(filePath + "-Verson.conf"))
					{
						if (!versionTrack.is_open())
						{
							std::string line;
							versionTrack.open(filePath + "-Verson.conf", std::ios::in);
							std::getline(versionTrack, line);
							logVersion = line;
							versionTrack.close();
						}
					}
					else
					{
						if (!versionTrack.is_open())
						{
							versionTrack.open(filePath + "-Verson.conf", std::ios::out);
							versionTrack << "0" << std::endl;
							logVersion = "0";
							versionTrack.close();

						}
					}
					// Increment file
					versionTrack.open(filePath + "-Verson.conf");
					int version = std::stoi(logVersion);
					version++;
					versionTrack << version;
					versionTrack.close();
					if (logVersion != "0")
					{
						filePath += logVersion;
					}

				}
				catch (std::exception e) {}
			}
			logFile_.open(filePath);
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

		if (dumpFile_.is_open())
		{
			dumpFile_.close();
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

	bool Logger::isPrefixing() const
	{
		return logPrefixes_;
	}

	void Logger::setPrefixing(const bool prefix)
	{
		logPrefixes_ = prefix;
	}

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
	 * Setter to set time format
	 */
	void Logger::setTimeStampsString(char * timeFormat)
	{
		timeFormat_ = timeFormat;
	}

	bool Logger::isConsoleOutputting() const
	{
		return logToConsole_;
	}

	void Logger::setConsleOutput(const bool console)
	{
		logToConsole_ = console;
	}

	bool Logger::isIncrementalLogging() const
	{
		return incrementalLogging_;
	}

	void Logger::setConsleOutput(const bool incLogging)
	{
		incrementalLogging_ = incLogging;
	}

	std::string Logger::getLogPath() const
	{
		return logPath_;
	}


	/*
	 * Dumps all logs of specific level
	 * Defaults to Logger::LogLevel::ALL
	 */
	void Logger::dumpLogs(Logger::LogLevel level)
	{
		if (!dumpFile_.is_open())
		{
			dumpFile_.open("Log.dump");
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

	}

	/*
	 * Sorts all of the logs depending on the order they were entered
	 * Prints them to a dump file
	 */
	void Logger::dumpAllOrdered()
	{
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
			dumpFile_.open("Log.dump");
		}

		for (int j = 0; j < allLogs.size(); j++)
		{
			dumpFile_ << allLogs[j].second << std::endl;
		}

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
		}
	}

	void Logger::processFlagValues(std::map<char, std::string>::iterator it, std::map<char, std::string> flagValues)
	{
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