/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:17 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/27 17:44:48 by nchairun         ###   ########.fr       */
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

        std::string	trim(const std::string& str) const;
		bool		isValidDate(const std::string& date) const;
		bool		parseValue(const std::string& str, double& value) const;
		double		findExchangeRate(const std::string& date) const; 
		bool 		processInputLine(const std::string& line) const;
	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		
		void	loadDataCsv(const std::string& filename);
		void	processInputTxt(const std::string&	filename);		
};


#endif