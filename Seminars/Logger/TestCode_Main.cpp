// Main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "TestCode_LoggerHandler.h"
#include "TestCode_ApplicationMain.h"

int main(int argc, char * argv[])
{
	/*
	 * Initalise the Logger singleton class
	 */
	TestCode_LoggerHandler logHandler(argc, argv);
	TestCode_ApplicationMain main;
	std::system("pause");
    return 0;
}

