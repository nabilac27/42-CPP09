/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/17 17:16:13 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main (int argc, char *argv[])
{
	try
	{
		PmergeMe value;
        
        value.parseValue(argc, argv);
		value.printValue("Initial");

		value.printPairs();
		value.makePairs();
		value.printPairs();
		
		value.printValue("After makePairs");

		value.sortPairs();
		value.printPairs();
		// value.printValue("After sortPairs");

		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;	
}