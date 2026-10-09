/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 15:33:22 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 02:13:43 by nchairun         ###   ########.fr       */
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
    PmergeMe pmerge;

    pmerge.parseValue(argc, argv);
    pmerge.printState("[Before]", VECTOR, false);

    pmerge.sort(DEBUG_MODE);
    pmerge.printState("[After ]", VECTOR, false);
    
    return (0);
}