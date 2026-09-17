/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/17 15:39:20 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ************************************************************************** */
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */

PmergeMe::PmergeMe() 
{
}

PmergeMe::PmergeMe(const PmergeMe&  other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{

	}
	return *this;
}

PmergeMe::~PmergeMe() 
{
}

/* *** */
void PmergeMe::parseValue(int argc, char *argv[])
{
	// validate argv[i]
	if (argc < 2)
        throw std::runtime_error("Error");
    for (int i = 1; i < argc; i++)
    {
		 // convert it to integer
		int value = std::atoi(argv[i]);

		if (value <= 0)
            throw std::runtime_error("Error");
	
        // add it to containers

        vector.push_back(value);
        deque.push_back(value);
    }
}

/*
	main()
	↓
	parseValue()
	↓
	check each argv[i]
	↓
	convert to int
	↓
	┌────────────┬────────────┐
	↓            ↓
	_vector      _deque

	./PmergeMe 3 5 9 7 4

	vector = [3, 5, 9, 7, 4]
	deque  = [3, 5, 9, 7, 4]
*/
