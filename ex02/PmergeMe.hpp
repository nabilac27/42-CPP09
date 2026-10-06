/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 18:53:59 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream> 
#include <string> 
#include <cctype>
#include <stdexcept> 
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <utility>

typedef std::vector<int>                  Vector;
typedef std::vector<size_t>               VectorSizeT;
typedef std::vector<std::pair<int, int> > VectorPair;

enum Debug
{
    PAIRS,
    CHAINS,
    CHAINS_FIRST_INSERTED
};

class PmergeMe
{
    private:
        Vector      vectorValues;

        Vector      vectorMainChain;
        VectorPair  vectorPending;

        bool        hasOdd;
        int         straggler;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();

        void        parseValue(int argc, char *argv[]);
        void        makePairs();
        void        sortPairs();
        void        createChains();
        void        fordJohnsonVector(Vector &values);
        void        insertFirstPending();

        VectorSizeT generateJacobsthal(size_t size);
        VectorSizeT generateInsertionOrder(size_t size);

        void        insertPending();
        void        insertStraggler();

        void        printState(const char *msg, bool debug);
        void        printDebugging(Debug type);
        
        // void        printPairs();
        // void        printChains(bool firstInserted);
};

#endif
