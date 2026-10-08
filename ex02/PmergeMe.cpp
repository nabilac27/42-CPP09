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

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vectorValues = other.vectorValues;
        vectorMainChain = other.vectorMainChain;
        vectorPendingChain = other.vectorPendingChain;

        dequeValues = other.dequeValues;
        dequeMainChain = other.dequeMainChain;
        dequePendingChain = other.dequePendingChain;

        hasOdd = other.hasOdd;
        straggler = other.straggler;
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

    makePairs(type);
    sortPairs(type);
    createChains(type);
    insertFirstPending(type);
    insertPending(type);
    insertStraggler(type);

    return (getTime() - start); // in s = (end - start) / 1000000.0;
}

/* ************************************************************************** */
/*  FORD-JOHNSON                                                              */
/* ************************************************************************** */
void PmergeMe::makePairs(Container type)
{
    if (type == VECTOR)
        makePairsTemp(vectorValues);
    else
        makePairsTemp(dequeValues);
}

void PmergeMe::sortPairs(Container type)
{
    if (type == VECTOR)
        sortPairsTemp(vectorValues);
    else
        sortPairsTemp(dequeValues);
}

void PmergeMe::createChains(Container type)
{
    if (type == VECTOR)
        createChainsTemp(
            vectorValues,
            vectorMainChain,
            vectorPendingChain);
    else
        createChainsTemp(
            dequeValues,
            dequeMainChain,
            dequePendingChain);
}

void PmergeMe::insertFirstPending(Container type)
{
    if (type == VECTOR)
        insertFirstPendingTemp(
            vectorMainChain,
            vectorPendingChain);
    else
        insertFirstPendingTemp(
            dequeMainChain,
            dequePendingChain);
}

void PmergeMe::insertPending(Container type)
{
    if (type == VECTOR)
        insertPendingTemplate(vectorMainChain, vectorPendingChain);
    else
        insertPendingTemplate(dequeMainChain, dequePendingChain);
}

void PmergeMe::insertStraggler(Container type)
{
    if (type == VECTOR)
        insertStragglerTemplate(vectorValues, vectorMainChain);
    else
        insertStragglerTemplate(dequeValues, dequeMainChain);
}

/* ************************************************************************** */
/*  TIME																	  */
/* ************************************************************************** */
size_t PmergeMe::getSize(Container type) const
{
    if (type == VECTOR)
        return (vectorValues.size());
    else
        return (dequeValues.size());
}

double PmergeMe::getTime()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000000.0 + time.tv_usec);
}

/* ************************************************************************** */
/*  PRINT																	  */
/* ************************************************************************** */
void PmergeMe::printState(const char *msg, Container type, bool debug)
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

void PmergeMe::printTime(double time, Container type) const
{
    std::string container;

    if (type == VECTOR)
        container = "std::vector";
    else
        container = "std::deque";

    std::cout << "Time to process a range of "
              << getSize(type)
              << " elements with " << container << " : "
              << std::fixed << std::setprecision(5)
              << time
              << " us"
              << std::endl;
}

void PmergeMe::printDebugging(Debug type)
{
    if (type == PAIRS)
    {
        std::cout << "\n[Pairs  ]   " << "Vector: ";
        for (size_t i = 0; i < vectorValues.size(); i += 2)
        {
            if (i + 1 < vectorValues.size())
                std::cout << "(" << vectorValues[i] << ", " << vectorValues[i + 1] << ") ";
            else
                std::cout << vectorValues[i];
        }

        std::cout << std::endl;
    }

    if (type == PAIRS_INDEX)
    {
        const int width = 11;

        // 1. Print pair values
        std::cout << "\n[Pairs  ]   Vector: ";

        for (size_t i = 0; i < vectorValues.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < vectorValues.size())
                oss << "(" << vectorValues[i] << ", "
                    << vectorValues[i + 1] << ")";
            else
                oss << vectorValues[i];

            std::cout << std::left << std::setw(width) << oss.str();
        }

        std::cout << std::endl;

        // 2. Print pair labels
        std::cout << "[Index  ]   Vector: ";

        for (size_t i = 0; i < vectorValues.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < vectorValues.size())
            {
                size_t index = (i / 2) + 1;

                oss << "(b" << index << ", a" << index << ")";
            }
            else
                oss << "Straggler";

            std::cout << std::left << std::setw(width) << oss.str();
        }

        std::cout << std::endl;
    }

    else if (type == CHAINS || type == CHAINS_FIRST_INSERTED)
    {
        std::cout << "\n[Chains ]" << std::endl;

        std::cout << "  "
                  << std::left << std::setw(15) << "Main chain"
                  << std::setw(20) << "Pending chain"
                  << "Straggler"
                  << std::endl;

        size_t mainIndex = 0;
        size_t pendingIndex = (type == CHAINS_FIRST_INSERTED) ? 1 : 0;

        while (mainIndex < vectorMainChain.size() || pendingIndex < vectorPendingChain.size())
        {
            std::string mainText;
            std::string pendingText;

            if (mainIndex < vectorMainChain.size())
            {
                std::ostringstream oss;
                oss << "[" << vectorMainChain[mainIndex] << "]";
                mainText = oss.str();
            }

            if (pendingIndex < vectorPendingChain.size())
            {
                std::ostringstream oss;
                oss << "[" << vectorPendingChain[pendingIndex].first
                    << "] -> "
                    << vectorPendingChain[pendingIndex].second;
                pendingText = oss.str();

                pendingIndex++;
            }

            std::cout << "  "
                      << std::left << std::setw(15) << mainText
                      << std::setw(20) << pendingText;

            if (mainIndex == 0 && hasOdd)
                std::cout << "[" << straggler << "]";

            std::cout << std::endl;

            mainIndex++;
        }

        std::cout << std::endl;
    }
}

void PmergeMe::printInsertionChains(const VectorSizeT &order, size_t insertionCount)
{
    // 1. Print current insertion information
    size_t index = order[insertionCount - 1];

    int pending = vectorPendingChain[index].first;
    int partner = vectorPendingChain[index].second;

    std::cout << "\n  [Insertion " << insertionCount + 1 << "] "
              << "b" << index + 1
              << " = " << pending
              << " (partner a" << index + 1
              << " = " << partner << ")"
              << std::endl;

    // 2. Build remaining pending chain
    VectorPair remainingPending;

    // b1 was already inserted in insertFirstPending().
    for (size_t j = 1; j < vectorPendingChain.size(); j++)
    {
        bool inserted = false;

        for (size_t k = 0; k < insertionCount; k++)
        {
            if (order[k] == j)
            {
                inserted = true;
                break;
            }
        }

        if (!inserted)
            remainingPending.push_back(vectorPendingChain[j]);
    }

    // 3. Print chains
    std::cout << "\n[Chains ]\n";
    std::cout << "  " << std::left
              << std::setw(15) << "Main chain"
              << std::setw(20) << "Pending chain"
              << "Straggler\n";

    size_t rows = std::max(vectorMainChain.size(),
                           remainingPending.size());

    for (size_t j = 0; j < rows; j++)
    {
        std::ostringstream mainText;
        std::ostringstream pendingText;
        std::ostringstream stragglerText;

        if (j < vectorMainChain.size())
            mainText << "[" << vectorMainChain[j] << "]";

        if (j < remainingPending.size())
        {
            pendingText << "[" << remainingPending[j].first
                        << "] -> " << remainingPending[j].second;
        }

        if (j == 0 && hasOdd)
            stragglerText << "[" << straggler << "]";

        std::cout << "  " << std::left
                  << std::setw(15) << mainText.str()
                  << std::setw(20) << pendingText.str()
                  << stragglerText.str()
                  << "\n";
    }
}

void PmergeMe::printRecursiveChains(const Vector &mainChain,
                                    const VectorPair &pendingChain,
                                    int depth,
                                    const std::string &stage)
{
    std::string indent(depth * 4, ' ');

    std::ostringstream prefix;
    prefix << "[Depth " << depth << "] " << stage << " -> ";

    const int mainWidth = 15;
    const int prefixWidth = std::max(
        static_cast<size_t>(36),
        prefix.str().length() + 1);

    std::cout << "\n"
              << indent
              << std::left
              << std::setw(prefixWidth) << prefix.str()
              << std::setw(mainWidth) << "Main chain"
              << "Pending chain\n";

    size_t rows = std::max(mainChain.size(), pendingChain.size());

    for (size_t i = 0; i < rows; i++)
    {
        std::ostringstream mainText;
        std::ostringstream pendingText;

        if (i < mainChain.size())
            mainText << "[" << mainChain[i] << "]";

        if (i < pendingChain.size())
        {
            pendingText << "[" << pendingChain[i].first
                        << "] -> " << pendingChain[i].second;
        }

        std::cout << indent
                  << std::setw(prefixWidth) << ""
                  << std::setw(mainWidth) << mainText.str()
                  << pendingText.str()
                  << "\n";
    }
}

/*
    ford-johnson, ford-johnson deque, insertPending
    Next priority: Update your outer insertPending() to use partner-bounded binary search too,
                    so the recursive and outer implementations follow the same insertion rules.

    ⚠️ fordJohnsonDeque() still needs the same recursive correction
    ⚠️ Pair identity for duplicate values is not handled robustly
    ⚠️ Straggler insertion still needs review for strict Ford-Johnson comparison behavior

    ---

    Jacobsthal order decides which pending value to insert next (b3 = 7).
    Binary search (lower_bound) decides where to insert it (between 6 and 9).
    Partner-bounded insertion decides how far the binary search is allowed to go (before 300).
*/