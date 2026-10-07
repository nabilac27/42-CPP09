/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:09:14 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/07 05:14:05 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "ERROR: Argument less than 2" << std::endl;
		return (1);
	}

	try
	{
		RPN rpn;
		rpn.process(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}

/*
	valgrind --leak-check=full --show-leak-kinds=all ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
*/