/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/17 17:53:29 by nchairun         ###   ########.fr       */
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

/* ************************************************************************** */
/*  PAIRS																	  */
/* ************************************************************************** */
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

void PmergeMe::sortPairs()
{
    size_t pairCount = vector.size() / 2;

    for (size_t i = 0; i < pairCount; i++)
    {
        for (size_t j = 0; j + 1 < pairCount; j++)
        {
            size_t firstPair = j * 2;
            size_t secondPair = (j + 1) * 2;

            if (vector[firstPair + 1] > vector[secondPair + 1])
            {
                std::swap(vector[firstPair], vector[secondPair]);
                std::swap(vector[firstPair + 1], vector[secondPair + 1]);
            }
        }
    }
}

void createChains()
{
    /* TO-DO */    
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

    // std::cout << "Deque:  ";
    // for (size_t i = 0; i < deque.size(); i++)
    //     std::cout << deque[i] << " ";
    std::cout << std::endl;
	std::cout << std::endl;
}

void PmergeMe::printPairs()
{
    std::cout << "printPairs()" << std::endl;
	std::cout << "------------------\n";

    std::cout << "Vector: ";
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


    ----

    parseValue()
      ↓
    makePairs()
        ↓
    sortPairs()
        ↓
    createChains()
        ↓
    insertFirstPending()
        ↓
    insertPending()
        ↓
    SORTED

    Current:
    pending → normal order → lower_bound entire chain

    Final Ford-Johnson:
    pending → Jacobsthal order → binary search limited by partner

    ---

    After sortPairs()

    1. parseValue()      ✓
    2. makePairs()       ✓
    3. sortPairs()       ✓
    4. createChains()    ← NEXT
    5. insert first small value
    6. Jacobsthal insertion
    7. binary search insertion
    8. handle odd leftover
    9. deque version
    10. timing

    Suppose after sortPairs():
        (3, 4) (1, 7) (8, 9)

    Each pair is:
        small  big
        3     4
        1     7
        8     9

    Now createChains() separates them:
        Main chain: 4 7 9
        Pending:    3 1 8

*/
