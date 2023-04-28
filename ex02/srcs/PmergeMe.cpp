/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:56:23 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/14 12:56:23 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <iostream>
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const PmergeMe &oth)
{
    *this = oth;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &oth)
{
    if (&oth == this)
        return *this;
    _vecNumbers = oth._vecNumbers;
    _deqNumbers = oth._deqNumbers;
    return *this;
}

PmergeMe::~PmergeMe()
{}

PmergeMe::PmergeMe()
{}

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

PmergeMe::PmergeMe(int ac, char **args)
{
    for (int i = 0; i < ac; ++i)
    {
        std::stringstream   ss(args[i]);
        std::string         token;

        while (ss >> token)
        {
            if (!isInt(token))
                throw BadInput();
            long value = std::strtol(token.c_str(), NULL, 10);
            if (value > INT_MAX || value <= 0)
                throw BadInput();
            if (std::find(_baseElements.begin(), _baseElements.end(), static_cast<int>(value)) != _baseElements.end())
                throw BadInput();
            _baseElements.push_back(static_cast<int>(value));
            _vecNumbers.push_back(static_cast<int>(value));
            _deqNumbers.push_back(static_cast<int>(value));
        }
    }
    _nbElements = _vecNumbers.size();
}

bool    comparePair(std::pair<int, int> p1, std::pair<int, int> p2)
{
    return p1.first < p2.first;
}

std::ostream& operator<<(std::ostream& os, const std::pair<int, int>& pair)
{
    return os << "(" << pair.first << ", " << pair.second << ")";
}

template<typename It>
void    print(const It& begin, const It& end)
{
    int i = 1;
    It it = begin;

    for (; it != end - 1 && i < MAX_SIZE_PRINT; it++, i++)
        std::cout << *it << " ";
    std::cout << *(it++);
    if (i == MAX_SIZE_PRINT && it != end)
        std::cout << " [...]";
    std::cout << std::endl;
}

template<typename It>
void    insertInGoodPlace(It& it, const It& begin, const It& end, int value)
{
    if (value < *it)
    {
        for (; it != end && value < *it; it++)
            ;
    }
    else
    {
        for (; it != begin && value > *(it - 1); it--)
            ;
    }
}

template<typename T, typename It>
void insertInGoodPlace(T& tab, It& it, int value)
{
    insertInGoodPlace(it, tab.begin(), tab.end(), value);
    it = tab.insert(it, value);
}

void PmergeMe::processVecSort()
{
    std::vector<pairInts>   pairs;
    int                     last = -1;
    iterVecInt              itInit;

    itInit = _vecNumbers.begin();
    if (_vecNumbers.size() % 2 == 1)
    {
        last = *itInit;
        itInit++;
    }
    for (; itInit != _vecNumbers.end(); itInit += 2)
    {
        pairInts input(*itInit, *(itInit + 1));
        if (input.first > input.second)
            std::swap(input.first, input.second);
        pairs.push_back(input);
    }
    _vecNumbers.clear();
    std::sort(pairs.begin(), pairs.end(), comparePair);
    for (iterVecInts it = pairs.begin(); it != pairs.end(); ++it)
        _vecNumbers.insert(_vecNumbers.begin(), it->first);
    iterVecInt it2 = _vecNumbers.begin();
    for (iterVecInts it = pairs.begin(); it != pairs.end(); ++it)
        insertInGoodPlace(_vecNumbers, it2, it->second);
    if (last != -1)
        insertInGoodPlace(_vecNumbers, it2, last);
}

void PmergeMe::processDeqSort()
{
    std::deque<pairInts>    pairs;
    int                     last = -1;
    iterDeqInt              itInit;

    itInit = _deqNumbers.begin();
    if (_deqNumbers.size() % 2 == 1)
    {
        last = *itInit;
        itInit++;
    }
    for (; itInit != _deqNumbers.end(); itInit += 2)
    {
        pairInts input(*itInit, *(itInit + 1));
        if (input.first > input.second)
            std::swap(input.first, input.second);
        pairs.push_back(input);
    }
    _deqNumbers.clear();
    std::sort(pairs.begin(), pairs.end(), comparePair);
    for (iterDeqInts it = pairs.begin(); it != pairs.end(); ++it)
        _deqNumbers.insert(_deqNumbers.begin(), it->first);
    iterDeqInt it2 = _deqNumbers.begin();
    for (iterDeqInts it = pairs.begin(); it != pairs.end(); ++it)
        insertInGoodPlace(_deqNumbers, it2, it->second);
    if (last != -1)
        insertInGoodPlace(_deqNumbers, it2, last);
}

size_t PmergeMe::nbElements() const
{
    return _nbElements;
}

void PmergeMe::elems() const
{
    print(_baseElements.begin(), _baseElements.end());
}

void PmergeMe::result() const
{
    print(_vecNumbers.rbegin(), _vecNumbers.rend());
}

const char *PmergeMe::BadInput::what() const throw()
{
    return "Error";
}
