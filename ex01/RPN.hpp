/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:05:54 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 17:03:28 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <climits>

class RPN
{
  private:
	  std::list<long long>	listBasedStack;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& 	operator=(const RPN& other);
		~RPN();

		void	process(const std::string& expression);
		bool	parseExpression(const std::string& expression);
		long  	calculate(long leftOperand, long rightOperand, char operatorr);

		bool  	isOperator(char token);
		bool	isOverflow(long left, long right, char operatorr)
};

#endif

