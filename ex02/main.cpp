/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/10 04:55:25 by nchairun         ###   ########.fr       */
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

    ./PmergeMe $(shuf -i 1-16 -n 25)
    ./PmergeMe $(shuf -i 1-30 -n 12)
    ./PmergeMe $(shuf -i 1-100 -n 25)
    ./PmergeMe $(shuf -i 1-1000 -n 100)
  
    `shuf -i 1-1000 -n 3000 | tr "\n" " " `
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
