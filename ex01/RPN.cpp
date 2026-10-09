/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:06:45 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/09 17:09:54 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/* ************************************************************************** */
/*  ORTHODOX CANONICAL FORM                                                   */
/* ************************************************************************** */
RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
	listBasedStack = other.listBasedStack;
}

RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
		listBasedStack = other.listBasedStack;
	return (*this);
}

RPN::~RPN()
{
}

/* ************************************************************************** */
/*  process()                                                  				  */
/* ************************************************************************** */
void	RPN::process(const std::string& expression)
{
	if (!parseExpression(expression))
		throw (std::runtime_error("ERROR: invalid token in parseExpression()"));
	if (listBasedStack.size() != 1)
		throw (std::runtime_error("ERROR: list size() not 1"));
	std::cout << listBasedStack.back() << std::endl;
}

/* ************************************************************************** */
/*  parseExpression()                                                  		  */
/* ************************************************************************** */
bool	RPN::parseExpression(const std::string& expression)
{
	std::stringstream	ss(expression);
	std::string			token;
	long 				rightOperand, leftOperand, result;
	
	while (ss >> token)
	{
		if (token.length() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
			listBasedStack.push_back(token[0] - '0');
	
		else if (token.length() == 1 && isOperator(token[0]))
		{
			if (listBasedStack.size() < 2)
				return (false);

			rightOperand	= listBasedStack.back();
			listBasedStack.pop_back();
			
			leftOperand		= listBasedStack.back();
			listBasedStack.pop_back();
	
			result 			= calculate(leftOperand, rightOperand, token[0]);
			listBasedStack.push_back(result);
		}
		else
			return (false);
	}
	return (true);
}

/* ************************************************************************** */
/*  calculate()   				                                              */
/* ************************************************************************** */
long	RPN::calculate(long leftOperand, long rightOperand, char operatorr)
{
	if (operatorr == '/' && rightOperand == 0)
        throw (std::runtime_error("ERROR: division by zero"));
    if (isOverflow(leftOperand, rightOperand, operatorr))
        throw (std::runtime_error("ERROR: arithmetic overflow"));

	switch (operatorr)
	{
		case '+':
			return (leftOperand + rightOperand);
		case '-':
			return (leftOperand - rightOperand);
		case '*':
    		return (leftOperand * rightOperand);
		case '/':
			return (leftOperand / rightOperand);
	}
	throw (std::runtime_error("ERROR: invalid operator"));
}



/* ************************************************************************** */
/*  isOperator()			                                                  */
/* ************************************************************************** */
bool	RPN::isOperator(char token)
{
	return (token == '+' || token == '-' || token == '*' || token == '/');
}

bool	RPN::isOverflow(long leftOperand, long rightOperand, char operatorr)
{
    switch (operatorr)
    {
        case '+':
            return ((rightOperand > 0 && leftOperand > LONG_MAX - rightOperand)
                || (rightOperand < 0 && leftOperand < LONG_MIN - rightOperand));
        case '-':
            return ((rightOperand < 0 && leftOperand > LONG_MAX + rightOperand)
                || (rightOperand > 0 && leftOperand < LONG_MIN + rightOperand));
        case '*':
            return ((leftOperand > 0 && rightOperand > 0 && leftOperand > LONG_MAX / rightOperand)
                || (leftOperand < 0 && rightOperand < 0 && leftOperand < LONG_MAX / rightOperand)
                || (leftOperand > 0 && rightOperand < 0 && rightOperand < LONG_MIN / leftOperand)
                || (leftOperand < 0 && rightOperand > 0 && leftOperand < LONG_MIN / rightOperand));
        case '/':
            return (leftOperand == LONG_MIN && rightOperand == -1);
    }
    return (false);
}