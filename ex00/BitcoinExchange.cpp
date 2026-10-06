/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:19 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 19:12:43 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* ************************************************************************** */
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */
BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	database = other.database;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		database = other.database;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

/* ************************************************************************** */
/*  loadDataCsvFile()                                           	          */
/* ************************************************************************** */
void BitcoinExchange::loadDataCsvFile(const String& filename)
{
	std::ifstream	databaseFile(filename.c_str());

	if (!databaseFile.is_open())
		throw (std::runtime_error("Error: could not open database."));

	String		line;
	std::getline(databaseFile, line);
	
	while (std::getline(databaseFile, line))
	{
		String::size_type comma = line.find(',');

		if (comma == String::npos)
			continue;

		String date 		= trim(line.substr(0, comma));
		String rateString	= trim(line.substr(comma + 1));

		double 				rateDouble;
		std::stringstream	ss(rateString);

		if (!(ss >> rateDouble) || !ss.eof())
			continue;
		
		database[date] = rateDouble;
	}
}

/* ************************************************************************** */
/*  processInputTxtFile()                                                     */
/* ************************************************************************** */
void BitcoinExchange::processInputTxtFile(const String& filename)
{
	std::ifstream	inputFile(filename.c_str());
	String 			line, key, value;

	if (!inputFile.is_open())
		throw (std::runtime_error("Error: could not open file."));
	if (!std::getline(inputFile, line)
		|| !parseKeyDate(line, key, value)
		|| key != "date"
		|| value != "value")
		throw (std::runtime_error("Error: bad input header."));
	
	while (std::getline(inputFile, line))
		processInputLine(line);
}

/* ************************************************************************** */
/*  parseKeyDate()                                                		      */
/* ************************************************************************** */
bool BitcoinExchange::parseKeyDate(const String& line, String& date,String& valueString)
{
	String::size_type separator = line.find('|');

	if (separator == String::npos
		|| line.find('|', separator + 1) != String::npos)
		return (printError("Error: bad input => " + line));

	date 		= trim(line.substr(0, separator));
	valueString = trim(line.substr(separator + 1));

	return (true);
}


/* ************************************************************************** */
/*  processInputLine()                                                		  */
/* ************************************************************************** */
bool BitcoinExchange::processInputLine(const String& line)
{
	String date;
	String valueString;
	double valueDouble;
	
	// if (!parseKeyDate(line, date, valueString)
	// 	|| !isValidDate(date, line)
	// 	|| !isValidValue(valueString, valueDouble, line)
	// 	|| !findExchangeRate(date, valueDouble))
	// 	return (false);

	if (!isValidDate(date, line)
		|| !isValidValue(valueString, valueDouble, line)
		|| !findExchangeRate(date, valueDouble))
		return (false);
	return (true);
}

/* ************************************************************************** */
/*  isValidDate()                                                		 	  */
/* ************************************************************************** */
bool BitcoinExchange::isValidDate(const String& date, const String& line)
{
	if (date.length() != 10)
		return (printError("Error: bad input => " + line));

	if (date[4] != '-' || date[7] != '-')
		return (printError("Error: bad input => " + line));

	for (std::size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (printError("Error: bad input => " + line));
	}

	int		year, month, day;
	char	dash1, dash2;

	std::stringstream ss(date);
	ss >> year >> dash1 >> month >> dash2 >> day;

	if (ss.fail() || year < 1 || month < 1 || month > 12)
		return (printError("Error: bad input => " + line));

	int max_days[12] =
	{
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	bool isLeapYear =
		(year % 4 == 0 && year % 100 != 0)
		|| year % 400 == 0;

	if (isLeapYear)
		max_days[1] = 29;

	if (day < 1 || day > max_days[month - 1])
		return (printError("Error: bad input => " + line));

	return (true);
}

/* ************************************************************************** */
/*  isValidValue()                                                		 	  */
/* ************************************************************************** */
bool BitcoinExchange::isValidValue(const String& valueString, double& valueDouble, const String& line)
{
	if (valueString.empty())
		return (printError("Error: bad input => " + line));

	std::stringstream ss(valueString);

	ss >> valueDouble;

	if (ss.fail() || !ss.eof())
		return (printError("Error: bad input => " + line));
	if (valueDouble < 0)
		return (printError("Error: not a positive number."));
	if (valueDouble > 1000)
		return (printError("Error: too large a number."));

	return (true);
}

/* ************************************************************************** */
/*  findExchangeRate()                                                		  */
/* ************************************************************************** */
bool BitcoinExchange::findExchangeRate(const String& date, double valueDouble)
{
	if (database.empty())
		return (printError("Error: database is empty."));
	
	std::map<String, double>::const_iterator it;

	it = database.upper_bound(date);

	if (it == database.begin())
		return (printError("Error: no earlier date available."));
	--it;

	double result = valueDouble * (it->second);

	std::cout << date
			  << " => "
			  << valueDouble
			  << " = "
			  << result
			  << std::endl;

	return (true);
}


/* ************************************************************************** */
/*  trim()                                                 			  		  */
/* ************************************************************************** */
String BitcoinExchange::trim(const String& str)
{
	std::size_t start	= 0;
	std::size_t end 	= str.length();

	while (start < str.length())
	{
		unsigned char currentChar = static_cast<unsigned char>(str[start]);
		if (!std::isspace(currentChar))
			break;
		start++;
	}
	while (end > start)
	{
		unsigned char currentChar = static_cast<unsigned char>(str[end - 1]);
		if (!std::isspace(currentChar))
			break;
		end--;
	}
	String result = str.substr(start, end - start);
	
	return (result);
}

/* ************************************************************************** */
/*  printError()                                              		  		  */
/* ************************************************************************** */
bool BitcoinExchange::printError(const String& message)
{
	std::cerr << message << std::endl;
	return (false);
}