/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:45:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 16:14:44 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (std::cerr << "Error: could not open file." << std::endl, 1);

	try
	{
		BitcoinExchange		btc;

		btc.loadDataCsvFile("files/data.csv");
		btc.processInputTxtFile(argv[1]);
	}
	catch (const std::exception& e)
	{
		return (std::cerr << e.what() << std::endl, 1);	
	}

	return (0);
}

/*
	valgrind --leak-check=full --show-leak-kinds=all ./btc input.txt
*/