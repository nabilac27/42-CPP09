/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/18 19:48:48 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ************************************************************************** */
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */
PmergeMe::PmergeMe() : hasOdd(false), oddValue(0)
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
        vector = other.vector;
        deque = other.deque;

        vectorMainChain = other.vectorMainChain;
        vectorPending = other.vectorPending;
	}
	return *this;
}

PmergeMe::~PmergeMe() 
{
}

/* ************************************************************************** */
/*  1. PARSE                                                                  */
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
/*  2. MAKE PAIRS                                                             */
/* ************************************************************************** */
void PmergeMe::makePairs()
{
    hasOdd = false;

    for (size_t i = 0; i + 1 < vector.size(); i += 2)
    {
        if (vector[i] > vector[i + 1])
            std::swap(vector[i], vector[i + 1]);
    }

    if (vector.size() % 2 != 0)
    {
        hasOdd = true;
        oddValue = vector.back();
        std::cout << "Odd value: " << oddValue << std::endl;
    }
}

/* ************************************************************************** */
/*  3. SORT PAIRS                                                             */
/* ************************************************************************** */
void PmergeMe::sortPairs()
{
    size_t countPairs = vector.size() / 2;

    for (size_t i = 0; i < countPairs; i++)
    {
        for (size_t j = 0; j + 1 < countPairs; j++)
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

/* ************************************************************************** */
/*  4. CREATE CHAINS                                                          */
/* ************************************************************************** */
void PmergeMe::createChains()
{
    vectorMainChain.clear();
    vectorPending.clear();

    size_t pairCount = vector.size() / 2;

    for (size_t i = 0; i < pairCount; i++)
    {
        size_t index = i * 2;

        vectorPending.push_back(vector[index]);
        vectorMainChain.push_back(vector[index + 1]);
    }
}

/* ************************************************************************** */
/*  5. INSERT FIRST PENDING                                                    */
/* ************************************************************************** */
void PmergeMe::insertFirstPending()
{
    if (vectorPending.empty())
        return;

    vectorMainChain.insert(
        vectorMainChain.begin(),
        vectorPending[0]
    );
}

/* ************************************************************************** */
/*  6. JACOBSTHAL                                                             */
/* ************************************************************************** */

std::vector<size_t> PmergeMe::generateJacobsthal(size_t size)
{
    std::vector<size_t> jacobsthal;

    size_t previous = 1;
    size_t current = 3;

    while (current <= size)
    {
        jacobsthal.push_back(current);

        size_t next = current + (2 * previous);

        previous = current;
        current = next;
    }

    return jacobsthal;
}

std::vector<size_t> PmergeMe::generateInsertionOrder(size_t size)
{
    std::vector<size_t> order;
    std::vector<size_t> jacobsthal = generateJacobsthal(size);

    size_t previous = 1;

    for (size_t i = 0; i < jacobsthal.size(); i++)
    {
        size_t current = jacobsthal[i];

        for (size_t j = current; j > previous; j--)
            order.push_back(j - 1);

        previous = current;
    }

    for (size_t j = size; j > previous; j--)
        order.push_back(j - 1);

    return order;
}

/* ************************************************************************** */
/*  7. BINARY INSERT PENDING                                                   */
/* ************************************************************************** */

void PmergeMe::insertPending()
{
    if (vectorPending.size() <= 1)
        return;

    std::vector<size_t> order =
        generateInsertionOrder(vectorPending.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i];
        int value = vectorPending[index];

        std::vector<int>::iterator position = std::lower_bound(
            vectorMainChain.begin(),
            vectorMainChain.end(),
            value
        );

        vectorMainChain.insert(position, value);
    }
}

/* ************************************************************************** */
/*  8. INSERT ODD LEFTOVER                                                     */
/* ************************************************************************** */

void PmergeMe::insertOdd()
{
    if (!hasOdd)
        return;

    std::vector<int>::iterator position;

    position = std::lower_bound(
        vectorMainChain.begin(),
        vectorMainChain.end(),
        oddValue
    );

    vectorMainChain.insert(position, oddValue);

    hasOdd = false;
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

void PmergeMe::printChains()
{
    std::cout << "printChains()" << std::endl;
    std::cout << "------------------" << std::endl;

    std::cout << "Main chain: ";

    for (size_t i = 0; i < vectorMainChain.size(); i++)
        std::cout << vectorMainChain[i] << " ";

    std::cout << std::endl;

    std::cout << "Pending:    ";

    for (size_t i = 0; i < vectorPending.size(); i++)
        std::cout << vectorPending[i] << " ";

    std::cout << std::endl << std::endl;
}
