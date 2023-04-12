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

void    doOp(RPN& rpn, const std::string& token)
{
    static const struct
    {
        void        (RPN::*handler)();
        std::string token;
    } operator_handle[4] =
            {
                    { &RPN::add, "+" },
                    { &RPN::sub, "-" },
                    { &RPN::div, "*" },
                    { &RPN::mul, "/" }
            };

    for (int i = 0; i < 4; ++i)
    {
        if (operator_handle[i].token == token)
        {
            (rpn.*operator_handle[i].handler)();
            return;
        }
    }
}

int RPN::result()
{
    for (size_t pos = _input.find(' '); pos != std::string::npos; pos = _input.find(' '))
    {
        std::string token = _input.substr(0, pos);
        if (isInt(token))
        {
            long val = std::strtol(token.c_str(), NULL, 10);
            if (val < INT_MIN || val > INT_MAX)
                throw std::invalid_argument("overflow");
            int intVal = static_cast<int>(val);
            _terms.push(intVal);
        }
        else
            doOp(*this, token);
        _input.erase(0, pos + 1);
    }
    if (_terms.size() == 1)
        return remove();
    return _terms.front();
}

void RPN::addInput(const std::string &input)
{
    _input += input.empty() ? input : "" + input;
}

void RPN::add()
{
    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    _terms.front() = remove() + _terms.front();
}

void RPN::sub()
{
    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    _terms.front() = remove() - _terms.front();
}

void RPN::div()
{
    int a;

    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    a = remove();
    if (_terms.front() == 0)
        throw DivideByZero();
    _terms.front() = a / _terms.front();
}

void RPN::mul()
{
    if (_terms.size() < 2)
        throw NotEnoughNumbers();
    _terms.front() = remove() * _terms.front();
}

int RPN::remove()
{
    int ret = _terms.front();
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
