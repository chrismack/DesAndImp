#include "Test2.h"
#include "Test.h"


Test2::Test2()
{
	Test::getInstance()->logger->debug("DEBUG");
	system("pause");
}


Test2::~Test2()
{
}
