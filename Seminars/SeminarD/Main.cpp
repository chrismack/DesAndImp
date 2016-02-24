// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <tuple>

#include "BlueRay.h"
#include "SingleDVD.h"
#include "ComboBox.h"
#include "VHS.h"
int main(int argc, char * argv[])
{
	SingleDVD dvd;
	dvd.setPackageDimensions(std::tuple<int, int, int>(1000, 20, 100));
	std::cout << std::get<0>(dvd.getPackageSize()) << std::endl;
	dvd.getBonusFeatures();

	system("pause");
	return 0;
}

