/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:22:20 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/08 17:38:20 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORDJOHNSON_TPP
#define FORDJOHNSON_TPP

template <typename ContainerType>
void PmergeMe::fordJohnson(ContainerType &values, int depth, bool debug)
{
    typedef typename ContainerType::iterator Iterator;
    typedef std::pair<int, int> Pair;
    typedef std::vector<Pair> PairVector;

    // Base case
    if (values.size() <= 1)
        return;

    // 1. Handle odd element
    bool hasOddLocal = (values.size() % 2 != 0);
    int stragglerLocal = 0;

    if (hasOddLocal)
        stragglerLocal = values.back();

    // 2. Create pairs (small, large)
    PairVector pairs;

    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        int small = values[i];
        int large = values[i + 1];

        if (small > large)
            std::swap(small, large);

        pairs.push_back(std::make_pair(small, large));
    }

    // 3. Extract and recursively sort larger values
    ContainerType larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    fordJohnson(larger, depth + 1, debug);

    // 4. Reorder pairs according to sorted larger values
    PairVector sortedPairs;
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

    // 5. Create main chain
    ContainerType mainChain = larger;

    // 6. Insert first smaller element (b1)
    if (!sortedPairs.empty())
        mainChain.insert(mainChain.begin(), sortedPairs[0].first);

    // 7. Insert remaining smaller elements in Jacobsthal order
    VectorSizeT order = generateInsertionOrder(sortedPairs.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i];

        int pending = sortedPairs[index].first;
        int partner = sortedPairs[index].second;

        Iterator partnerPosition =
            std::find(mainChain.begin(), mainChain.end(), partner);

        Iterator position =
            std::lower_bound(mainChain.begin(), partnerPosition, pending);

        mainChain.insert(position, pending);
    }

    // 8. Insert straggler
    if (hasOddLocal)
    {
        Iterator position =
            std::lower_bound(mainChain.begin(),
                             mainChain.end(),
                             stragglerLocal);

        mainChain.insert(position, stragglerLocal);
    }

    // 9. Return sorted values
    values = mainChain;

    if (debug)
    {
        std::cout << std::string(depth * 4, ' ')
                  << "[Depth " << depth << "] Return: ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";

        std::cout << std::endl;
    }
}

template <typename ContainerType>
void PmergeMe::makePairsTemp(ContainerType &values)
{
    hasOdd = false;

    // 1. Compare and sort each pair
    for (size_t i = 0; i + 1 < values.size(); i += 2)
    {
        if (values[i] > values[i + 1])
            std::swap(values[i], values[i + 1]);
    }

    // 2. Handle odd element (straggler)
    if (values.size() % 2 != 0)
    {
        hasOdd = true;
        straggler = values.back();
    }
}

template <typename ContainerType>
void PmergeMe::sortPairsTemp(ContainerType &values)
{
    typedef std::pair<int, int> Pair;
    typedef std::vector<Pair> PairVector;

    PairVector pairs;
    size_t pairCount = values.size() / 2;

    // 1. Create pairs
    for (size_t i = 0; i < pairCount; i++)
    {
        size_t index = i * 2;
        int small = values[index];
        int large = values[index + 1];

        pairs.push_back(std::make_pair(small, large));
    }

    // 2. Extract larger elements
    ContainerType larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    // 3. Sort larger elements recursively
    fordJohnson(larger, 0, false); // --- FOR DEBUGGING: TRUE ---

    // 4. Reorder pairs
    PairVector sortedPairs;
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

    // 5. Put pairs back into container
    for (size_t i = 0; i < sortedPairs.size(); i++)
    {
        values[i * 2] = sortedPairs[i].first;
        values[i * 2 + 1] = sortedPairs[i].second;
    }
}

template <typename ContainerType, typename PairContainerType>
void PmergeMe::createChainsTemp(
    ContainerType &values,
    ContainerType &mainChain,
    PairContainerType &pendingChain)
{
    mainChain.clear();
    pendingChain.clear();

    size_t pairCount = values.size() / 2;

    for (size_t i = 0; i < pairCount; i++)
    {
        size_t index = i * 2;
        int small = values[index];
        int large = values[index + 1];

        pendingChain.push_back(std::make_pair(small, large));
        mainChain.push_back(large);
    }
}

template <typename ContainerType, typename PairContainerType>
void PmergeMe::insertFirstPendingTemp(
    ContainerType &mainChain,
    PairContainerType &pendingChain)
{
    if (pendingChain.empty())
        return;

    mainChain.insert(mainChain.begin(), pendingChain[0].first);
}

#endif