// Main.cpp : Defines the entry point for the console application.
/*
*Author : Chris Mack n0576565
*/

#include "DynArray.h"

#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(int argc, char *argv[])
{	
	
	int test = 10;
	DynArray<int> dynArray;

	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test);

	cout << dynArray.size() << endl;
	cout << dynArray.capacity() << endl;
	cout << dynArray << endl;
	system("pause");


	return 0;
}

