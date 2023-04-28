/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:54:44 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/14 12:54:44 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"
#include <sys/time.h>
#include <iomanip>

double launchTimer(PmergeMe& merger, void (PmergeMe::*fn)())
{
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    (merger.*fn)();
    clock_gettime(CLOCK_MONOTONIC, &end);

    double endNano = (double)end.tv_nsec * 1e-6;
    double startNano = (double)start.tv_nsec * 1e-6;
    endNano += (double)end.tv_sec * 1e3;
    startNano += (double)start.tv_sec * 1e3;
    return endNano - startNano;
}

void    printTest(size_t n, long double duration, const std::string& name)
{
    std::cout << "Time to process a range of " << std::setw(4) << n << " with "
              << name << " : " << std::fixed << duration << " ms" <<  std::endl;
}

int main(int ac, char **av)
{
    if (ac == 1)
        return 0;
    try
    {
        PmergeMe merger(ac - 1, av + 1);
        std::cout << "Before:\t";
        merger.elems();
        double duration1 = launchTimer(merger, &PmergeMe::processVecSort);
        double duration2 = launchTimer( merger, &PmergeMe::processDeqSort);
        std::cout << "After:\t";
        merger.result();
        printTest(merger.nbElements(), duration1, "std::vector");
        printTest(merger.nbElements(), duration2, "std::deque");
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}