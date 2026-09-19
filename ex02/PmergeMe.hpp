/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/19 19:40:57 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream> 
#include <string> 
#include <stdexcept> 
#include <vector>
#include <deque>
#include <cstdlib>
#include <algorithm>

class PmergeMe
{
    private:
            struct PendingElement
        {
            int value;
            int partner;

            PendingElement(int v, int p)
                : value(v), partner(p)
            {
            }
        };

        // Original containers
        std::vector<int> vector;
        std::deque<int>  deque;

        // Vector Ford-Johnson
        std::vector<int> vectorMainChain;
        // std::vector<int> vectorPending;
        std::vector<PendingElement> vectorPending;

        // Odd leftover
        bool hasOdd;
        int oddValue;

    public:
        /* Orthodox Canonical Form */
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        /* 1. Parse */
        void parseValue(int argc, char *argv[]);

        /* 2. Make pairs */
        void makePairs();

        /* 3. Sort pairs */
        void sortPairs();

        /* 4. Create chains */
        void createChains();

        /* 5. Insert first pending */
        void insertFirstPending();

        /* 6. Jacobsthal */
        std::vector<size_t> generateJacobsthal(size_t size);
        std::vector<size_t> generateInsertionOrder(size_t size); 

        /* 7. Insert pending */
        void insertPending();

        /* 8. Odd leftover */
        void insertOdd();

        /* Debug */
        void printValue(const char *msg);
        void printPairs();
        void printChains();
};

#endif

/*
    program must use the merge-insert sort algorithm to sort the positive integer
    sequence.
*/