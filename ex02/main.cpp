/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/07 05:14:24 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"


int main(int argc, char *argv[])
{
    try
    {
        PmergeMe pmerge;

        pmerge.parseValue(argc, argv);
        pmerge.printState("Before", VECTOR, false);

        double vectorTime = pmerge.sort(VECTOR);
        double dequeTime  = pmerge.sort(DEQUE);

        pmerge.printState("After ", VECTOR, false);
        pmerge.printTime(vectorTime, VECTOR);
        pmerge.printTime(dequeTime, DEQUE);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}
/*
    valgrind --leak-check=full --show-leak-kinds=all ./PmergeMe 9 8 7 6 5 4 3 2 1
*/

// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe pmerge;

//         pmerge.parseValue(argc, argv);
//         pmerge.printState("Before", VECTOR, false);

//         // Vector
//         double vectorStart = pmerge.getTime();

//         pmerge.makePairs(VECTOR);
//         pmerge.sortPairs(VECTOR);
//         pmerge.createChains(VECTOR);
//         pmerge.insertFirstPending(VECTOR);
//         pmerge.insertPending(VECTOR);
//         pmerge.insertStraggler(VECTOR);

//         double vectorEnd  = pmerge.getTime();
//         double vectorTime = vectorEnd - vectorStart;

//         // Deque
//         double dequeStart = pmerge.getTime();

//         pmerge.makePairs(DEQUE);
//         pmerge.sortPairs(DEQUE);
//         pmerge.createChains(DEQUE);
//         pmerge.insertFirstPending(DEQUE);
//         pmerge.insertPending(DEQUE);
//         pmerge.insertStraggler(DEQUE);

//         double dequeEnd  = pmerge.getTime();
//         double dequeTime = dequeEnd - dequeStart;

//         // Print
//         pmerge.printState("After ", VECTOR, false);
//         pmerge.printTime(vectorTime, VECTOR);
//         pmerge.printTime(dequeTime, DEQUE);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return (1);
//     }

//     return (0);
// }

// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe pmerge;

//         pmerge.parseValue(argc, argv);
//         pmerge.printState("Before", VECTOR, false);

//         double start = pmerge.getTime();
             
//         pmerge.makePairs(VECTOR);
//         pmerge.sortPairs(VECTOR);

//         pmerge.createChains(VECTOR);
//         pmerge.insertFirstPending(VECTOR);
        
//         pmerge.insertPending(VECTOR);
//         pmerge.insertStraggler(VECTOR);

//         double end        = pmerge.getTime();
//         double vectorTime = end - start;    // in s = (end - start) / 1000000.0; 
        
//         pmerge.printState("After ", VECTOR, false);
//         pmerge.printTime(vectorTime, VECTOR);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return (1);
//     }

//     return (0);
// }

/* ************************************************************************** */
/* Main function with step-by-step debugging output                           */
/* ************************************************************************** */

// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe pmerge;

//         pmerge.parseValue(argc, argv);
//         pmerge.printState("Initial", true);
//         std::cout << " ------------------------------------" << std::endl;

//         // 1. Make pairs
//         pmerge.makePairs();
//         pmerge.printDebugging(PAIRS);
//         std::cout << " ------------------------------------" << std::endl;
                
//         // 2. Compare each pairs, and sort
//         pmerge.sortPairs();
//         pmerge.printDebugging(PAIRS);
//         std::cout << " ------------------------------------" << std::endl;

//         // 3. Recursively, sort, big elements, Create main chain + pending
//         pmerge.createChains();
//         pmerge.printDebugging(CHAINS);
//         std::cout << " ------------------------------------" << std::endl;

//         // 4. Insert first pending
//         pmerge.insertFirstPending();
//         pmerge.printDebugging(CHAINS_FIRST_INSERTED);
//         std::cout << " ------------------------------------" << std::endl;

        
//         // 5. Insert remaining pending using Jacobsthal order
//         pmerge.insertPending();
//         pmerge.printDebugging(CHAINS_FIRST_INSERTED);
//         std::cout << " ------------------------------------" << std::endl;
        
//         pmerge.insertStraggler();
//         pmerge.printDebugging(CHAINS_FIRST_INSERTED);
//         pmerge.printState("Sorted", true);
//     }
        
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }
