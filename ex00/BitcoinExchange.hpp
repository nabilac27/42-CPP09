/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:17 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 16:09:00 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <cmath>

typedef std::string 	String;

class BitcoinExchange
{
	private:
		std::map<String, double>	database;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		
		void	loadDataCsvFile(const String& filename);
		void	processInputTxtFile(const String&	filename);
	
		bool	processInputLine(const String& line);
		bool	parseKeyDate(const String& line, String& date, String& valueString);
		bool	isValidDate(const String& date, const String& line);
		bool	isValidValue(const String& valueString, double& valueDouble, const String& line);
		bool	findExchangeRate(const String& date, double valueDouble);
	
		String	trim(const String& str);
		bool	printError(const String& message);
};


#endif