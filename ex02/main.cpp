/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/08 14:56:07 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe pmerge;

//         pmerge.parseValue(argc, argv);
//         pmerge.printState("Before", VECTOR, false);

//         double vectorTime = pmerge.sort(VECTOR);
//         double dequeTime  = pmerge.sort(DEQUE);

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

/*
    valgrind --leak-check=full --show-leak-kinds=all ./PmergeMe 9 8 7 6 5 4 3 2 1
*/

/* ************************************************************************** */
/* Main function with step-by-step debugging output                           */
/* ************************************************************************** */

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe pmerge;

        pmerge.parseValue(argc, argv);
        pmerge.printState("Initial", VECTOR, true);
        std::cout << "------------------------------------" << std::endl;

        // 1. Make pairs
        std::cout << "\n============================= [STEP 1] Make pairs             =============================" << std::endl;
        pmerge.makePairs(VECTOR);
        pmerge.printDebugging(PAIRS);

        // 2. Sort pairs by larger elements
        std::cout << "\n============================= [STEP 2] Sort pairs             =============================" << std::endl;
        pmerge.sortPairs(VECTOR);
        pmerge.printDebugging(PAIRS);

        // 3. Create main and pending chains
        std::cout << "\n============================= [STEP 3] Create chains          =============================" << std::endl;
        pmerge.createChains(VECTOR);
        pmerge.printDebugging(CHAINS);

        // 4. Insert first pending element
        std::cout << "\n============================= [STEP 4] Insert first pending   =============================" << std::endl;
        pmerge.insertFirstPending(VECTOR);
        pmerge.printDebugging(CHAINS_FIRST_INSERTED);

        // 5. Insert remaining pending elements
        std::cout << "\n============================= [STEP 5] Jacobsthal insertion   =============================" << std::endl;
        pmerge.insertPending(VECTOR);
        pmerge.printDebugging(CHAINS_FIRST_INSERTED);

        // 6. Insert straggler
        std::cout << "\n============================= [STEP 6] Insert straggler       =============================" << std::endl;
        pmerge.insertStraggler(VECTOR);

        // 7. Print final result
        pmerge.printState("Sorted", VECTOR, true);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}

// old main
// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe pmerge;

//         pmerge.parseValue(argc, argv);
//         pmerge.printState("Initial", VECTOR, true);
//         std::cout << " ------------------------------------" << std::endl;

//         // 1. Make pairs
//         pmerge.makePairs(VECTOR);
//         pmerge.printDebugging(PAIRS);
//         std::cout << " ------------------------------------" << std::endl;
                
//         // 2. Compare each pairs, and sort
//         pmerge.sortPairs(VECTOR);
//         pmerge.printDebugging(PAIRS);
//         std::cout << " ------------------------------------" << std::endl;

//         // 3. Recursively, sort, big elements, Create main chain + pending
//         pmerge.createChains(VECTOR);
//         pmerge.printDebugging(CHAINS);
//         std::cout << " ------------------------------------" << std::endl;

//         // 4. Insert first pending
//         pmerge.insertFirstPending(VECTOR);
//         pmerge.printDebugging(CHAINS_FIRST_INSERTED);
//         std::cout << " ------------------------------------" << std::endl;

        
//         // 5. Insert remaining pending using Jacobsthal order
//         pmerge.insertPending(VECTOR);
//         pmerge.printDebugging(CHAINS_FIRST_INSERTED);
//         std::cout << " ------------------------------------" << std::endl;
        
//         pmerge.insertStraggler(VECTOR);
//         pmerge.printDebugging(CHAINS_FIRST_INSERTED);
//         pmerge.printState("Sorted", VECTOR, true);
//     }
        
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return 1;
//     }

//     return (0);
// }
