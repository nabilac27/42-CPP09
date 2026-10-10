/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 17:22:20 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 01:58:01 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_TPP
#define PMERGEME_TPP

/* ************************************************************************** */
/*  FORD-JOHNSON -- 1. MAKE PAIRS											  */
/* ************************************************************************** */
template <typename ContainerType>
void PmergeMe::makePairs(ContainerType &values)
{
	hasOdd = false;
	for (size_t i = 0; i + 1 < values.size(); i += 2)
	{
		if (values[i] > values[i + 1])
			std::swap(values[i], values[i + 1]);
	}
	if (values.size() % 2 != 0)
	{
		hasOdd = true;
		straggler = values.back();
	}
}

/* ******************************************************************************** */
/*  FORD-JOHNSON -- 2. SORT LARGER ELEMENTS recursively, use recursiveFordJohnson() */
/* ******************************************************************************-- */
template <typename ContainerType>
void PmergeMe::sortPairs(ContainerType &values, int depth, bool debug)
{
	VectorPair		pairs, sortedPairs;
	ContainerType	larger;
	size_t 			pairCount, index;
	int 			small, large;

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
		larger.push_back(pairs[i].second);

	// 3. Sort larger elements recursively
	if (debug)
	{
		PmergeMe2 debugger;
		debugger.debugRecFordJohnson(*this, larger, depth + 1, false); // 'true' for details
	}
	else
		recursiveFordJohnson(larger, depth + 1);

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

	// 5. Put pairs back into container
	for (size_t i = 0; i < sortedPairs.size(); i++)
	{
		values[i * 2] = sortedPairs[i].first;
		values[i * 2 + 1] = sortedPairs[i].second;
	}
}

/* ************************************************************************** */
/*  FORD-JOHNSON -- 3. CREATE 2 CHAINS 										  */
/* ************************************************************************** */
template <typename ContainerType, typename PairContainerType>
void PmergeMe::createChains(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain)
{
	size_t 	pairCount;
	size_t 	index;
	int 	small;
	int 	large;

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
		return;
	mainChain.insert(mainChain.begin(), pendingChain[0].first);
}

/* **************************************************************************** */
/*  FORD-JOHNSON -- 5. INSERT REMAINING ELEMENTS 								*/
/* **************************************************************************** */
template <typename ContainerType, typename PairContainerType>
void PmergeMe::insertPending(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain)
{
	VectorSizeT order;
	size_t 		index;
	int 		pending;
	int 		partner;

	if (pendingChain.size() <= 1)
		return;
	if (pendingChain.size() > 1)
	{
		order = generateInsertionOrder<VectorSizeT>(pendingChain.size());
		for (size_t i = 0; i < order.size(); i++)
		{
			index 	= order[i];
			pending = pendingChain[index].first;
			partner = pendingChain[index].second;
			binarySearchInsertion(mainChain, pending, partner, true);
		}
	}
	pendingChain.clear();
	if (hasOdd)
	{
		binarySearchInsertion(mainChain, straggler, 0, false);
		hasOdd = false;
	}
	values = mainChain;
}

/* ************************************************************************** */
/*  FORD-JOHNSON ALGORITHM								                      */
// /* *********************************************************************** */
template <typename ContainerType>
void PmergeMe::recursiveFordJohnson(ContainerType &values, int depth)
{
	typedef typename ContainerType::iterator Iterator;

	VectorPair 		pairs;
	VectorPair 		sortedPairs;
	ContainerType	larger;

	if (values.size() <= 1)
		return;

	bool hasOddLocal = (values.size() % 2 != 0);
	int	 stragglerLocal = 0;

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

	// 2. Extract larger elements
	for (size_t i = 0; i < pairs.size(); i++)
		larger.push_back(pairs[i].second);

	// 3. Sort larger elements recursively
	recursiveFordJohnson(larger, depth + 1);

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

	// 5. Create main chain
	ContainerType mainChain = larger;

	// 6. Insert first pending (b1)
	if (!sortedPairs.empty())
		mainChain.insert(mainChain.begin(), sortedPairs[0].first);

	// 7. Jacobsthal insertion
	VectorSizeT order = generateInsertionOrder<VectorSizeT>(sortedPairs.size());

	for (size_t i = 0; i < order.size(); i++)
	{
		size_t index = order[i];

		if (index == 0)
			continue;

		int pending = sortedPairs[index].first;
		int partner = sortedPairs[index].second;

		binarySearchInsertion(mainChain, pending, partner, true);
	}

	// 8. Insert straggler
	if (hasOddLocal)
	{
		Iterator position = std::lower_bound(mainChain.begin(), mainChain.end(), stragglerLocal);
		mainChain.insert(position, stragglerLocal);
	}

	// 9. Return
	values = mainChain;
}

/* ************************************************************************** */
/*  JACOBSTHAL SEQUENCE									                      */
/* ************************************************************************** */
template <typename ContainerType>
ContainerType PmergeMe::generateJacobsthal(size_t size)
{
	ContainerType 	jacobsthal;
	size_t 			previous, current, next;

	previous = 1;
	current  = 3;
	next 	 = 0;

	while (current <= size)
	{
		jacobsthal.push_back(current);
		next 	 = current + (2 * previous);
		previous = current;
		current  = next;
	}
	return (jacobsthal);
}

template <typename ContainerType>
ContainerType PmergeMe::generateInsertionOrder(size_t size)
{
	ContainerType 	order;
	ContainerType	jacobsthal;
	size_t 		 	previous;
	size_t 		 	current;

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
size_t PmergeMe::binarySearchInsertion(ContainerType &mainChain, int value, int partner, bool hasPartner)
{
	typedef typename ContainerType::iterator Iterator;
	Iterator partnerPosition = mainChain.end();

	if (hasPartner)
		partnerPosition = std::find(mainChain.begin(), mainChain.end(), partner);

	Iterator 	position 		= std::lower_bound(mainChain.begin(), partnerPosition, value);
	size_t 		insertedIndex 	= std::distance(mainChain.begin(), position);

	mainChain.insert(position, value);

	return (insertedIndex);
}

#endif