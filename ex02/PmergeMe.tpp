/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:22:20 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 21:22:19 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_TPP
# define PMERGEME_TPP

/* ************************************************************************** */
/*  FORD-JOHNSON -- 1. MAKE PAIRS											  */
/* ************************************************************************** */
template <typename ContainerType> 
void PmergeMe::makePairs(ContainerType &values)
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
		hasOdd 		= true;
		straggler	= values.back();
	}
}

/* ****************************************************************************** */
/*  FORD-JOHNSON -- 2. SORT LARGER ELEMENTS recursively, use mergeInsertionSort() */
/* ****************************************************************************** */
template <typename ContainerType> 
void PmergeMe::sortPairs(ContainerType &values)
{
	VectorPair 		pairs;
	VectorPair 		sortedPairs;
	size_t			pairCount;
	size_t			index;
	int				small;
	int				large;
	ContainerType	largerElementsChain;

	pairCount = values.size() / 2;
	// 1. Create pairs
	for (size_t i = 0; i < pairCount; i++)
	{
		index = i * 2;
		small = values[index];
		large = values[index + 1];
		pairs.push_back(std::make_pair(small, large));
	}
	// 2. Extract larger elements
	for (size_t i = 0; i < pairs.size(); i++)
		largerElementsChain.push_back(pairs[i].second);
	// 3. Sort larger elements recursively
	mergeInsertionSort(largerElementsChain, 0, true); // --- FOR DEBUGGING: TRUE ---
	// 4. Reorder pairs
	std::vector<bool> used(pairs.size(), false);
	for (size_t i = 0; i < largerElementsChain.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].second == largerElementsChain[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break ;
			}
		}
	}
	// 5. Put pairs back into container
	for (size_t i = 0; i < sortedPairs.size(); i++)
	{
		values[i * 2] 		= sortedPairs[i].first;
		values[i * 2 + 1]	= sortedPairs[i].second;
	}
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 3. CREATE 2 CHAINS 										  */
/* ************************************************************************** */
template <typename ContainerType,typename PairContainerType> 
void PmergeMe::createChains(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain)
{
	size_t	pairCount;
	size_t	index;
	int		small;
	int		large;

	mainChain.clear();
	pendingChain.clear();
	pairCount = values.size() / 2;
	for (size_t i = 0; i < pairCount; i++)
	{
		index = i * 2;
		small = values[index];
		large = values[index + 1];
		pendingChain.push_back(std::make_pair(small, large));
		mainChain.push_back(large);
	}
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 4. INSERT FIRST ELEMENT IN PENDING CHAIN				  */
/* ************************************************************************** */
template <typename ContainerType, typename PairContainerType> 
void PmergeMe::insertFirstPending(ContainerType &mainChain, PairContainerType &pendingChain)
{
	if (pendingChain.empty())
		return ;
	mainChain.insert(mainChain.begin(), pendingChain[0].first);
}

/* **************************************************************************** */
/*  FORD-JOHNSON -- 5. INSERT REMAINING ELEMENTS 								*/
/* 		in Jacobsthal order, using Binary search insertion 						*/
/* 		Instead of inserting pending elements simply from left to right, 		*/
/*		it uses a special insertion order derived from the Jacobsthal sequence	*/ 
/* **************************************************************************** */
template <typename ContainerType, typename PairContainerType> 
void PmergeMe::insertPending(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain)
{
	VectorSizeT	order;
	size_t		index;
	int			pending;
	int			partner;

	if (pendingChain.size() <= 1)
		return ;
	if (pendingChain.size() > 1)
	{
		order = generateInsertionOrder<VectorSizeT>(pendingChain.size());
		for (size_t i = 0; i < order.size(); i++)
		{
			index = order[i];
			pending = pendingChain[index].first;
			partner = pendingChain[index].second;
			binarySearchInsertion(mainChain, pending, partner, true);
		}
	}
	pendingChain.clear();

	 // Insert straggler if the input has an odd number of elements
    if (hasOdd)
    {
        binarySearchInsertion(mainChain, straggler, 0, false);
        hasOdd = false;
    }

    // Copy sorted main chain back into original container
    values = mainChain;
}

/* ************************************************************************** */
/*  MERGE-INSERTION SORT								                      */
/* ************************************************************************** */

template <typename ContainerType>
void PmergeMe::mergeInsertionSort(ContainerType &values, int depth, bool debug)
{
    typedef typename ContainerType::iterator Iterator;

    VectorPair pairs;
    VectorPair sortedPairs;
    std::string indent(depth * 4, ' ');

    // 0. Enter recursion
    if (debug)
    {
        std::cout << "\n" << indent
                  << "[Depth " << depth << "] Value: ";
        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // Base case
    if (values.size() <= 1)
    {
        if (debug)
            std::cout << indent << "[Depth " << depth << "] ----------- Recursion's base case -----------\n";
        return;
    }

    // Handle odd element
    bool hasOddLocal = (values.size() % 2 != 0);
    int stragglerLocal = 0;

    if (hasOddLocal)
        stragglerLocal = values.back();

    // 1. Create pairs
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
        const int width = 12;

        std::ostringstream prefix;
        prefix << "[Depth " << depth << "] ";

        std::string padding(indent.length() + prefix.str().length(), ' ');

        // Print pairs
        std::cout << indent << prefix.str() << "Pairs: ";

        for (size_t i = 0; i < pairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(" << pairs[i].first
                << ", " << pairs[i].second << ")";

            std::cout << std::left << std::setw(width) << oss.str();
        }

        if (hasOddLocal)
            std::cout << "Straggler: " << stragglerLocal;

        std::cout << std::endl;

        // Print pair indexes
        std::cout << padding << "Index: ";

        for (size_t i = 0; i < pairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(b" << i + 1 << ", a" << i + 1 << ")";

            std::cout << std::left << std::setw(width) << oss.str();
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // 2. Extract larger elements
    ContainerType larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].second);

    if (debug)
    {
        std::cout << indent
                  << "[Depth " << depth << "] Return: ";

        for (size_t i = 0; i < larger.size(); i++)
            std::cout << larger[i] << " ";

        std::cout << std::endl;
    }

    // 3. Recursive sort
    mergeInsertionSort(larger, depth + 1, debug);

    // 4. Reorder pairs
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

    // DEBUG: Print sorted pairs and their indexes
    if (debug)
    {
        const int width = 12;

        std::ostringstream prefix;
        prefix << "[Depth " << depth << "] ";

        std::string padding(indent.length() + prefix.str().length(), ' ');

        std::cout << "\n" << indent << prefix.str() << "Sorted pairs: ";

        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(" << sortedPairs[i].first
                << ", " << sortedPairs[i].second << ")";

            std::cout << std::left << std::setw(width) << oss.str();
        }
        std::cout << std::endl;

        std::cout << padding << "Index:        ";

        for (size_t i = 0; i < sortedPairs.size(); i++)
        {
            std::ostringstream oss;
            oss << "(b" << i + 1 << ", a" << i + 1 << ")";

            std::cout << std::left << std::setw(width) << oss.str();
        }
        std::cout << std::endl;
    }

    // 5. Create main chain
    ContainerType mainChain = larger;

    if (debug)
    {
        std::ostringstream prefix;
        prefix << "[Depth " << depth << "] Create chains:  ";

        std::string padding(indent.length() + prefix.str().length(), ' ');

        std::cout << "\n" << indent << prefix.str()
                << std::left << std::setw(15) << "Main chain"
                << "Pending chain\n";

        for (size_t i = 0; i < mainChain.size(); i++)
        {
            std::ostringstream mainText;
            std::ostringstream pendingText;

            mainText << "[" << mainChain[i] << "]";

            if (i < sortedPairs.size())
                pendingText << "[" << sortedPairs[i].first
                            << "] -> " << sortedPairs[i].second;

            std::cout << padding
                    << std::left << std::setw(15) << mainText.str()
                    << pendingText.str() << "\n";
        }
    }

    if (debug && !sortedPairs.empty())
    {
        size_t count = sortedPairs.size();

        std::cout << "\n" << indent
                << "[Depth " << depth << "] Chain ends at b"
                << count << " = ["
                << sortedPairs[count - 1].first
                << "]  | means " << count << " pending elements\n";
    }

    // 6. Insert first pending (b1)
    if (!sortedPairs.empty())
    {
        mainChain.insert(mainChain.begin(), sortedPairs[0].first);

    if (debug)
    {
        std::ostringstream prefix;
        prefix << "[Depth " << depth << "] Insert b1 = ["
            << sortedPairs[0].first << "]:  ";

        std::string padding(indent.length() + prefix.str().length(), ' ');

        std::cout << "\n" << indent << prefix.str()
                << "Main chain  <- insert first pending\n";

        for (size_t i = 0; i < mainChain.size(); i++)
            std::cout << padding << "[" << mainChain[i] << "]\n";
    }
    }

    // 7. Jacobsthal insertion
    VectorSizeT order =
        generateInsertionOrder<VectorSizeT>(sortedPairs.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i];

        if (index == 0)
            continue;

        int pending = sortedPairs[index].first;
        int partner = sortedPairs[index].second;

        binarySearchInsertion(mainChain, pending, partner, true);

        size_t lastCompleteBoundary = 1;
        size_t previous = 1;
        size_t current = 3;

        while (current <= sortedPairs.size())
        {
            lastCompleteBoundary = current;

            size_t next = current + 2 * previous;
            previous = current;
            current = next;
        }

    if (debug)
    {
        std::ostringstream prefix;
        prefix << "[Depth " << depth << "] Insert b"
            << index + 1 << " = [" << pending << "]:  ";

        std::string padding(indent.length() + prefix.str().length(), ' ');

        std::cout << "\n" << indent << prefix.str() << "Main chain";

        if (index + 1 <= lastCompleteBoundary)
            std::cout << "  <- Jacobsthal";
        else
            std::cout << "  <- remaining element";

        std::cout << "\n";

        for (size_t j = 0; j < mainChain.size(); j++)
            std::cout << padding << "[" << mainChain[j] << "]\n";
    }
        // if (debug)
        // {
        //     std::ostringstream prefix;
        //     prefix << "[Depth " << depth << "] Insert b"
        //         << index + 1 << " = [" << pending << "]:  ";

        //     std::string padding(indent.length() + prefix.str().length(), ' ');

        //     std::cout << "\n" << indent << prefix.str()
        //             << "Main chain\n";

        //     for (size_t j = 0; j < mainChain.size(); j++)
        //         std::cout << padding << "[" << mainChain[j] << "]\n";
        // }
    }

    // 8. Insert straggler
    if (hasOddLocal)
    {
        Iterator position    = std::lower_bound(mainChain.begin(), mainChain.end(), stragglerLocal);
        size_t insertedIndex = std::distance(mainChain.begin(), position);

        mainChain.insert(position, stragglerLocal);

    if (debug)
    {
            std::ostringstream prefix;
            prefix << "[Depth " << depth << "] Insert straggler = [" << stragglerLocal << "]:  ";

            std::string padding(indent.length() + prefix.str().length(), ' ');

            std::cout << "\n" << indent << prefix.str() << "Main chain\n";

            for (size_t i = 0; i < mainChain.size(); i++)
            {
                std::cout << padding << "[" << mainChain[i] << "]";

                if (i == insertedIndex)
                    std::cout << "  <- inserted straggler, using lower_bound()";

                std::cout << "\n";
            }
        }
    }
    

    // 9. Return
    values = mainChain;

    if (debug)
    {
        std::cout << indent
                  << "[Depth " << depth << "] Return: ";

        for (size_t i = 0; i < values.size(); i++)
            std::cout << values[i] << " ";

        std::cout << std::endl;
    }
}

// template <typename ContainerType>
// void PmergeMe::mergeInsertionSort(ContainerType &values, int depth, bool debug)
// {
//     typedef typename ContainerType::iterator Iterator;
// 	VectorPair pairs;
// 	VectorPair sortedPairs;

//     // Base case
//     if (values.size() <= 1)
//         return ;

//     // Handle odd element
//     bool hasOddLocal 	= (values.size() % 2 != 0);
//     int  stragglerLocal = 0;

//     if (hasOddLocal)
//         stragglerLocal = values.back();

//     // 1. Create pairs (small, large)
//     for (size_t i = 0; i + 1 < values.size(); i += 2)
//     {
//         int small = values[i];
//         int large = values[i + 1];

//         if (small > large)
//             std::swap(small, large);

//         pairs.push_back(std::make_pair(small, large));
//     }

//     // 2. Extract and recursively sort larger values
//     ContainerType larger;

//     for (size_t i = 0; i < pairs.size(); i++)
//         larger.push_back(pairs[i].second);

// 	// 3. Sort larger elements recursively
//     mergeInsertionSort(larger, depth + 1, debug);

//     // 4. Reorder pairs according to sorted larger values
//     std::vector<bool> used(pairs.size(), false);

//     for (size_t i = 0; i < larger.size(); i++)
//     {
//         for (size_t j = 0; j < pairs.size(); j++)
//         {
//             if (!used[j] && pairs[j].second == larger[i])
//             {
//                 sortedPairs.push_back(pairs[j]);
//                 used[j] = true;
//                 break ;
//             }
//         }
//     }

//     // 5. Create main chain
//     ContainerType mainChain = larger;

//     // 6. Insert first smaller element (b1)
//     if (!sortedPairs.empty())
//         mainChain.insert(mainChain.begin(), sortedPairs[0].first);

//     // 7. Insert remaining smaller elements in Jacobsthal order
//     VectorSizeT order = generateInsertionOrder<VectorSizeT>(sortedPairs.size());

//     for (size_t i = 0; i < order.size(); i++)
//     {
//         size_t index = order[i];
//         int pending = sortedPairs[index].first;
//         int partner = sortedPairs[index].second;

//         Iterator partnerPosition = std::find(mainChain.begin(),
//                 mainChain.end(), partner);

//         Iterator position = std::lower_bound(mainChain.begin(),
//                 partnerPosition, pending);

//         mainChain.insert(position, pending);
//     }

//     // 8. Insert straggler
//     if (hasOddLocal)
//     {
//         Iterator position = std::lower_bound(mainChain.begin(), mainChain.end(), stragglerLocal);
//         mainChain.insert(position, stragglerLocal);
//     }

//     // 9. Return sorted values
//     values = mainChain;

//     if (debug)
//     {
//         std::cout << std::string(depth * 4,
//             ' ') << "[Depth " << depth << "] Return: ";

//         for (size_t i = 0; i < values.size(); i++)
//             std::cout << values[i] << " ";

//         std::cout << std::endl;
//     }
// }

/* ************************************************************************** */
/*  JACOBSTHAL SEQUENCE									                      */
/* ************************************************************************** */
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
template <typename ContainerType> 
ContainerType PmergeMe::generateJacobsthal(size_t size)
{
	ContainerType	jacobsthal;
	size_t			previous;
	size_t			current;
	size_t			next;

	previous = 1;
	current  = 3;
	next 	 = 0;

	while (current <= size)
	{
		jacobsthal.push_back(current);
		next = current + (2 * previous);
		previous = current;
		current = next;
	}
	return (jacobsthal);
}

template <typename ContainerType> 
ContainerType PmergeMe::generateInsertionOrder(size_t size)
{
	ContainerType	order;
	ContainerType	jacobsthal;
	size_t			previous;
	size_t			current;

	jacobsthal	= generateJacobsthal<ContainerType>(size);
	previous 	= 1;
	for (size_t i = 0; i < jacobsthal.size(); i++)
	{
		current = jacobsthal[i];
		for (size_t j = current; j > previous; j--)
			order.push_back(j - 1);
		previous = current;
	}
	for (size_t j = size; j > previous; j--)
		order.push_back(j - 1);
	return (order);
}

/* ************************************************************************** */
/*  BINARY SEARCH INSERTION                                                   */
/* ************************************************************************** */
template <typename ContainerType>
void PmergeMe::binarySearchInsertion(ContainerType &mainChain, int value, int partner, bool hasPartner)
{
    typedef typename ContainerType::iterator Iterator;

    Iterator partnerPosition;
    Iterator position;

    partnerPosition = mainChain.end();
    if (hasPartner)
        partnerPosition = std::find(mainChain.begin(), mainChain.end(), partner);

    position = std::lower_bound(mainChain.begin(), partnerPosition, value);
    mainChain.insert(position, value);
}

#endif