/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:56:23 by ambouren          #+#    #+#             */
/*   Updated: 2023/04/14 12:56:23 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <string>
#ifdef DEBUG
#define MAX_SIZE_PRINT -1
#else
#define MAX_SIZE_PRINT 5
#endif

class PmergeMe
{
public:
    ~PmergeMe();
    PmergeMe(int ac, char **args);
    class BadInput : public std::exception
    {
    public:
        const char * what() const throw();
    };
    void    processVecSort();
    void    processDeqSort();
    size_t  nbElements() const;
    void    elems() const;
    void    result() const;
private:
    typedef std::pair<int, int> pairInts;
    typedef std::vector<int>::iterator iterVecInt;
    typedef std::vector<pairInts>::iterator iterVecInts;
    typedef std::deque<int>::iterator iterDeqInt;
    typedef std::deque<pairInts>::iterator iterDeqInts;
    PmergeMe();
    PmergeMe(const PmergeMe& oth);
    PmergeMe&   operator=(const PmergeMe& oth);

    std::vector<int>    _baseElements;
    std::vector<int>    _vecNumbers;
    std::deque<int>     _deqNumbers;
    size_t              _nbElements;
};
