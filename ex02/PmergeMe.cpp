/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/23 06:21:23 by nchairun         ###   ########.fr       */
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
        vector          = other.vector;
        deque           = other.deque;
        
        vectorMainChain = other.vectorMainChain;
        vectorPending   = other.vectorPending;
        
        hasOdd          = other.hasOdd;
        oddValue        = other.oddValue;
	}
	return (*this);
}

PmergeMe::~PmergeMe() 
{
}

/* ************************************************************************** */
/*  PARSE                                                                     */
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
/*  FORD-JOHNSON -- 1. MAKE PAIRS                                             */
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
/*  FORD-JOHNSON -- 2. SORT PAIRS into (smaller, larger)                      */
/* ************************************************************************** */
/*
    ! need to be implemented with Ford-Johnson Algorithm

    sortPairs()
    (8,9) (3,4) (1,7) (5,6)
                │
                │ take .second
                ▼
            9 4 7 6
                │
                ▼
    fordJohnsonVector(larger)
*/

void PmergeMe::sortPairs()
{
    std::vector<std::pair<int, int> > pairs;

    size_t pairCount = vector.size() / 2;

    // 1. Create pairs
    for (size_t i = 0; i < pairCount; i++)
    {
        size_t index = i * 2;

        int small = vector[index];
        int large = vector[index + 1];

        pairs.push_back(
            std::make_pair(small, large)
        );
    }

    // 2. Extract larger elements
    std::vector<int> larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    // 3. Sort larger elements recursively
    fordJohnsonVector(larger);

    // 4. Reorder pairs
    std::vector<std::pair<int, int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].second == larger[i])
            {
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    // 5. Put pairs back into vector
    for (size_t i = 0; i < sortedPairs.size(); i++)
    {
        vector[i * 2] = sortedPairs[i].first;
        vector[i * 2 + 1] = sortedPairs[i].second;
    }
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 3. RECURSIVELY SORT BIG ELEMENTS                          */
/* ************************************************************************** */
/*
    inside fordJohnsonVector(), turn them into pair again
*/
void PmergeMe::fordJohnsonVector(std::vector<int> &values)
{
    if (values.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;

    bool hasOddValue = (values.size() % 2 != 0);
    int odd = 0;

    if (hasOddValue)
        odd = values.back();
    // 1. Make pairs
    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int first = values[i];
        int second = values[i + 1];

        if (first > second)
            std::swap(first, second);

        pairs.push_back(
            std::make_pair(first, second)
        );
    }

    // 2. Extract larger values
    std::vector<int> larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    // 3. Recursively sort larger values
    fordJohnsonVector(larger);

    // 4. Start main chain with sorted larger values
    std::vector<int> mainChain = larger;

    // 5. Insert smaller values
    for (size_t i = 0; i < pairs.size(); i++)
    {
        int pending = pairs[i].first;

        std::vector<int>::iterator position =
            std::lower_bound(
                mainChain.begin(),
                mainChain.end(),
                pending
            );

        mainChain.insert(position, pending);
    }

    if (hasOddValue)
    {
        std::vector<int>::iterator position =
            std::lower_bound(
                mainChain.begin(),
                mainChain.end(),
                odd
            );

        mainChain.insert(position, odd);
    }
    // 6. Give sorted result back to caller
    values = mainChain;
}


/* ************************************************************************** */
/*  FORD-JOHNSON -- 4. Insert the partner of the smallest big element         */
/* ************************************************************************** */
void PmergeMe::createChains()
{
    vectorMainChain.clear();
    vectorPending.clear();

    size_t pairCount = vector.size() / 2;

    for (size_t i = 0; i < pairCount; i++)
    {
        size_t index = i * 2;

        int small = vector[index];
        int large = vector[index + 1];

    vectorPending.push_back(
        std::make_pair(small, large)
    );
        vectorMainChain.push_back(large);
    }
}

void PmergeMe::insertFirstPending()
{
    if (vectorPending.empty())
        return;

    vectorMainChain.insert(
        vectorMainChain.begin(),
        vectorPending[0].first
    );
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 5. Insert the remaining small elements                    */
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
/*  BINARY INSERT PENDING                                                     */
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

        int value = vectorPending[index].first;
        int partner = vectorPending[index].second;

        std::vector<int>::iterator partnerPosition =
            std::find(
                vectorMainChain.begin(),
                vectorMainChain.end(),
                partner
            );

        std::vector<int>::iterator position =
            std::lower_bound(
                vectorMainChain.begin(),
                partnerPosition,
                value
            );

        vectorMainChain.insert(position, value);
    }
}

/* ************************************************************************** */
/*  INSERT ODD LEFTOVER                                                       */
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
    {
        std::cout << "("
                  << vectorPending[i].first
                  << " -> "
                  << vectorPending[i].second
                  << ") ";
    }

    std::cout << std::endl << std::endl;
}