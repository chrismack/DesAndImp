#pragma once

#ifndef LINEPARSE_H
#define LINEPARSE_H

#include <vector>
#include <set>
#include <map>
#include <string>

namespace SDI
{
	class LineParse
	{
	private:
	public:
		LineParse();
		~LineParse();

		/* Vector of commandline arguments */
		std::vector<std::string> parseArgs(int argc, char * argv[]);

		/* Return set of unique flags in commandline arguments in alphabetical order */
		std::set<char> parseArgsFlags(int argc, char * argv[]);

		/* Return map of flag and associated value */
		std::map<char, std::string> parseArgsValues(int argc, char * argv[]);
	};
}


#endif /* LINEPARSE_H */