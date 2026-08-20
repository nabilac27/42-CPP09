/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:05:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/21 00:08:21 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

class RPN
{
	private:
		std::stack<int> numbers;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

};

#endif


/*
    Why do we use std::stack?
    Because RPN naturally works with the last numbers we encountered first.

    A stack follows:
        LIFO — Last In, First Out
    
                      RPN expression
                    │
                    ▼
              Read each token
                    │
             ┌──────┴──────┐
             │             │
          Number        Operator
             │             │
             ▼             ▼
           push       pop 2 numbers
                           │
                           ▼
                      calculate
                           │
                           ▼
                         push
                           │
                           ▼
                       next token

*/