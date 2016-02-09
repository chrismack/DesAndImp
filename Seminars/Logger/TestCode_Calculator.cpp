#include "TestCode_Calculator.h"



TestCode_Calculator::TestCode_Calculator()
{
	logger->info("Calculator starting");
	std::string exit;
	std::string num1, num2, operatorString;

	int result;
	while (exit != "exit")
	{
		std::cout << "Please enter first number : ";
		std::cin >> num1;
		std::cout << std::endl;
		logger->debug("num1, = " + num1);

		std::cout << "Please enter operator (+, -, *, /): ";
		std::cin >> operatorString;
		std::cout << std::endl;
		logger->debug("operator, = " + operatorString);

		std::cout << "Please enter second number : ";
		std::cin >> num2;
		std::cout << std::endl;
		logger->debug("num2, = " + num2);

		if (operatorString == "+")
		{
			result = add(stringToInt(num1), stringToInt(num2));
		}
		else if (operatorString == "-")
		{
			result = subtract(stringToInt(num1), stringToInt(num2));
		}
		else if (operatorString == "*")
		{
			result = multiply(stringToInt(num1), stringToInt(num2));
		}
		else if(operatorString == "/")
		{
			result = divide(stringToInt(num1), stringToInt(num2));
		}
		else
		{
			logger->error("Invalid operator entered");
		}

		std::cout << "The result is " << result << std::endl;
		logger->info("The result is :" + result);
		logger->debug("calc finished");
		std::cout << "type exit if you want to end calculator" << std::endl;
		std::cin >> exit;
	}
}


TestCode_Calculator::~TestCode_Calculator()
{
}

int TestCode_Calculator::add(int i, int j)
{
	logger->logFormatted(SDI::Logger::LogLevel::DEBUG, "adding numbers %d + %d", i, j);
	if (i + j < 0)
	{
		logger->logFormatted(SDI::Logger::LogLevel::WARNING, "%d + %d will return negative", i, j);
	}
	return i + j;
}

int TestCode_Calculator::subtract(int i , int j)
{
	logger->logFormatted(SDI::Logger::LogLevel::DEBUG, "subtracting numbers %d - %d", i, j);
	if (i - j < 0)
	{
		logger->logFormatted(SDI::Logger::LogLevel::INFO, "%d - %d returns a negative number", i, j);
	}
	return i - j;
}

int TestCode_Calculator::multiply(int i , int j)
{
	logger->logFormatted(SDI::Logger::LogLevel::DEBUG, "multiplying numbers %d * %d", i, j);
	return i * j;
}

int TestCode_Calculator::divide(int i, int j)
{
	logger->logFormatted(SDI::Logger::LogLevel::DEBUG, "dividing numbers %d / %d", i, j);
	try
	{
		if (j == 0)
		{
			throw std::exception("cannot divide by 0");
		}
		if (!(i / j % 0))
		{
			logger->logFormatted(SDI::Logger::LogLevel::WARNING, "%d / %d will return double data may be lost", i, j);
		}
	}
	catch (std::exception e)
	{
		logger->error(e.what());
		return 0;
	}
	return i / j;
}

int TestCode_Calculator::stringToInt(std::string number)
{
	logger->info("Converting : " + number + " to int");
	return std::atoi(number.c_str());
	
}
