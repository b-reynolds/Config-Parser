#include <iostream>
#include "config_parser.h"

int main()
{
	ConfigParser config_parser;

	auto result = config_parser.parse("config.cfg");

	std::string output;

	int a;
	if(!ConfigParser::find(result, "a", output) || !ConfigParser::to_int(output, a))
	{
		return 1;
	}

	int b;
	if (!ConfigParser::find(result, "b", output) || !ConfigParser::to_int(output, b))
	{
		return 1;
	}

	printf("The sum of %d and %d is %d.\n", a, b, a + b);

	getchar();
}