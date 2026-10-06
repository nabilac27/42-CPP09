/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 18:06:52 by nchairun         ###   ########.fr       */
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
#include <utility>

typedef std::vector<int>                  vect;
typedef std::vector<size_t>               vectSize;
typedef std::vector<std::pair<int, int> > vectPair;

class PmergeMe
{
    private:
            vect     vector;
            vect     vectorMainChain;
            vectPair vectorPending;

            bool     hasOdd;
            int      straggler;

        public:
            PmergeMe();
            PmergeMe(const PmergeMe &other);
            PmergeMe& operator=(const PmergeMe &other);
            ~PmergeMe();

            void parseValue(int argc, char *argv[]);
            void makePairs();
            void sortPairs();
            void createChains();
            void fordJohnsonVector(vect&    values);
            void insertFirstPending();

            vectSize generateJacobsthal(size_t size);
            vectSize generateInsertionOrder(size_t size);

            void insertPending();
            void insertStraggler();

            void printState(const char *msg, bool debug);
            void printPairs();
            void printChains(bool firstInserted);
};

#endif
