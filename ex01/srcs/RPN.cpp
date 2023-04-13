/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:21:22 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/12 16:21:22 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <climits>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "RPN.hpp"

RPN::RPN() : _input("")
{}

RPN::~RPN()
{}

RPN::RPN(const RPN &oth) : _terms(oth._terms), _input(oth._input)
{}

RPN &RPN::operator=(const RPN &oth)
{
    if (&oth == this)
        return *this;
    _input = oth._input;
    _terms = oth._terms;
    return *this;
}

bool    isInt(const std::string& value)
{
    bool ret = false;

    for (size_t i = 0; i < value.size(); ++i)
    {
        ret = true;
        if (!std::isdigit(value[i]))
            return false;
    }
    return ret;
}

int RPN::doOp(const std::string& token)
{
    static const struct
    {
        int         (RPN::*handler)();
        std::string token;
    } operator_handle[4] =
            {
                    { &RPN::add, "+" },
                    { &RPN::sub, "-" },
                    { &RPN::div, "/" },
                    { &RPN::mul, "*" }
            };

    for (int i = 0; i < 4; ++i)
        if (operator_handle[i].token == token)
            return (this->*operator_handle[i].handler)();
    throw NotValidInput();
}

int RPN::result()
{
    std::stringstream   ss(_input);
    std::string         token;

    while (ss >> token)
    {
        if (isInt(token))
        {
            long val = std::strtol(token.c_str(), NULL, 10);
            if (val < INT_MIN || val > INT_MAX)
                throw std::invalid_argument("overflow");
            int intVal = static_cast<int>(val);
            _terms.push(intVal);
        }
        else
            _terms.push(doOp(token));
    }
    _input = "";
    if (_terms.size() == 1)
        return remove();
    return _terms.top();
}

void RPN::addInput(const std::string &input)
{
    _input += _input.empty() ? input : " " + input;
}

int RPN::add()
{
    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    return remove() + remove();
}

int RPN::sub()
{
    int a;

    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    a = remove();
    return remove() - a;
}

int RPN::div()
{
    int a;
    int b;

    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    a = remove();
    b = remove();
    if (a == 0)
        throw DivideByZero();
    return b / a;
}

int RPN::mul()
{
    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    return remove() * remove();
}

int RPN::remove()
{
    int ret = _terms.top();
    _terms.pop();
    return ret;
}

const char *RPN::NotEnoughNumbers::what() const throw()
{
    return "Error: not enough numbers for operator.";
}

const char *RPN::DivideByZero::what() const throw()
{
    return "Error: you tried to divide by 0.";
}

const char *RPN::NotValidInput::what() const throw()
{
    return "Error: not a valid input.";
}
