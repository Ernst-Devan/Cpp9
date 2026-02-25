#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <stdexcept>
#include<bits/stdc++.h>

#define DATA_BASE_NAME "data.csv"

BitcoinExchange::BitcoinExchange()
{
    parse_data_base();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& b) 
{
    requests = b.requests;
    parse = b.parse;
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& b) 
{
    if (this == &b)
        return (*this);
    requests = b.requests;
    parse = b.parse;
    return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::add_wallet(char *name)
{
    std::ifstream file;

    file.open(name);

    if (!file.is_open() || file.bad() ||  file.fail())
        throw(std::invalid_argument("[Error] Wallet problem with the opening"));

    if (parse_wallet(file))
        return;
}

int BitcoinExchange::parse_wallet(std::ifstream& file)
{
    std::string line;

    getline(file, line);
    if (line != "date | value")
    {
        std::cout << "[Error] Not find date | value" << std::endl;
        return 1;
    }
    while (file.good() && getline(file, line))
    {
        if (line.size() == 0)
            continue;
        if (!get_line(line))
            value_of_wallet();
    }
    return 0;
}

static bool isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

unsigned int BitcoinExchange::check_number_day()
{
    int day;
    int month;
    int year;

    sscanf(parse.date.substr(0, 4).c_str(), "%d", &year);
    sscanf(parse.date.substr(5, 2).c_str(), "%d", &month);
    sscanf(parse.date.substr(8, 2).c_str(), "%d", &day);

    int daysInMonth;

	if (month == 2)
	{
		if (isLeapYear(year))
			daysInMonth = 29;
		else
			daysInMonth = 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		daysInMonth = 30;
	}
	else
	{
		daysInMonth = 31;
	}
	if (day < 1 || day > daysInMonth)
    {
        std::cout << "[Error]: Date number of day" << std::endl;
		return (1);
    }
	return (0);

}

unsigned int BitcoinExchange::value_of_wallet()
{
    tm      date = {};
    time_t  timestamp;
    int   d_date;
    float f_value;
    float result;
    
    sscanf(parse.date.substr(0, 4).c_str(), "%d", &d_date);
    date.tm_year = d_date - 1900;
    sscanf(parse.date.substr(5, 2).c_str(), "%d", &d_date);
    date.tm_mon = d_date - 1;
    sscanf(parse.date.substr(8, 2).c_str(), "%d", &d_date);
    date.tm_mday = d_date;

    timestamp = mktime(&date);

    sscanf(parse.value.c_str(), "%f", &f_value);

    result = get_value_date(timestamp);
    if (result == -1)
        return 1;

    result = analyse_price(result, f_value);
    
    display_price(result);

    return 0;
}

float BitcoinExchange::get_value_date(time_t timestamp)
{
    try
    {
        return requests.at(timestamp);
    }
    catch(const std::exception& e)
    {
        return (get_value_previous_date(timestamp));
    }
    return 0;
}

float BitcoinExchange::get_value_previous_date(time_t timestamp)
{
    std::map<time_t, float>::iterator it = requests.begin();

    it++;
    
    if (it->first > timestamp)
    {
        std::cout <<  "[Error] Date in wallet before date of DataBase" << std::endl;
        return -1;
    }
    while (it != requests.end() && it->first < timestamp)
    {
        it++;
    }
    if (it == requests.end())
    {
        std::cout << "[Error] DataBase looks weird" << std::endl;
        return -1;
    }
    it--;
    return it->second;
}

float BitcoinExchange::analyse_price(float value, float wallet)
{
    return value * wallet;
}

void    BitcoinExchange::display_price(float result)
{
    std::cout << parse.date << " => " << parse.value << " = " << result << std::endl;
}

unsigned int BitcoinExchange::get_line(std::string line)
{
    size_t index;

    index = line.find(" | ");
    if(index == std::string::npos)
    {
        std::cout << "[Error] Seperator not find" << std::endl;
        return 1;
    }

    parse.date = line.substr(0, index);
    parse.separator = line.substr(index, index + 3);
    parse.value = line.substr(index + 3, line.size());

    if (check_validity())
        return 1;
    if (check_number_day())
        return 1;
    return 0;
}

unsigned int BitcoinExchange::check_validity()
{
    //date validity
    tm tm;
    float value;
    int   day;
    unsigned int dot = 0;

    if (parse.date.size() != 10 || !strptime(parse.date.c_str(), "%Y-%m-%d", &tm) || !isdigit(parse.date[9]))
    {
        std::cout << "[Error] Date invalid format" << std::endl;
        return 1;
    }

    if (!sscanf(parse.date.substr(8, 2).c_str(), "%d", &day))
    {
        std::cout << "[Error] Date invalid format" << std::endl;
        return 1;
    }

    //Number validity
    for(unsigned int i = 0; i < parse.value.size(); i++)
    {
        if (!isdigit(parse.value[i]))
        {
            if (parse.value[i] == '.')
                dot++;
            if (parse.value[i] != '.' || dot > 1 || i == 0 || i == parse.value.size() - 1)
            {
                std::cout << "[Error] Number invalid format" << std::endl;
                return 1;
            }

        }
    }

    if (!sscanf(parse.value.c_str(), "%f", &value))
    {
        std::cout << "[Error] Number invalid format" << std::endl;
        return 1;
    }

    if (value < 0)
    {
        std::cout << "[Error] Negative number" << std::endl;
        return 1;
    }
    
    if (value > 1000)
    {
        std::cout << "[Error] Number too big" << std::endl;
        return 1;
    }
    return 0;
}

void BitcoinExchange::adding_data(std::string& line, std::string separator)
{
    tm  date = {};
    time_t timestamp;
    size_t  index;
    float   f_value = 0;

    index = line.find(separator);

    sscanf(line.substr(0, 4).c_str(), "%f", &f_value);
    date.tm_year = f_value - 1900;
    sscanf(line.substr(5, 2).c_str(), "%f", &f_value);
    date.tm_mon = f_value - 1;
    sscanf(line.substr(8, 2).c_str(), "%f", &f_value);
    date.tm_mday = f_value;

    timestamp = mktime(&date);

    sscanf(line.substr(index + separator.size(), line.size()).c_str(), "%f", &f_value);
    requests[timestamp] = f_value;
}

void BitcoinExchange::parse_data_base()
{
    std::string line;
    std::ifstream data_base;

    data_base.open(DATA_BASE_NAME);
    
    if (!data_base.is_open() || data_base.bad(), data_base.fail())
        throw(std::invalid_argument("[Error] DataBase problem with the opening"));

    getline(data_base, line);
    if (line != "date,exchange_rate")
        throw(std::invalid_argument("[Error] Not find date,exchange_rate"));
    while (getline(data_base, line))
    {
        if (line.size() == 0)
            continue;
        adding_data(line, ",");
    }
}