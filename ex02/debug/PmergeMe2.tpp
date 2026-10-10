/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe2.tpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 23:53:06 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 01:39:41 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME2_TPP
#define PMERGEME2_TPP

template <typename ContainerType>
void PmergeMe2::debugRecFordJohnson(PmergeMe &sorter, ContainerType &values, int depth, bool debug)
{
    typedef typename ContainerType::iterator Iterator;

    VectorPair pairs;
    VectorPair sortedPairs;
    DebugInfo info;
    info.depth = depth;

    if (debug)
    {
        Vector snapshot(values.begin(), values.end());
        info.values = &snapshot;
        printDebugDetails(INPUT_VALUES, info);
    }

    if (values.size() <= 1)
    {
        if (debug)
            printDebugDetails(BASE_CASE, info);
        return;
    }

    bool hasOddLocal = (values.size() % 2 != 0);
    int stragglerLocal = 0;

    if (hasOddLocal)
        stragglerLocal = values.back();

    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int small = values[i];
        int large = values[i + 1];

        if (small > large)
            std::swap(small, large);

        pairs.push_back(std::make_pair(small, large));
    }

    if (debug)
    {
        info.pairs = &pairs;
        info.hasOdd = hasOddLocal;
        info.straggler = stragglerLocal;
        printDebugDetails(PAIR_INDEX, info);
    }

    ContainerType larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    if (debug)
    {
        Vector snapshot(larger.begin(), larger.end());
        info.values = &snapshot;
        printDebugDetails(LARGER_VALUES, info);
    }

    debugRecFordJohnson(sorter, larger, depth + 1, debug); 

   
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

    if (debug)
    {
        info.pairs = &sortedPairs;
        printDebugDetails(SORTED_PAIR_INDEX, info);
    }

    ContainerType mainChain = larger;

    if (debug)
    {
        Vector snapshot(mainChain.begin(), mainChain.end());
        info.values = &snapshot;
        info.pairs = &sortedPairs;
        printDebugDetails(MAIN_CHAIN_RECUR, info);
        printDebugDetails(MAIN_CHAIN_ENDS, info);
    }

    if (!sortedPairs.empty())
    {
        mainChain.insert(mainChain.begin(), sortedPairs[0].first);

        if (debug)
        {
            Vector snapshot(mainChain.begin(), mainChain.end());
            info.values = &snapshot;
            info.pairs = &sortedPairs;
            printDebugDetails(INSERT_B1, info);
        }
    }

    VectorSizeT order = sorter.generateInsertionOrder<VectorSizeT>(sortedPairs.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i];

        if (index == 0)
            continue;

        int pending = sortedPairs[index].first;
        int partner = sortedPairs[index].second;

        size_t insertedIndex = sorter.binarySearchInsertion(mainChain, pending, partner, true);
        if (debug)
        {
            Vector snapshot(mainChain.begin(), mainChain.end());
            info.values = &snapshot;
            info.pairs = &sortedPairs;
            info.index = index;
            info.pending = pending;
            info.partner = partner;
            info.insertedIndex = insertedIndex;
            printDebugDetails(BINARY_SEARCH_INSERT, info);
        }
    }

    if (hasOddLocal)
    {
        Iterator position = std::lower_bound(mainChain.begin(), mainChain.end(), stragglerLocal);
        size_t insertedIndex = std::distance(mainChain.begin(), position);

        mainChain.insert(position, stragglerLocal);

        if (debug)
        {
            Vector snapshot(mainChain.begin(), mainChain.end());
            info.values = &snapshot;
            info.straggler = stragglerLocal;
            info.insertedIndex = insertedIndex;
            printDebugDetails(STRAGGLER_INSERT, info);
        }
    }

    values = mainChain;

    if (debug)
    {
        Vector snapshot(values.begin(), values.end());
        info.values = &snapshot;
        printDebugDetails(RETURN_RECUR_VALUE, info);
    }
}

#endif