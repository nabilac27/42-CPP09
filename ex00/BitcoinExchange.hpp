/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:46:17 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/06 17:06:00 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    • The program name is btc. ✅
    • Your program must take a file as an argument.
    • Each line in this file must use the following format: "date | value".
    • A valid date will always be in the following format: Year-Month-Day.
    • A valid value must be either a float or a positive integer, between 0 and 1000.   
*/

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<std::string, double> database;
        
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		
		void	processFile(const std::string&	filename);
		
};

#endif