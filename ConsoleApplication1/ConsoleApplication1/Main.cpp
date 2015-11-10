// Main.cpp : Defines the entry point for the console application.
/*
*Author : Chris Mack n0576565
*/

#include "stdafx.h"
#include "DynArray.cpp"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

int main(int argc, char *argv[])
{
	DynArray<string> dynArray;
	string test = "Test";

	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test);
	dynArray.push_back(test);
	cout << dynArray.get(1) << endl;
	//cout << dynArray.get(8) << endl;
	//dynArray.pop_back();



	cout << dynArray.size() << endl;
	cout << dynArray.capacity()<< endl;


	system("pause");


	return 0;
}

