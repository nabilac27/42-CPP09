/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 01:43:19 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/time.h>
#include <utility>
#include <vector>

typedef std::vector<int>    Vector;
typedef std::vector<size_t> VectorSizeT;
typedef std::vector<std::pair<int, int> > VectorPair;

typedef std::deque<int>     Deque;
typedef std::deque<std::pair<int, int> > DequePair;

enum Container
{
    VECTOR,
    DEQUE,
};

class PmergeMe2;

class PmergeMe
{
    private:
        friend class PmergeMe2;

        Vector      vectorValues;
        Vector      vectorMainChain;
        VectorPair  vectorPendingChain;

        Deque       dequeValues;
        Deque       dequeMainChain;
        DequePair   dequePendingChain;

        bool    hasOdd;
        int     straggler;

    public:
        /*  OCF   ************************************************************ */
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe&   operator=(const PmergeMe &other);
        ~PmergeMe();

         /*  PUBLIC INTERFACE   ********************************************** */
        void    parseValue(int argc, char *argv[]);
        double  sort(Container type);
        double  getTime();
        void    printState(const char *msg);
        void    printTime(double time, Container type) const;

        /*  FORD-JOHNSON STEPS *********************************************** */
        template <typename ContainerType>
        void    makePairs(ContainerType &values);

        template <typename ContainerType>
        void    sortPairs(ContainerType &values, int depth, bool debug);

        template <typename ContainerType, typename PairContainerType>
        void    createChains(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain);

        template <typename ContainerType, typename PairContainerType>
        void    insertFirstPending(ContainerType &mainChain, PairContainerType &pendingChain);

        template <typename ContainerType, typename PairContainerType>
        void    insertPending(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain);

         /*  RECURSIVE FORD JOHNSON  ****************************************** */
        template <typename ContainerType>
        void    recursiveFordJohnson(ContainerType &values, int depth);

        /*  JACOBSTHAL SEQUENCE  ********************************************* */
        template <typename ContainerType>
        ContainerType generateJacobsthal(size_t size);

        template <typename ContainerType>
        ContainerType generateInsertionOrder(size_t size);

        /*  BINARY SEARCH INSERTION ****************************************** */
        template <typename ContainerType>
        size_t  binarySearchInsertion(ContainerType &mainChain, int value, int partner, bool hasPartner);

};

// #include "PmergeMe.tpp"

#endif
