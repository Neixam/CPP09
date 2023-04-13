/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:21:22 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/12 16:21:22 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <string>

class RPN
{
public:
    RPN();
    ~RPN();
    RPN(const RPN& oth);
    RPN&    operator=(const RPN& oth);
    int     result();
    void    addInput(const std::string& input);
    class   NotEnoughNumbers : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
    class   DivideByZero : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
    class   NotValidInput : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
private:
    int     remove();
    int     doOp(const std::string& token);
    int     add();
    int     sub();
    int     div();
    int     mul();
    std::stack<int> _terms;
    std::string     _input;
};


#endif
