#pragma once

#ifndef LINEPARSE_H
#define LINEPARSE_H

#include <vector>
#include <set>
#include <map>

namespace SDI
{
	class LineParse
	{
	private:
	public:
		LineParse();
		~LineParse();

		std::vector<std::string> parseArgs(int argc, char * argv[]);
		std::set<char> parseArgsFlags(int argc, char * argv[]);
		std::map<char, std::string> parseArgsValues(int argc, char * argv[]);
	};
}


#endif /* LINEPARSE_H */