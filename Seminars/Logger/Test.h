#pragma once
#include "Logger.h"

class Test
{
	private:
	public:
		SDI::Logger* logger;
		static Test* instance;


		Test();
		Test(int argc, char * argv[]);
		~Test();
		
		static Test* getInstance();
};