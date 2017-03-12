#include "config_parser.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

std::map<std::string, std::string> ConfigParser::parse(const std::string& file) const
{
	std::map<std::string, std::string> map;

	std::ifstream input_stream(file.c_str(), std::ios::in);
	for(std::string line; getline(input_stream, line);)
	{
		auto split_key = split(line, ':');
		if(split_key.size() != 2)
		{
			continue;
		}

		std::string key = erase(split(line, ':')[0], ' ');

		std::string value;
		if(!get_value(split_key[1], value))
		{
			continue;
		}

		map[key] = value;
	}

	return map;
}

bool ConfigParser::to_ullong(const std::string& input, unsigned long long& out)
{
	try
	{
		out = stoull(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_llong(const std::string& input, long long& out)
{
	try
	{
		out = stoll(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_long(const std::string& input, long& out)
{
	try
	{
		out = stol(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_uint(const std::string& input, unsigned int& out)
{
	try
	{
		out = stoul(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_int(const std::string& input, int& out)
{
	try
	{
		out = stoi(input);
	}
	catch(std::invalid_argument)
	{
		return false;
	}
	catch(std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_float(const std::string& input, float& out)
{
	try
	{
		out = stof(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_ldouble(const std::string& input, long double& out)
{
	try
	{
		out = stold(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_double(const std::string& input, double& out)
{
	try
	{
		out = stod(input);
	}
	catch (std::invalid_argument)
	{
		return false;
	}
	catch (std::out_of_range)
	{
		return false;
	}
	return true;
}

bool ConfigParser::to_bool(std::string input, bool& out)
{
	input = lower(input);

	if(input == "true")
	{
		out = true;
		return true;
	}
	if(input == "false")
	{
		out = false;
		return true;
	}

	int result;
	if(!to_int(input, result))
	{
		return false;
	}

	out = static_cast<bool>(result);
	return true;
}

bool ConfigParser::get_value(std::string& string, std::string& out)
{
	int begin = NULL;
	int end = NULL;

	unsigned int length = string.length();

	for(unsigned int i = 0; i < length; ++i)
	{
		if (string[i] != '"')
		{
			continue;
		}
		if(begin == NULL)
		{
			begin = i + 1;
			continue;
		}	
		if(i == length - 1)
		{
			end = i;
		}	
	}

	if(begin == NULL || end == NULL)
	{
		return false;
	}

	out = string.substr(begin, end - begin);

	return true;
}


std::vector<std::string> ConfigParser::split(const std::string& string, const char& delimiter)
{
	std::vector<std::string> parts;
	std::stringstream ss(string);
	std::string current;

	while (getline(ss, current, delimiter))
	{
		parts.push_back(current);
	}

	return parts;
}

std::string& ConfigParser::erase(std::string& string, const char& character)
{
	string.erase(remove(string.begin(), string.end(), character), string.end());
	return string;
}

std::string& ConfigParser::lower(std::string& string)
{
	for(auto & character : string)
	{
		character = tolower(character);
	}
	return string;
}
