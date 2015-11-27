#include "LineParse.h"
#include <iostream>
#include <vector>
#include <string>

namespace SDI
{
	LineParse::LineParse()
	{
	}


	LineParse::~LineParse()
	{
	}

	/*
	 * This function converts each of the parameters to a std::string and collects them all in
	 * a vector in the same order as argv; this vector is the return value of the function.
	 */
	std::vector<std::string> LineParse::parseArgs(int argc, char * argv[])
	{
		std::vector<std::string> stringContainer;
		for (int i = 1; i < argc; i++)
		{
			std::cout << argv[i] << std::endl;
			stringContainer.push_back(argv[i]);
		}

		return stringContainer;
	}

	/*
	 * This variant collects single character flags that will be set with perhaps a ‘ - ‘ or a ‘ / ’
	 * on the command line; you are free to impose restrictions as appropriate, such as
	 * each flag must have its own ‘ - ‘ or all of them must be in a no - space string.Case
	 * sensitivity is a consideration.
	 */
	std::set<char> LineParse::parseArgsFlags(int argc, char * argv[])
	{
		std::set<char> charSet;
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
	 * This variant collects single character flags that are passed with values
	 */
	std::map<char, std::string> LineParse::parseArgsValues(int argc, char * argv[])
	{
		std::map<char, std::string> valuesMap;
		
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				std::string wordToSearch = argv[i];
				if (wordToSearch.find('='))
				{
					std::string value;
					std::size_t found = wordToSearch.find('=');
					
					for (int j = found + 1; j < wordToSearch.size(); j++)
					{
						value += wordToSearch[j];
					}
					//valuesMap[argv[i][1]] = value;
					valuesMap.insert(std::pair<char, std::string>(argv[i][1], value));
				}
			}
		}
		return valuesMap;
	}

}

