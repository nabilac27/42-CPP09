/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:06:45 by nchairun          #+#    #+#             */
/*   Updated: 2026/10/08 05:01:14 by nchairun         ###   ########.fr       */
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
		throw (std::runtime_error("ERROR: invalid token in parseExpression()"));
	if (numbers.size() != 1)
		throw (std::runtime_error("ERROR: list size() not 1"));
	std::cout << numbers.back() << std::endl;
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
			numbers.push_back(token[0] - '0');
		else if (token.length() == 1 && isOperator(token[0]))
		{
			if (numbers.size() < 2)
				return (false);

			long long right = numbers.back();
			numbers.pop_back();
			long long left = numbers.back();
			numbers.pop_back();
			long long result = calculate(left, right, token[0]);

			numbers.push_back(result);
		}
		else
			return (false);
	}

	return (true);
}

/* ************************************************************************** */
/*  calculate()   				                                              */
/* ************************************************************************** */
long long RPN::calculate(long long left, long long right, char operation)
{
	switch (operation)
	{
		case '+':
			return (left + right);

		case '-':
			return (left - right);

		case '*':
			if ((left > 0 && right > 0 && left > LLONG_MAX / right)
			|| (left < 0 && right < 0 && left < LLONG_MAX / right)
			|| (left > 0 && right < 0 && right < LLONG_MIN / left)
			|| (left < 0 && right > 0 && left < LLONG_MIN / right))
				throw std::runtime_error("ERROR: multiplication overflow in calculate()");
    		return (left * right);

		case '/':
			if (right == 0)
				throw (std::runtime_error("ERROR: division by zero in calculate()"));
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

