/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:52 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/12 16:06:52 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <iostream>
#include "BitcoinExchange.hpp"

int countColumn(const std::string& firstLine, char delim)
{
    int                 len = 0;
    std::string         _;
    std::stringstream   ss(firstLine);

    while (std::getline(ss, _, delim))
        len++;
    return len;
}

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	ifs("resources/data.csv");
	std::string 	buf;

	if (!ifs || !std::getline(ifs, buf) || countColumn(buf, ',') != 2)
        throw NoGoodDataBase();
	while (std::getline(ifs, buf))
	{
		std::stringstream	ss(buf);
		std::string			token;

		if (!std::getline(ss, token, ','))
            throw NoGoodDataBase();
        std::string date(token);

        if (!std::getline(ss, token, ','))
            throw NoGoodDataBase();
        double  exchange = std::strtod(token.c_str(), NULL);

        std::pair<std::string, double>  input(date, exchange);
        _dataBase.insert(input);
    }
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &oth)
    : _dataBase(oth._dataBase)
{}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &oth)
{
	if (&oth == this)
		return *this;
    for (iterData it = _dataBase.begin(); it != _dataBase.end(); ++it)
    {
        _dataBase.insert(*it);
    }
	return *this;
}

std::string& trim(std::string& s)
{
    s.erase(s.find_last_not_of(" \n\t\r\f\v") + 1);
    s.erase(0, s.find_first_not_of(" \n\t\r\f\v"));
    return s;
}

bool    isValidDate(const std::string& date)
{
    std::stringstream   ss(date);
    std::string         token;

    if (countColumn(date, '-') != 3)
        return false;
    std::getline(ss, token, '-');
    long year = std::strtol(token.c_str(), NULL, 10);
    if (year < 1900 || year >= 3000)
        return false;
    std::getline(ss, token, '-');
    long month = std::strtol(token.c_str(), NULL, 10);
    if (month > 12 || month < 1)
        return false;
    std::getline(ss, token, '-');
    long day = std::strtol(token.c_str(), NULL, 10);
    if (day < 1 || day > 31)
        return false;
    return true;
}

void BitcoinExchange::parseInput(const std::string& inputName)
{
    std::ifstream   input(inputName.c_str());
    std::string     buf;

    if (!input)
        throw NoGoodInputFile(inputName + " is not valid");
    if (!std::getline(input, buf))
        throw NoGoodInputFile( "file is empty");
    if (countColumn(buf, '|') != 2)
        throw NoGoodInputFile("you don't have 2 column");
    while (std::getline(input, buf))
    {
        try
        {
            std::stringstream	ss(buf);
            std::string			token;
            if (!std::getline(ss, token, '|'))
                throw NoGoodInputFile("no date");
            std::string date(trim(token));
            if (!isValidDate(date))
                throw NoGoodInputFile(date);

            if (!std::getline(ss, token, ','))
                throw NoGoodInputFile("no exchange value");
            double  value = std::strtod(trim(token).c_str(), NULL);
            if (value > 1000)
                throw TooLargeValue();
            if (value < 0)
                throw NoPositiveValue();
            double newValue = getNewValue(date, value);
            std::cout << date << " => " << value << " = " << newValue << std::endl;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

double BitcoinExchange::getNewValue(const std::string &date, double value)
{
    iterData it = _dataBase.lower_bound(date);

    if (it == _dataBase.end())
        throw NoGoodInputFile("too recent date");
    if (it->first == date)
        return it->second * value;
    if (it == _dataBase.begin())
        throw NoGoodInputFile("too ancient date");
    it--;
    return it->second * value;
}

const char *BitcoinExchange::NoGoodDataBase::what() const throw()
{
	return "Error: no database present.";
}

const char *BitcoinExchange::NoGoodInputFile::what() const throw()
{
    return _arg.c_str();
}

const char *BitcoinExchange::NoPositiveValue::what() const throw()
{
    return "Error: not a positive number.";
}

const char *BitcoinExchange::TooLargeValue::what() const throw()
{
    return "Error: too large a number.";
}
