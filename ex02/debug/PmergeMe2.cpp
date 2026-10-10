/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe2.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 01:31:43 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 04:54:34 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../PmergeMe.hpp"
#include "PmergeMe2.hpp"

/* ************************************************************************** */
/* SORT                                                                       */
/* ************************************************************************** */
// void PmergeMe2::sortDebug(PmergeMe &sorter)
// {
//     PmergeMe2 debugger;
//     Vector values = sorter.vectorValues;

//     debugger.resetStats();
//     debugger.debugRecFordJohnson(sorter, values, 0, false);
//     debugger.printStats("Stats");
//     std::cout << "\n ----------------- [STEP 1] Make pairs --------------------------------------- " << std::endl;
//     sorter.makePairs(sorter.vectorValues);
//     printDebugSimple(sorter, PAIRS);

//     std::cout << "\n ----------------- [STEP 2] Sort pairs --------------------------------------- " << std::endl;
//     sorter.sortPairs(sorter.vectorValues, 0, true);
//     // printDebugSimple(sorter, PAIRS);
//     printDebugSimple(sorter, PAIRS_INDEX);

//     std::cout << "\n ----------------- [STEP 3] Create chains from original sorted pairs --------- " << std::endl;
//     sorter.createChains(sorter.vectorValues, sorter.vectorMainChain, sorter.vectorPendingChain);
//     printDebugSimple(sorter, CHAINS);

//     std::cout << "\n ----------------- [STEP 4] Insert first pending ----------------------------- " << std::endl;
//     sorter.insertFirstPending(sorter.vectorMainChain, sorter.vectorPendingChain);
//     printDebugSimple(sorter, CHAINS_FIRST_INSERTED);

//     std::cout << "\n ----------------- [STEP 5] Jacobsthal insertion + straggler ----------------- " << std::endl;
//     sorter.insertPending(sorter.vectorValues, sorter.vectorMainChain, sorter.vectorPendingChain);
//     printDebugSimple(sorter, CHAINS_FIRST_INSERTED);
// }
void PmergeMe2::sortDebug(PmergeMe &sorter)
{
    PmergeMe2 debugger;

    Vector jacobValues = sorter.vectorValues;
    Vector noJacobValues = sorter.vectorValues;

    // STEP 1
    std::cout << "\n ----------------- [STEP 1] Make pairs --------------------------------------- " << std::endl;
    sorter.makePairs(sorter.vectorValues);
    printDebugSimple(sorter, PAIRS);

    // STEP 2
    std::cout << "\n ----------------- [STEP 2] Sort pairs --------------------------------------- " << std::endl;
    sorter.sortPairs(sorter.vectorValues, 0, true);
    // printDebugSimple(sorter, PAIRS);
    printDebugSimple(sorter, PAIRS_INDEX);

    // STEP 3
    std::cout << "\n ----------------- [STEP 3] Create chains from original sorted pairs --------- " << std::endl;
    sorter.createChains(sorter.vectorValues, sorter.vectorMainChain, sorter.vectorPendingChain);
    printDebugSimple(sorter, CHAINS);

    // STEP 4
    std::cout << "\n ----------------- [STEP 4] Insert first pending ----------------------------- " << std::endl;
    sorter.insertFirstPending(sorter.vectorMainChain, sorter.vectorPendingChain);
    printDebugSimple(sorter, CHAINS_FIRST_INSERTED);

    // STEP 5
    std::cout << "\n ----------------- [STEP 5] Jacobsthal insertion + straggler ----------------- " << std::endl;
    sorter.insertPending(sorter.vectorValues, sorter.vectorMainChain, sorter.vectorPendingChain);
    printDebugSimple(sorter, CHAINS_FIRST_INSERTED);

    // Compare Jacobsthal vs No Jacobsthal
    // std::cout << "\n ----------------- [COMPARISON] ---------------------------------------------- " << std::endl;

    // debugger.resetStats();
    // debugger.debugRecFordJohnson(sorter, jacobValues, 0, false, JACOB);
    // debugger.printStats("FordJohnson with Jacobsthal");

    // std::cout << std::endl;

    // debugger.resetStats();
    // debugger.debugRecFordJohnson(sorter, noJacobValues, 0, false, NO_JACOB);
    // debugger.printStats("FordJohnson No Jacobsthal");

    // std::cout << "\n[Explanation]\n"
    //         << "Comparisons : Number of element comparisons during pair ordering and binary search\n"
    //         << "Insertions  : Number of elements inserted into the main chain\n"
    //         << "Moves       : Estimated number of element shifts caused by insertions\n"
    //         << std::endl;
}

/* ************************************************************************** */
/*  PRUNT                                                                     */
/* ************************************************************************** */
void PmergeMe2::printDebugState(const PmergeMe &sorter, const char *msg, Container type, bool debug)
{
    if (type == VECTOR)
    {
        if (debug)
            std::cout << "\n[" << msg << "]   Vector: ";
        else
            std::cout << msg << ": ";

        for (size_t i = 0; i < sorter.vectorValues.size(); i++)
            std::cout << sorter.vectorValues[i] << " ";
        std::cout << std::endl;
    }
}

void PmergeMe2::printDebugSimple(const PmergeMe &sorter, DebugCase type)
{
    if (type == PAIRS)
    {
        std::cout << "\n[Pairs  ]   Vector: ";

        for (size_t i = 0; i < sorter.vectorValues.size(); i += 2)
        {
            if (i + 1 < sorter.vectorValues.size())
                std::cout << "(" << sorter.vectorValues[i] << ", "
                          << sorter.vectorValues[i + 1] << ") ";
            else
                std::cout << sorter.vectorValues[i];
        }
        std::cout << std::endl;
    }
    else if (type == PAIRS_INDEX)
    {
        const int width = 11;

        std::cout << "\n[Pairs  ]   Vector: ";

        for (size_t i = 0; i < sorter.vectorValues.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < sorter.vectorValues.size())
                oss << "(" << sorter.vectorValues[i] << ", "
                    << sorter.vectorValues[i + 1] << ")";
            else
                oss << sorter.vectorValues[i];

            std::cout << std::left << std::setw(width) << oss.str();
        }
        std::cout << std::endl;

        std::cout << "[Index  ]   Vector: ";

        for (size_t i = 0; i < sorter.vectorValues.size(); i += 2)
        {
            std::ostringstream oss;

            if (i + 1 < sorter.vectorValues.size())
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

        while (mainIndex < sorter.vectorMainChain.size() || pendingIndex < sorter.vectorPendingChain.size())
        {
            std::string mainText;
            std::string pendingText;

            if (mainIndex < sorter.vectorMainChain.size())
            {
                std::ostringstream oss;
                oss << "[" << sorter.vectorMainChain[mainIndex] << "]";
                mainText = oss.str();
            }

            if (pendingIndex < sorter.vectorPendingChain.size())
            {
                std::ostringstream oss;
                oss << "[" << sorter.vectorPendingChain[pendingIndex].first
                    << "] -> "
                    << sorter.vectorPendingChain[pendingIndex].second;

                pendingText = oss.str();
                pendingIndex++;
            }

            std::cout << "  "
                      << std::left << std::setw(15) << mainText
                      << std::setw(20) << pendingText;

            if (mainIndex == 0 && sorter.hasOdd)
                std::cout << "[" << sorter.straggler << "]";

            std::cout << std::endl;
            mainIndex++;
        }

        std::cout << std::endl;
    }
}

void PmergeMe2::printDebugDetails(DebugCase type, const DebugInfo &info) const
{
    const std::string indent(info.depth * 4, ' ');
    std::ostringstream prefixStream;
    prefixStream << "[Depth " << info.depth << "] ";
    const std::string prefix = prefixStream.str();
    const std::string padding(indent.size() + prefix.size(), ' ');

    switch (type)
    {
    case PAIRS:
    case PAIRS_INDEX:
    case CHAINS:
    case CHAINS_FIRST_INSERTED:
        break;

    case INPUT_VALUES:
    case LARGER_VALUES:
    case RETURN_RECUR_VALUE:
    {
        if (!info.values)
            return;
        std::cout << "\n"
                  << indent << prefix;
        if (type == INPUT_VALUES)
            std::cout << "Value: ";
        else if (type == LARGER_VALUES)
            std::cout << "Larger elements: ";
        else
            std::cout << "Return: ";
        for (size_t i = 0; i < info.values->size(); ++i)
            std::cout << (*info.values)[i] << " ";
        std::cout << "\n";
        break;
    }
    case BASE_CASE:
        std::cout << indent << prefix
                  << "----------- Recursion's base case -----------\n";
        break;
    case PAIR_INDEX:
    case SORTED_PAIR_INDEX:
    {
        if (!info.pairs)
            return;
        const VectorPair &pairs = *info.pairs;
        const std::string title = type == PAIR_INDEX ? "Pairs: " : "Sorted pairs: ";
        std::cout << "\n"
                  << indent << prefix << title;
        for (size_t i = 0; i < pairs.size(); ++i)
        {
            std::ostringstream item;
            item << "(" << pairs[i].first << ", " << pairs[i].second << ")";
            std::cout << std::left << std::setw(12) << item.str();
        }
        if (type == PAIR_INDEX && info.hasOdd)
            std::cout << "Straggler: " << info.straggler;
        std::cout << "\n"
                  << padding << std::left << std::setw(title.size()) << "Index: ";
        for (size_t i = 0; i < pairs.size(); ++i)
        {
            std::ostringstream item;
            item << "(b" << i + 1 << ", a" << i + 1 << ")";
            std::cout << std::left << std::setw(12) << item.str();
        }
        std::cout << "\n";
        break;
    }
    case MAIN_CHAIN_RECUR:
    {
        if (!info.values || !info.pairs)
            return;
        const Vector &chain = *info.values;
        const VectorPair &pairs = *info.pairs;
        std::ostringstream header;
        header << prefix << "Create chains:  ";
        const std::string pad(indent.size() + header.str().size(), ' ');
        std::cout << "\n"
                  << indent << header.str()
                  << std::left << std::setw(15) << "Main chain" << "Pending chain\n";
        const size_t rows = std::max(chain.size(), pairs.size());
        for (size_t i = 0; i < rows; ++i)
        {
            std::ostringstream mainText, pendingText;
            if (i < chain.size())
                mainText << "[" << chain[i] << "]";
            if (i < pairs.size())
                pendingText << "[" << pairs[i].first << "] -> " << pairs[i].second;
            std::cout << pad << std::left << std::setw(15) << mainText.str()
                      << pendingText.str() << "\n";
        }
        break;
    }
    case MAIN_CHAIN_ENDS:
    {
        if (!info.pairs || info.pairs->empty())
            return;
        const size_t count = info.pairs->size();
        std::cout << "\n"
                  << indent << prefix << "Chain ends at b" << count
                  << " = [" << (*info.pairs)[count - 1].first << "]  | means "
                  << count << " pending elements\n";
        break;
    }
    case ENTER_RECUR:
    {
        std::cout << "\n"
                  << indent
                  << "[Depth " << info.depth << "] Value: ";

        if (info.values)
        {
            for (size_t i = 0; i < info.values->size(); i++)
                std::cout << (*info.values)[i] << " ";
        }

        std::cout << "\n\n";
        break;
    }

    case INSERT_B1:
    case BINARY_SEARCH_INSERT:
    case STRAGGLER_INSERT:
    {
        if (!info.values)
            return;
        if (type == INSERT_B1 && (!info.pairs || info.pairs->empty()))
            return;
        if (type == BINARY_SEARCH_INSERT && !info.pairs)
            return;
        std::ostringstream header;
        header << prefix;
        if (type == INSERT_B1)
            header << "Insert b1 = [" << (*info.pairs)[0].first << "]:  ";
        else if (type == BINARY_SEARCH_INSERT)
            header << "Insert b" << info.index + 1 << " = [" << info.pending << "]:  ";
        else
            header << "Insert straggler = [" << info.straggler << "]:  ";
        const std::string pad(indent.size() + header.str().size(), ' ');
        std::cout << "\n"
                  << indent << header.str() << "Main chain";
        if (type == INSERT_B1)
            std::cout << "      ✋ checkpoint 1";
        if (type == BINARY_SEARCH_INSERT)
        {
            size_t checkpoint = 1, previous = 1, current = 3;
            while (checkpoint < info.index + 1)
            {
                checkpoint = current;
                const size_t next = current + 2 * previous;
                previous = current;
                current = next;
            }
            std::cout << "      ✋ checkpoint " << checkpoint;
            if (checkpoint > info.pairs->size())
                std::cout << " (remaining)";
        }
        std::cout << "\n";
        for (size_t i = 0; i < info.values->size(); ++i)
        {
            std::cout << pad << "[" << (*info.values)[i] << "]";
            if (type == INSERT_B1 && i == 0)
                std::cout << " <- first pending";
            else if (type == BINARY_SEARCH_INSERT && i == info.insertedIndex)
                std::cout << " <- lower_bound(chain.begin(), partner=" << info.partner
                          << ", value=" << info.pending << ")";
            else if (type == STRAGGLER_INSERT && i == info.insertedIndex)
                std::cout << " <- inserted straggler, using lower_bound()";
            std::cout << "\n";
        }
        break;
    }
    }
}

PmergeMe2::PmergeMe2()
    : _comparisons(0), _insertions(0), _moves(0)
{}

void PmergeMe2::resetStats()
{
    _comparisons = 0;
    _insertions = 0;
    _moves = 0;
}

void PmergeMe2::addComparison()
{
    ++_comparisons;
}

void PmergeMe2::addInsertion()
{
    ++_insertions;
}

void PmergeMe2::addMoves(size_t count)
{
    _moves += count;
}

void PmergeMe2::printStats(const std::string &name) const
{
    std::cout << "\n=== " << name << " ===" << std::endl;
    std::cout << "Comparisons: " << _comparisons << std::endl;
    std::cout << "Insertions:  " << _insertions << std::endl;
    std::cout << "Moves:       " << _moves << std::endl;
}