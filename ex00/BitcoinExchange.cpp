/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:19 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/27 19:30:54 by nchairun         ###   ########.fr       */
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
/*  loadDataCsv()                                           	     		  */
/* ************************************************************************** */
void BitcoinExchange::loadDataCsv(const std::string& filename)
{
	std::ifstream	databaseFile(filename.c_str());

	if (!databaseFile.is_open())
		throw (std::runtime_error("Error: could not open database."));

	std::string		line;
	std::getline(databaseFile, line);
	
	while (std::getline(databaseFile, line))
	{
		std::string::size_type comma = line.find(',');

		if (comma == std::string::npos)
			continue;

		std::string date 		= trim(line.substr(0, comma));
		std::string rateString	= trim(line.substr(comma + 1));

		double 				rateDouble;
		std::stringstream	ss(rateString);

		if (!(ss >> rateDouble))
			continue;
		
		database[date] = rateDouble;
	}
}

/* ************************************************************************** */
/*  processInputTxt()                                                		  */
/* ************************************************************************** */
void BitcoinExchange::processInputTxt(const std::string& filename)
{
	std::ifstream inputFile(filename.c_str());

	if (!inputFile.is_open())
		throw (std::runtime_error("Error: could not open file."));

	std::string line;
	std::getline(inputFile, line);

	while (std::getline(inputFile, line))
		processInputLine(line);
}


/* ************************************************************************** */
/*  processInputLine()                                                		  */
/* ************************************************************************** */
bool BitcoinExchange::processInputLine(const std::string& line) const
{
	std::string date;
	std::string valueString;
	double 		valueDouble;
	
	if (!parseDateValue(line, date, valueString))
		return (false);
	if (!isValidDate(date))
	{
		std::cerr << "Error: bad input => "
				  << line << std::endl;
		return (false);
	}
	if (!isValidValue(valueString, valueDouble, line))
		return (false);
	
	try
	{
		findExchangeRate(date, valueDouble);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (false);
	}

	return (true);
}

/* ************************************************************************** */
/*  parseDateValue()                                                		  */
/* ************************************************************************** */
bool BitcoinExchange::parseDateValue(const std::string& line, std::string& date,std::string& valueString) const
{
	std::string::size_type separator = line.find('|');

	if (separator == std::string::npos
		|| line.find('|', separator + 1) != std::string::npos)
	{
		std::cerr << "Error: bad input => "
				  << line << std::endl;
		return (false);
	}

	date 		= trim(line.substr(0, separator));
	valueString = trim(line.substr(separator + 1));

	return (true);
}

/* ************************************************************************** */
/*  isValidDate()                                                		 	  */
/* ************************************************************************** */
bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);

	for (std::size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}

	int 	year, month, day;
	char	dash1, dash2;

	std::stringstream ss(date);

	ss >> year >> dash1 >> month >> dash2 >> day;

	if (ss.fail())
		return (false);
	if (month < 1 || month > 12)
		return (false);

	int days[12] =
	{
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	bool leapYear = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

	if (leapYear)
		days[1] = 29;
	if (day < 1 || day > days[month - 1])
		return (false);
	return (true);
}

/* ************************************************************************** */
/*  isValidValue()                                                		 	  */
/* ************************************************************************** */
bool BitcoinExchange::isValidValue(const std::string& valueString, double& valueDouble, const std::string& line) const
{
	if (valueString.empty())
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}

	char* end;

	valueDouble = std::strtod(valueString.c_str(), &end);

	if (end == valueString.c_str() || *end != '\0')
	{
		std::cerr << "Error: bad input => " << line << std::endl;
		return (false);
	}

	if (valueDouble < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}

	if (valueDouble > 1000)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}

	return (true);
}

/* ************************************************************************** */
/*  findExchangeRate()                                                		  */
/* ************************************************************************** */
void BitcoinExchange::findExchangeRate(const std::string& date, double valueDouble) const
{
	std::map<std::string, double>::const_iterator it;

	it = database.lower_bound(date);

	if (it != database.end() && it->first == date)
	{
		// exact date found , return (it->second);
	}
	else if (it == database.begin())
	{
		throw (std::runtime_error("Error: no earlier date available."));
	}
	else
	{
		if (it == database.end() || it->first != date)
			--it;
	}

	double exchangeRate = it->second;
	double result 		= valueDouble * exchangeRate;

	std::cout << date
			  << " => "
			  << valueDouble
			  << " = "
			  << result
			  << std::endl;
}


/* ************************************************************************** */
/*  trim()                                                 			  		  */
/* ************************************************************************** */
std::string BitcoinExchange::trim(const std::string& str) const
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
	std::string result = str.substr(start, end - start);
	
	return (result);
}
