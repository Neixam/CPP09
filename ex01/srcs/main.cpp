/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:21:13 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/12 16:21:13 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
    RPN rpn;

    for (int i = 1; i < ac; i++)
        rpn.addInput(av[i]);
    try
    {
        std::cout << rpn.result() << std::endl;
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}