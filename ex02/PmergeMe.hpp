/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 01:19:14 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

/* ************************************************************************** */
/*  INCLUDES                                                                  */
/* ************************************************************************** */
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

/* ************************************************************************** */
/*  TYPEDEFS                                                                  */
/* ************************************************************************** */
typedef std::vector<int>                  Vector;
typedef std::vector<size_t>               VectorSizeT;
typedef std::vector<std::pair<int, int> > VectorPair;

typedef std::deque<int>                   Deque;
typedef std::deque<std::pair<int, int> >  DequePair;

/* ************************************************************************** */
/*  ENUMS                                                                     */
/* ************************************************************************** */
enum Container
{
    VECTOR,
    DEQUE
};

enum Debug
{
    PAIRS,
    PAIRS_INDEX,
    CHAINS,
    CHAINS_FIRST_INSERTED
};

/* ************************************************************************** */
/*  CLASS                                                                     */
/* ************************************************************************** */
class PmergeMe
{
    private:
        /*  CONTAINERS   **************************************************** */
        Vector      vectorValues;
        Vector      vectorMainChain;
        VectorPair  vectorPendingChain;
        
        Deque       dequeValues;
        Deque       dequeMainChain;
        DequePair   dequePendingChain;

        bool        hasOdd;
        int         straggler;

    public:
        /*  OCF   ************************************************************ */
        PmergeMe();
        PmergeMe(const PmergeMe&    other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        /*  PUBLIC INTERFACE   ********************************************** */
        void        parseValue(int argc, char*  argv[]);
        double      sort(Container type);
        double      getTime();

        /*  PRINT     ******************************************************* */
        void        printState(const char* msg, Container type, bool debug);
        void        printTime(double time, Container type) const;
        void        printDebugging(Debug type);
        void        printInsertionChains(const VectorSizeT& order, size_t insertionCount);
        void        printRecursiveChains(const Vector& mainChain, const VectorPair& pendingChain, int depth, const std::string& stage);

    private:
        /*  FORD-JOHNSON    ************************************************* */
        template <typename ContainerType>
        void    makePairs(ContainerType &values);

        template <typename ContainerType>
        void    sortPairs(ContainerType &values);

        template <typename ContainerType, typename PairContainerType>
        void    createChains(ContainerType &values, ContainerType &mainChain, PairContainerType &pendingChain);

        template <typename ContainerType, typename PairContainerType>
        void    insertFirstPending(ContainerType &mainChain, PairContainerType &pendingChain);

        template <typename ContainerType, typename PairContainerType>
        void    insertPending(ContainerType &mainChain, PairContainerType &pendingChain);

        template <typename ContainerType>
        void    insertStraggler(ContainerType &values, ContainerType &mainChain);
        
        /*  MERGE-INSERTION SORT  ******************************************** */
        template <typename ContainerType>
        void    mergeInsertionSort(ContainerType &values, int depth, bool debug);

        /*  JACOBSTHAL SEQUENCE  ********************************************* */
        template <typename ContainerType>
        ContainerType generateJacobsthal(size_t size);

        template <typename ContainerType>
        ContainerType generateInsertionOrder(size_t size);

        /*  BINARY SEARCH INSERTION ****************************************** */
        template <typename ContainerType>
        void    binarySearchInsertion(ContainerType &mainChain, int value, int partner, bool hasPartner);
};

/* ************************************************************************** */
/*  TEMPLATE IMPLEMENTATIONS                                                  */
/* ************************************************************************** */
#include "PmergeMe.tpp"

#endif
