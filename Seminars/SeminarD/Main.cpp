// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "BlueRay.h"
#include "SingleDVD.h"

int main(int argc, char * argv[])
{
	SingleDVD dvd;
	dvd.setPackageDimensions(std::make_pair(101, 20));
	std::cout << dvd.getPackageSize().first << std::endl;
	system("pause");
	return 0;
}

