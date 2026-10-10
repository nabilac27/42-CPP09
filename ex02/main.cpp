/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 02:00:48 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
    try
    {
        PmergeMe pmerge;

        pmerge.parseValue(argc, argv);
        pmerge.printState("Before");

        double vectorTime = pmerge.sort(VECTOR);
        double dequeTime  = pmerge.sort(DEQUE);

        pmerge.printState("After ");
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

    4 7 6 5  3 1  4 2 1 5 4 3 5 6 2 3 4 5
*/

// /* ************************************************************************** */
// /* Main function with step-by-step debugging output                           */
// /* ************************************************************************** */
// #include "debug/PmergeMe2.hpp"
// int main(int argc, char *argv[])
// {
//     PmergeMe pmerge;
//     PmergeMe2 debugger;

//     pmerge.parseValue(argc, argv);
//     debugger.printDebugState(pmerge, "Before", VECTOR, true);
//     debugger.sortDebug(pmerge);
//     debugger.printDebugState(pmerge, "After ", VECTOR, true);

//     return (0);
// }
