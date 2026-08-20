/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/21 00:06:45 by nchairun          #+#    #+#             */
/*   Updated: 2026/08/21 00:08:58 by nchairun         ###   ########.fr       */
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
	this->numbers = other.numbers;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		this->numbers = other.numbers;
	return (*this);
}

RPN::~RPN()
{
}