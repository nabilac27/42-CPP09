/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/17 16:54:51 by nchairun         ###   ########.fr       */
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


void PmergeMe::makePairs()
{
    for (size_t i = 0; i + 1 < vector.size(); i += 2)
    {
        if (vector[i] > vector[i + 1])
        {
            int temp = vector[i];
            vector[i] = vector[i + 1];
            vector[i + 1] = temp;
        }
    }
}

/* ************************************************************************** */
/*  PRINT																	  */
/* ************************************************************************** */
void PmergeMe::printValue(const char* msg)
{
    std::cout << "printValue() - " << msg << std::endl;
	std::cout << "------------------\n";
	
    std::cout << "Vector: ";
    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;

    std::cout << "Deque:  ";
    for (size_t i = 0; i < deque.size(); i++)
        std::cout << deque[i] << " ";
    std::cout << std::endl;
	std::cout << std::endl;
}

void PmergeMe::printMakePairs()
{
    std::cout << "printMakePairs()" << std::endl;
	std::cout << "------------------\n";

    for (size_t i = 0; i < vector.size(); i += 2)
    {
        if (i + 1 < vector.size())
            std::cout << "(" << vector[i] << ", " << vector[i + 1] << ") ";
        else
            std::cout << vector[i];
    }

    std::cout << std::endl;
	std::cout << std::endl;
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
