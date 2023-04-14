/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:52 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/12 16:06:52 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>


class BitcoinExchange
{
public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& oth);
    BitcoinExchange&    operator=(const BitcoinExchange& oth);
	class NoGoodDataBase : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
    class NoGoodInputFile : public std::exception
    {
    public:
        ~NoGoodInputFile() throw()
        {}
        explicit NoGoodInputFile(const std::string& arg) throw()
            : _arg("Error: bad input => " + arg)
        {}
        NoGoodInputFile(const NoGoodInputFile& oth) throw()
            : _arg(oth._arg)
        {}
        virtual const char* what() const throw();
    private:
        std::string _arg;
    };
    class NoPositiveValue : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
    class TooLargeValue : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
    void    parseInput(const std::string& inputName);
private:
    typedef std::map<std::string, double>::iterator         iterData;
    double  getNewValue(const std::string& date, double value);
	std::map<std::string, double>	_dataBase;
};
