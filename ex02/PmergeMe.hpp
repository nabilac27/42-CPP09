/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/07 02:39:37 by nchairun         ###   ########.fr       */
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
typedef std::deque<size_t>                DequeSizeT;
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

        // Ford-Johnson
        void        makePairs(Container type);
    
    /* ------ to change for deque ------ */
        void        sortPairs(Container type);

        void        createChains();
        void        insertFirstPending();
        void        insertPending();
        void        insertStraggler();

        // Recursive sorting
        void        fordJohnsonVector(Vector&   values, 
                                        int   depth = 0, 
                                        bool  debug = false);
        
        // Jacobsthal
        VectorSizeT generateJacobsthal(size_t size);
        VectorSizeT generateInsertionOrder(size_t size);

        // Utilities
        size_t      getVectorSize() const;
        double      getTime();
        
/* ------ to change for deque ------ */

        // Print
        void        printState(const char*  msg, bool debug);
        void        printTime(double time, const std::string &container) const;
        void        printDebugging(Debug type);
};

#endif
