/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/17 16:37:00 by nchairun         ###   ########.fr       */
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
        vector	= other.vector;
        deque	= other.deque;
	}
	return *this;
}

PmergeMe::~PmergeMe() 
{
}

/* ************************************************************************** */
/*  PARSE																	  */
/* ************************************************************************** */
void PmergeMe::parseValue(int argc, char *argv[])
{
	if (argc < 2)
        throw std::runtime_error("Error");
    for (int i = 1; i < argc; i++)
    {
		int value = std::atoi(argv[i]);
		if (value <= 0)
            throw std::runtime_error("Error");

        vector.push_back(value);
        deque.push_back(value);
    }
}

void PmergeMe::printParsedValue()
{
    std::cout << "printParsedValue() \n";
	std::cout << "------------------\n";
	
    std::cout << "Vector: ";
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;

    std::cout << "Deque:  ";
    for (size_t i = 0; i < deque.size(); i++)
        std::cout << deque[i] << " ";
    std::cout << std::endl;
	std::cout << "------------------\n";
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
