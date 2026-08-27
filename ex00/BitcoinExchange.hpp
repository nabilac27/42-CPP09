/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:17 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/27 19:35:14 by nchairun         ###   ########.fr       */
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

class BitcoinExchange
{
	private:
		std::map<std::string, double> database;

		bool processInputLine(const std::string& line) const;
		bool parseDateValue(const std::string& line, std::string& date,std::string& valueString) const;
		bool isValidDate(const std::string& date) const;
		bool isValidValue(const std::string& valueString, double& valueDouble, const std::string& line) const;
		void findExchangeRate(const std::string& date, double valueDouble) const;
        std::string	trim(const std::string& str) const;


	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		
		void	loadDataCsv(const std::string& filename);
		void	processInputTxt(const std::string&	filename);		
};


#endif