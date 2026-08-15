/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:19 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/15 23:18:52 by nchairun         ###   ########.fr       */
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
/*  processFile()                                                  			  */
/* ************************************************************************** */

void BitcoinExchange::processFile(const std::string& filename)
{
	std::ifstream inputFile(filename.c_str());

	if (!inputFile.is_open())
		throw (std::runtime_error("Error: could not open file."));

	std::string line;

	// Skip header
	if (!std::getline(inputFile, line))
		throw (std::runtime_error("Error: empty file."));

	while (std::getline(inputFile, line))
	{
		/* -------------------------------------------------------------- */
		/*  CHECK FORMAT: date | value                                    */
		/* -------------------------------------------------------------- */

		std::string::size_type separator = line.find('|');

		if (separator == std::string::npos
			|| line.find('|', separator + 1) != std::string::npos)
		{
			std::cerr << "Error: bad input => "
					  << line
					  << std::endl;
			continue;
		}

		/* -------------------------------------------------------------- */
		/*  SPLIT DATE AND VALUE                                          */
		/* -------------------------------------------------------------- */

		std::string date;
		std::string valueString;

		date = trim(line.substr(0, separator));
		valueString = trim(line.substr(separator + 1));

		/* -------------------------------------------------------------- */
		/*  VALIDATE DATE                                                  */
		/* -------------------------------------------------------------- */

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => "
					  << line
					  << std::endl;
			continue;
		}

		/* -------------------------------------------------------------- */
		/*  VALIDATE VALUE                                                 */
		/* -------------------------------------------------------------- */

		double value;

		if (!parseValue(valueString, value))
		{
			std::cerr << "Error: bad input => "
					  << line
					  << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number."
					  << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cerr << "Error: too large a number."
					  << std::endl;
			continue;
		}

		/* -------------------------------------------------------------- */
		/*  FIND EXCHANGE RATE AND PRINT                                  */
		/* -------------------------------------------------------------- */

		try
		{
			double rate = findExchangeRate(date);

			std::cout << date
					  << " => "
					  << value
					  << " = "
					  << value * rate
					  << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

/* ************************************************************************** */
/*  UTILS                                                 			  		  */
/* ************************************************************************** */
std::string BitcoinExchange::trim(const std::string& str) const
{
	std::size_t start = 0;
	std::size_t end = str.length();

	while (start < str.length()
		&& std::isspace(static_cast<unsigned char>(str[start])))
		start++;

	while (end > start
		&& std::isspace(static_cast<unsigned char>(str[end - 1])))
		end--;

	return (str.substr(start, end - start));
}

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

	int year;
	int month;
	int day;
	char dash1;
	char dash2;

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

	bool leapYear =
		(year % 4 == 0 && year % 100 != 0)
		|| year % 400 == 0;

	if (leapYear)
		days[1] = 29;

	if (day < 1 || day > days[month - 1])
		return (false);

	return (true);
}

bool BitcoinExchange::parseValue(
	const std::string& str,
	double& value
) const
{
	if (str.empty())
		return (false);

	char* end;

	value = std::strtod(str.c_str(), &end);

	if (end == str.c_str())
		return (false);

	if (*end != '\0')
		return (false);

	return (true);
}

double BitcoinExchange::findExchangeRate(const std::string& date) const
{
	std::map<std::string, double>::const_iterator it;

	it = database.lower_bound(date);

	if (it != database.end() && it->first == date)
		return (it->second);

	if (it == database.begin())
		throw (std::runtime_error("Error: no earlier date available."));

	if (it == database.end())
	{
		--it;
		return (it->second);
	}

	--it;

	return (it->second);
}

/*
	Program flow
	
		main
		│
		├── check argc
		│
		├── BitcoinExchange btc
		│
		└── btc.processFile(argv[1])
				│
				├── open file
				├── if fail → throw exception
				└── (later)
					read every line
	-----
		
		void BitcoinExchange::processFile(const std::string& filename)
		{
			open file
			skip header
			while (getline(...))
			{
				validate line
				validate date
				validate value
				find exchange rate
				print result
			}
		}
*/