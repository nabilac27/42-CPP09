/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 18:06:58 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/* ************************************************************************** */
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */
PmergeMe::PmergeMe() : hasOdd(false), straggler(0)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe&   PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vector          = other.vector;
        vectorMainChain = other.vectorMainChain;
        vectorPending   = other.vectorPending;
        hasOdd          = other.hasOdd;
        straggler       = other.straggler;
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
        throw(std::runtime_error("Error"));
    for (int i = 1; i < argc; i++)
    {
        int value = std::atoi(argv[i]);
        if (value <= 0)
            throw(std::runtime_error("Error"));
        vector.push_back(value);
    }
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 1. MAKE PAIRS                                             */
/* ************************************************************************** */
void PmergeMe::makePairs()
{
    hasOdd = false;

    for (size_t i = 0; i+1 < vector.size(); i+=2)
    {
        if (vector[i] > vector[i + 1])
            std::swap(vector[i], vector[i + 1]);
    }
    if (vector.size() % 2 != 0)
    {
        hasOdd    = true;
        straggler = vector.back();
    };
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 2. SORT PAIRS into (smaller, larger)                      */
/* ************************************************************************** */
/*
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
        pairs.push_back(std::make_pair(small, large));
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
        vector[i * 2]       = sortedPairs[i].first;     // ?
        vector[i * 2 + 1]   = sortedPairs[i].second;    // ?
    }
}

// /* ************************************************************************** */
// /*  FORD-JOHNSON -- 3. RECURSIVELY SORT BIG ELEMENTS                          */
// /* ************************************************************************** */
void PmergeMe::fordJohnsonVector(std::vector<int>&  values)
{
    if (values.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;

    bool    hasOdd = (values.size() % 2 != 0);
    int     straggler     = 0;

    if (hasOdd)
        straggler = values.back();

    // 1. Make pairs
    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int first   = values[i];
        int second  = values[i + 1];

        if (first > second)
            std::swap(first, second);
        pairs.push_back(std::make_pair(first, second));
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

        std::vector<int>::iterator position = std::lower_bound(mainChain.begin(), mainChain.end(), pending);
        mainChain.insert(position, pending);
    }

    if (hasOdd)
    {
        std::vector<int>::iterator position = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(position, straggler);
    }
    
    // 6. Give sorted result back to caller
    values = mainChain;
}

// /* ************************************************************************** */
// /*  FORD-JOHNSON -- 4. Insert the partner of the smallest big element         */
// /* ************************************************************************** */
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
        vectorPending.push_back(std::make_pair(small, large));
        vectorMainChain.push_back(large);
    }
}

void PmergeMe::insertFirstPending()
{
    if (vectorPending.empty())
        return;
    vectorMainChain.insert(vectorMainChain.begin(),vectorPending[0].first);
}

// /* ************************************************************************** */
// /*  FORD-JOHNSON -- 5. Insert the remaining small elements                    */
// /* ************************************************************************** */
/*
    generateJacobsthal
    previous = 1
    current  = 3

    next = 3 + 2×1 = 5
    next = 5 + 2×3 = 11
    next = 11 + 2×5 = 21

    3, 5, 11, 21, 43...

    For :   generateJacobsthal(10)  --> [3, 5]
    11 isn't included because we only have 10 pending elements.
*/
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

    return (jacobsthal);
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

    return (order);
}

// /* ************************************************************************** */
// /*  BINARY INSERT PENDING                                                     */
// /* ************************************************************************** */
void PmergeMe::insertPending()
{
    if (vectorPending.size() <= 1)
        return;

    std::vector<size_t> order = generateInsertionOrder(vectorPending.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t  index   = order[i];
        int     value   = vectorPending[index].first;
        int     partner = vectorPending[index].second;

        std::vector<int>::iterator partnerPosition = std::find(vectorMainChain.begin(), vectorMainChain.end(), partner);
        std::vector<int>::iterator position        = std::lower_bound(vectorMainChain.begin(), partnerPosition, value);
        vectorMainChain.insert(position, value);
    }
    vectorPending.clear();
}

// /* ************************************************************************** */
// /*  INSERT STRAGGLER                                                          */
// /* ************************************************************************** */
void PmergeMe::insertStraggler()
{
    if (hasOdd)
    {
        std::vector<int>::iterator position;

        position    = std::lower_bound(vectorMainChain.begin(), vectorMainChain.end(), straggler);
        vectorMainChain.insert(position, straggler);
        hasOdd      = false;
    }
    vector  = vectorMainChain;
}

/* ************************************************************************** */
/*  PRINT																	  */
/* ************************************************************************** */
void PmergeMe::printState(const char *msg, bool debug)
{
    if (debug)
        std::cout << "\n[" << msg << "]   Vector: ";
    else
        std::cout << msg << ": ";

    for (size_t i = 0; i < vector.size(); i++)
        std::cout << vector[i] << " ";
    std::cout << std::endl;
}

void PmergeMe::printPairs()
{
    std::cout << "\n[Pairs  ]   " << "Vector: ";
    for (size_t i = 0; i < vector.size(); i += 2)
    {
        if (i + 1 < vector.size())
            std::cout << "(" << vector[i] << ", " << vector[i + 1] << ") ";
        else
            std::cout << vector[i];
    }

    std::cout << std::endl;
}

void PmergeMe::printChains(bool firstInserted)
{
    std::cout << "\n[Chains ]" << std::endl;
    std::cout << "  Main chain     Pending" << std::endl;

    size_t mainIndex    = false;
    size_t pendingIndex = firstInserted ? true : false;

    while (mainIndex < vectorMainChain.size() || pendingIndex < vectorPending.size())
    {
        std::cout << "     ";

        if (mainIndex < vectorMainChain.size())
            std::cout << "[" << vectorMainChain[mainIndex] << "]";
        else
            std::cout << "   ";

        std::cout << "          ";

        if (pendingIndex < vectorPending.size())
        {
            std::cout << "[" << vectorPending[pendingIndex].first
                      << "] -> "
                      << vectorPending[pendingIndex].second;
            pendingIndex++;
        }

        std::cout << std::endl;
        mainIndex++;
    }
    std::cout << std::endl;
}
