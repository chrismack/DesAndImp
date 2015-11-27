// Main.cpp : Defines the entry point for the console application.
/*
*Author : Chris Mack n0576565
*/

#include "DynArray.h"

#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{


	string test = "10";
	string test2 = "20";
	unsigned int test3 = 20000;
	DynArray<string> dynArray(20000);

	dynArray.push_back(test2);
	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test2);
	dynArray.push_back(test);
	dynArray.push_back(test);

	for (int i = dynArray.size(); i < dynArray.capacity(); i++)
	{
		std::ostringstream sstream;
		sstream << "This is a test" << i;
		dynArray.set(i, sstream.str());
	}
	
	cout << dynArray.size() << endl;
	cout << dynArray.capacity() << endl;
	cout << dynArray << endl;


	system("pause");


	return 0;
}

