/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 23:25:27 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iomanip>

// int main(int argc, char *argv[])
// {
//     try
//     {
//         PmergeMe pmerge;

//         pmerge.parseValue(argc, argv);
//         pmerge.printState("Before", false);
        
//         double start = pmerge.getTime();
             
//         pmerge.makePairs();
//         pmerge.sortPairs();

//         pmerge.createChains();
//         pmerge.insertFirstPending();
        
//         pmerge.insertPending();
//         pmerge.insertStraggler();

//         double end = pmerge.getTime();
        
//         pmerge.printState("After ", false);


//         double vectorTime = end - start;

//         std::cout << "Time to process a range of "
//                 << pmerge.getVectorSize()
//                 << " elements with std::vector : "
//                 << std::fixed << std::setprecision(5)
//                 << vectorTime
//                 << " us"
//                 << std::endl;

//         // double vectorTime2 = (end - start) / 1000000.0; // seconds
//         //         std::cout << "Time to process a range of "
//         //         << pmerge.getSize()
//         //         << " elements with std::vector : "
//         //         << std::fixed << std::setprecision(5)
//         //         << vectorTime2
//         //         << " s"
//         //         << std::endl;
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe pmerge;

        pmerge.parseValue(argc, argv);
        pmerge.printState("Initial", true);
        std::cout << " ------------------------------------" << std::endl;

        // 1. Make pairs
        pmerge.makePairs();
        pmerge.printDebugging(PAIRS);
        std::cout << " ------------------------------------" << std::endl;
                
        // 2. Compare each pairs, and sort
        pmerge.sortPairs();
        pmerge.printDebugging(PAIRS);
        std::cout << " ------------------------------------" << std::endl;

        // 3. Recursively, sort, big elements, Create main chain + pending
        pmerge.createChains();
        pmerge.printDebugging(CHAINS);
        std::cout << " ------------------------------------" << std::endl;

        // 4. Insert first pending
        pmerge.insertFirstPending();
        pmerge.printDebugging(CHAINS_FIRST_INSERTED);
        std::cout << " ------------------------------------" << std::endl;

        
        // 5. Insert remaining pending using Jacobsthal order
        pmerge.insertPending();
        pmerge.printDebugging(CHAINS_FIRST_INSERTED);
        pmerge.printState("Sorted", true);
        std::cout << " ------------------------------------" << std::endl;
        
        pmerge.insertStraggler();
        pmerge.printDebugging(CHAINS_FIRST_INSERTED);
        pmerge.printState("Sorted", true);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
