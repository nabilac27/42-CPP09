/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:06:45 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/27 21:27:07 by nchairun         ###   ########.fr       */
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

void RPN::process(const std::string& expression)
{
	if (!parseExpression(expression))
		throw (std::runtime_error("Error"));
}

bool RPN::parseExpression(const std::string& expression)
{
	std::stringstream	ss(expression);
	std::string			token;

	while (ss >> token)
	{
		std::cout << "Token: " << token << std::endl;
	}

	return (true);
}