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
	DynArray<string> dynArray;

	dynArray.push_back(test2);
	dynArray.push_back(test);
	dynArray.push_back(test);
	
	DynArray<string> dynarray2;
	dynarray2.push_back("Testing 2 array");
	
	dynarray2 = dynArray;
	dynArray.set(0, "This is a test override of =");
	cout << dynarray2.get(0) << " hello"<< endl;


	
	cout << dynArray.size() << endl;
	cout << dynArray.capacity() << endl;
	cout << dynArray << endl;


	system("pause");


	return 0;
}

