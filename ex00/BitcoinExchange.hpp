/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:17 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/10 18:55:11 by nchairun         ###   ########.fr       */
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

typedef std::string 	String;

class BitcoinExchange
{
	private:
		std::map<String, double> database;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		
		void	loadDataCsvFile(const String& filename);
		void	processInputTxtFile(const String&	filename);
		bool	parseKeyDate(const String& line, String& date, String& valueString);
		bool	processInputLine(const String& line);
		bool	isValidDate(const String& date, const String& line);
		bool	isValidValue(const String& valueString, double& valueDouble, const String& line);
		bool	findExchangeRate(const String& date, double valueDouble);
		String	trim(const String& str);
		bool	printError(const String& message);
};


#endif