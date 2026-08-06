/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:19 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/06 17:03:54 by nchairun         ###   ########.fr       */
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
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */

void BitcoinExchange::processFile(const std::string& filename)
{
	std::ifstream inputFile(filename.c_str());

	if (!inputFile.is_open())
		throw (std::runtime_error("Error: could not open file."));


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