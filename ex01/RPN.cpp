/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:06:45 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/06 19:12:20 by nchairun         ###   ########.fr       */
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
	numbers = other.numbers;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		numbers = other.numbers;
	return (*this);
}

RPN::~RPN()
{
}

/* ************************************************************************** */
/*  process()                                                  				  */
/* ************************************************************************** */
void RPN::process(const std::string& expression)
{
	if (!parseExpression(expression))
		throw (std::runtime_error("ERROR: parseExpression()"));
	if (numbers.size() != 1)
		throw (std::runtime_error("ERROR: stack size() not 1"));
	std::cout << numbers.top() << std::endl;
}

/* ************************************************************************** */
/*  parseExpression()                                                  		  */
/* ************************************************************************** */
bool RPN::parseExpression(const std::string& expression)
{
	std::stringstream	ss(expression);
	std::string			token;

	while (ss >> token)
	{
		if (token.length() == 1
			&& std::isdigit(static_cast<unsigned char>(token[0])))
			numbers.push(token[0] - '0');
		else if (token.length() == 1 && isOperator(token[0]))
		{
			if (numbers.size() < 2)
				return (false);

			int right = numbers.top();
			numbers.pop();

			int left = numbers.top();
			numbers.pop();

			int result = calculate(left, right, token[0]);

			numbers.push(result);
		}
		else
			return (false);
	}

	return (true);
}

/* ************************************************************************** */
/*  calculate()   				                                              */
/* ************************************************************************** */
int RPN::calculate(int left, int right, char operation)
{
	switch (operation)
	{
		case '+':
			return (left + right);

		case '-':
			return (left - right);

		case '*':
			return (left * right);

		case '/':
			if (right == 0)
				throw (std::runtime_error("ERROR: calculate(), division by zero"));
			return (left / right);
	}
	throw (std::runtime_error("ERROR: calculate()"));
}

/* ************************************************************************** */
/*  isOperator()			                                                  */
/* ************************************************************************** */
bool RPN::isOperator(char token)
{
	return (token == '+'
		|| token == '-'
		|| token == '*'
		|| token == '/');
}

