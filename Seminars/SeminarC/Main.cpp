// SeminarC.cpp : Defines the entry point for the console application.
//

#include "LineParse.h"
#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;
int main(int argc, char * argv[])
{
	
	vector<std::string> myVec;
	std::set<char> charSet;
	std::set<char>::iterator it;

	std::map<char, string> valuesMap;
	std::map<char, string>::iterator itMap;


	SDI::LineParse lineParse;
	myVec = lineParse.parseArgs(argc, argv);

	for (std::string str : myVec)
	{
		std::cout << str << std::endl;
	}
	
	charSet = lineParse.parseArgsFlags(argc, argv);
	for (it = charSet.begin(); it != charSet.end(); ++it)
	{
		cout << *it << endl;
	}

	valuesMap = lineParse.parseArgsValues(argc, argv);
	for (itMap = valuesMap.begin(); itMap != valuesMap.end(); ++itMap)
	{
		cout << itMap->first << " : " << itMap->second << endl;
	}


	system("pause");
    return 0;
}

