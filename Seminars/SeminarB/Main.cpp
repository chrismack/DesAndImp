// Main.cpp : Defines the entry point for the console application.
/*
*Author : Chris Mack n0576565
*/

#include "DynArray.h"
#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;
using namespace SDI;

int main(int argc, char *argv[])
{
	DynArray<string> dynArray;
	DynArray<string> dynArray2(50);
	DynArray<string> dynArray3(50, true);
	DynArray<string> dynArrayHello("Hello");

	cout << dynArray.size() << endl;
	cout << dynArray2.size() << endl;

	cout << dynArray.capacity() << endl;
	cout << dynArray2.capacity() << endl;

	cout << dynArray.empty() << endl;
	cout << dynArrayHello.empty() << endl;

	cout << dynArray.equality(dynArray2) << endl;
	cout << dynArray.equality(dynArrayHello) << endl;


	dynArray.push_back("Hello");
	dynArray.push_back("There");

	dynArray.push_front("I am cool");

	cout << dynArray << endl;

	dynArray.pop_front();
	dynArray.pop_back();

	cout << dynArray << endl;

	dynArray.push_back("1");
	dynArray.push_back("2");
	dynArray.push_back("3");

	cout << dynArray << endl;

	cout << dynArray.capacity() << endl;

	dynArray.reserve(500);

	cout << dynArray.capacity() << endl;

	dynArray.shrink();

	cout << dynArray.capacity() << endl;

	dynArray.insert(2, "Hello BOB");
	cout << dynArray << endl;

	dynArray.remove(2);

	cout << dynArray << endl;

	dynArray.append(dynArrayHello);

	cout << dynArray << endl;

	dynArray.set(2, "SET");

	cout << dynArray << endl;

	dynArray.zap();
	dynArray.push_back("new");
	cout << dynArray << endl;

	dynArray = dynArrayHello;

	cout << dynArray << endl;

	dynArray += dynArray;

	cout << dynArray << endl;

	cout << dynArray[0] << endl;

	cout << dynArray.front() << endl;

	dynArray.push_back("Back");

	cout << dynArray.back() << endl;

	cout << dynArray.get(1) << endl;

	system("pause");

	return 0;
}

