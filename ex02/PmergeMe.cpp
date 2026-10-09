/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 23:18:59 by nchairun         ###   ########.fr       */
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
        vectorValues        = other.vectorValues;
        vectorMainChain     = other.vectorMainChain;
        vectorPendingChain  = other.vectorPendingChain;

        dequeValues         = other.dequeValues;
        dequeMainChain      = other.dequeMainChain;
        dequePendingChain   = other.dequePendingChain;

        hasOdd              = other.hasOdd;
        straggler           = other.straggler;
    }
    return (*this);
}

PmergeMe::~PmergeMe()
{
}

/* ************************************************************************** */
/*  PUBLIC INTERFACE                                                          */
/* ************************************************************************** */
void    PmergeMe::parseValue(int argc, char *argv[])
{
    if (argc < 2)
        throw(std::runtime_error("Error"));

    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j]; j++)
        {
            if (!std::isdigit(argv[i][j]))
                throw(std::runtime_error("Error"));
        }
        int value = std::atoi(argv[i]);

        if (value <= 0)
            throw(std::runtime_error("Error"));

        vectorValues.push_back(value);
        dequeValues.push_back(value);
    }
}

double PmergeMe::sort(Container type)
{
    double start = getTime();

    if (type == VECTOR)
    {
        makePairs(vectorValues);
        sortPairs(vectorValues);
        createChains(vectorValues, vectorMainChain, vectorPendingChain);
        insertFirstPending(vectorMainChain, vectorPendingChain);
        insertPending(vectorValues, vectorMainChain, vectorPendingChain);
    }
    else if (type == DEQUE)
    {
        makePairs(dequeValues);
        sortPairs(dequeValues);
        createChains(dequeValues, dequeMainChain, dequePendingChain);

        insertPending(dequeValues, dequeMainChain, dequePendingChain);
    }
    else if (type == DEBUG_MODE)
        sortDebug();

    return (getTime() - start);
}

double  PmergeMe::getTime()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000000.0 + time.tv_usec);
}

/* ************************************************************************** */
/*  PRINT																	  */
/* ************************************************************************** */
void    PmergeMe::printState(const char *msg, Container type, bool debug)
{
    if (type == VECTOR)
    {
        if (debug)
            std::cout << "\n[" << msg << "]   Vector: ";
        else
            std::cout << msg << ": ";

        for (size_t i = 0; i < vectorValues.size(); i++)
            std::cout << vectorValues[i] << " ";
        std::cout << std::endl;
    }
}

void    PmergeMe::printTime(double time, Container type) const
{
    std::string container;
    size_t      container_size;

    if (type == VECTOR)
    {
        container      = "std::vector";
        container_size = vectorValues.size();
    }
    else
    {
        container      = "std::deque";
        container_size = dequeValues.size();
    }

    std::cout << "Time to process a range of "
              << container_size
              << " elements with " << container << " : "
              << std::fixed        << std::setprecision(5)
              << time              << " us"
              << std::endl;
}

