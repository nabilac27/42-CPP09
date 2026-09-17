/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 22:02:57 by nchairun          #+#    #+#             */
/*   Updated: 2026/09/17 16:52:07 by nchairun         ###   ########.fr       */
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

class PmergeMe
{
	private:
		std::vector<int> vector;
		std::deque<int>  deque;

    public:
		PmergeMe();
		PmergeMe(const PmergeMe&    other); 
		PmergeMe &operator=(const PmergeMe& other); 
		~PmergeMe(); 
		
		void parseValue(int argc, char *argv[]);
		void printValue(const char* msg);
		void printMakePairs();
		void makePairs();

		
};

#endif