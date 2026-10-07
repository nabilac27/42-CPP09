/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:05:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/07 05:00:13 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>

class RPN
{
  private:
	  std::list<long long> numbers;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

    void	process(const std::string& expression);
    bool	parseExpression(const std::string& expression);
    bool  	isOperator(char token);
    int   	calculate(int left, int right, char operation);
};

#endif

