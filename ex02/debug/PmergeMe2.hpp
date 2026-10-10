/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe2.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 00:01:27 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 04:38:03 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME2_HPP
#define PMERGEME2_HPP

#include "../PmergeMe.hpp"

enum DebugCase
{
    INPUT_VALUES,
    BASE_CASE,
    PAIR_INDEX,
    LARGER_VALUES,
    SORTED_PAIR_INDEX,
    MAIN_CHAIN_RECUR,
    MAIN_CHAIN_ENDS,
    INSERT_B1,
    BINARY_SEARCH_INSERT,
    STRAGGLER_INSERT,
    RETURN_RECUR_VALUE,
    ENTER_RECUR,
    PAIRS,
    PAIRS_INDEX,
    CHAINS,
    CHAINS_FIRST_INSERTED
};

enum InsertionMode
{
    JACOB,
    NO_JACOB
};

struct DebugInfo
{
    const Vector *values;
    const VectorPair *pairs;

    int depth;
    bool hasOdd;
    int straggler;

    size_t index;
    int pending;
    int partner;
    size_t insertedIndex;

    DebugInfo()
        : values(NULL),
          pairs(NULL),
          depth(0),
          hasOdd(false),
          straggler(0),
          index(0),
          pending(0),
          partner(0),
          insertedIndex(0)
    {
    }
};

class PmergeMe2
{
private:
    size_t _comparisons;
    size_t _insertions;
    size_t _moves;

public:
    PmergeMe2();
    void sortDebug(PmergeMe &sorter);
    void printDebugState(const PmergeMe &sorter, const char *msg, Container type, bool debug);
    void printDebugSimple(const PmergeMe &sorter, DebugCase type);
    void printDebugDetails(DebugCase type, const DebugInfo &info) const;

    template <typename ContainerType>
    void debugRecFordJohnson(PmergeMe &sorter, ContainerType &values, int depth, bool debug);

    template <typename ContainerType>
    void noJacobsthal(ContainerType &mainChain,
                      const VectorPair &sortedPairs, DebugInfo &info, bool debug);

    template <typename ContainerType>
    size_t debugBinarySearch(ContainerType &mainChain,
                             int value, int partner, bool hasPartner);

    template <typename ContainerType>
    void debugRecFordJohnson(PmergeMe &sorter, ContainerType &values,
                             int depth, bool debug, InsertionMode mode);
    void resetStats();
    void addComparison();
    void addInsertion();
    void addMoves(size_t count);
    void printStats(const std::string &name) const;
};

#include "../PmergeMe.tpp"
#include "PmergeMe2.tpp"
#endif
