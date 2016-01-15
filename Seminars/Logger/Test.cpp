#include "Test.h"
#include "Test2.h"

Test* Test::instance;

Test::Test()
{
	logger = new SDI::Logger();
}

Test::Test(int argc, char * argv[])
{
	Test::instance = this;

	logger = new SDI::Logger(argc, argv);
	logger->setConsleOutput(true);
	logger->info("This is info");

	Test2 t = Test2();
}


Test::~Test()
{
}

Test * Test::getInstance()
{
	if (Test::instance == nullptr)
	{
		Test::instance = new Test();
	}
	return Test::instance;
}



