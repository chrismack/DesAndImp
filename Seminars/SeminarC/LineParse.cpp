#ifndef LINEPARSE_CPP
#define LINEPARSE_CPP

#include "LineParse.h"


namespace SDI
{
	LineParse::LineParse()
	{}


	LineParse::~LineParse()
	{}


	/*
	 * Returns vector of command line arguments in order 
	 */
	std::vector<std::string> LineParse::parseArgs(int argc, char * argv[])
	{
		std::vector<std::string> stringContainer;
		for (int i = 0; i < argc; i++)
		{
			stringContainer.push_back(argv[i]);
		}

		return stringContainer;
	}

	/*
	 * Returns a set of unique commandline argument flags in alphabetical order
	 * Flags defined by '-'
	 */
	std::set<char> LineParse::parseArgsFlags(int argc, char * argv[])
	{
		std::set<char> charSet;
		// Ignore first argument as we know this won't contain a flag
		for (int i = 1; i < argc; i++)
		{
			// If argument start with '-'
			if (argv[i][0] == '-')
			{
				charSet.insert(argv[i][1]);
			}
		}
		return charSet;
	}

	/*
	 * Return map of commandline areguments followed by their values
	 * Values seperated by '='
	 * Flags defined by '-'
	 */
	std::map<char, std::string> LineParse::parseArgsValues(int argc, char * argv[])
	{

		std::map<char, std::string> valuesMap;
		
		// Ignore first element as we know this won't contain a flag
		for (int i = 1; i < argc; i++)
		{
			// Check if next element has a valid flag
			if (argv[i][0] == '-')
			{
				std::string wordToSearch = argv[i];
				// Check if word has a value to find
				if (wordToSearch.find('='))
				{
					std::string value;
					// Get position of the '=' in the string
					std::size_t found = wordToSearch.find('=');
					
					for (int j = found + 1; j < wordToSearch.size(); j++)
					{
						value += wordToSearch[j];
					}
					// Add Flag and corresponding values to map 
					valuesMap.insert(std::pair<char, std::string>(argv[i][1], value));
				}
			}
		}
		return valuesMap;
	}

}

#endif /* LINEPARSE_CPP */

