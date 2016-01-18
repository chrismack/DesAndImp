// Main.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "LoggerHandler.h"
#include "ApplicationMain.h"

int main(int argc, char * argv[])
{
	/*
	 * Initalise the Logger singleton class
	 */
	LoggerHandler logHandler(argc, argv);
	ApplicationMain main;
	std::system("pause");
    return 0;
}

