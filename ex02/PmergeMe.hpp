/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/08 16:48:51 by nchairun         ###   ########.fr       */
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
#include <sys/time.h>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <deque>


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
        // Vector
        Vector      vectorValues;
        Vector      vectorMainChain;
        VectorPair  vectorPendingChain;
        
        // Deque
        Deque       dequeValues;
        Deque       dequeMainChain;
        DequePair   dequePendingChain;

        // Current container state
        bool        hasOdd;
        int         straggler;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe&    other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        // Parsing
        void        parseValue(int argc, char*  argv[]);
        double      sort(Container type);

        // Ford-Johnson
        void        makePairs(Container type);
        void        sortPairs(Container type);

        void        createChains(Container type);
        void        insertFirstPending(Container type);
        void        insertPending(Container type);
        void        insertStraggler(Container type);

        // Recursive sorting
        void        fordJohnsonVector(Vector&   values, 
                                        int   depth = 0, 
                                        bool  debug = false);
        void        fordJohnsonDeque(Deque& values,
                                        int depth = 0,
                                        bool debug = false);    // to be implemented
        
        // Jacobsthal
        VectorSizeT generateJacobsthal(size_t size);
        VectorSizeT generateInsertionOrder(size_t size);

        // Utilities
        size_t      getSize(Container type) const;
        double      getTime();
        

        // Print
        void        printState(const char* msg, Container type, bool debug);
        void        printTime(double time, Container type) const;
        void        printDebugging(Debug type);
        void        printInsertionChains(const VectorSizeT& order, size_t insertionCount);
        void printRecursiveChains(const Vector& mainChain,
                          const VectorPair& pendingChain,
                          int depth,
                          const std::string& stage);
};

#endif
