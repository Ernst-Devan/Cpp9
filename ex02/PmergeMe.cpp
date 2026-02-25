#include "PmergeMe.hpp"
#include <iostream>
#include <cstdio>

void    PmergeMe::create_initial_vector(char **nbs, int ac)
{
    std::vector<int> list;
    std::vector<std::pair<int,int> > raw_pair_list;

    for(int i = 1; i < ac; i++)
    {
        int tmp;

        sscanf(nbs[i], "%d", &tmp);
        list.push_back(tmp);
    }

    create_pair_list(list, raw_pair_list);
    
}

std::vector<int>    PmergeMe::create_pair_list(std::vector<int>& list, std::vector<std::pair<int,int> >& raw)
{
    std::vector<int>::iterator it = list.begin();
    std::vector<std::pair<int,int> > pair_list;
    std::vector<int> main;

    
    while (it != list.end())
    {
        int first;
        int second;
        
        first = *it++;
        if (it == list.end())
        break;
        second = *it++;
        pair_list.push_back(std::make_pair(first, second));
    }
    
    if (raw.empty())
    raw = pair_list;
    
    sort_pair_list(pair_list);
    take_max(main ,pair_list);

    if (list.size() <= 1)
        return max;

    std::vector<int> sorted_main = create_pair_list(main, raw);

    insert_first_little(sorted_main, raw);

    return sorted_main;
}

void    PmergeMe::insert_first_little(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list)
{
    std::cout << "test:" << std::endl;
    show_list(main);
    main.insert(main.begin(), get_little_from_bigger(pair_list ,main[0]));
    std::cout << "test:" << std::endl;
    show_list(main);

    std::cout << std::endl;
}

int    PmergeMe::get_little_from_bigger(std::vector<std::pair<int, int> >& pair_list, int bigger)
{
    std::vector<std::pair<int, int> >::iterator it = pair_list.begin();

    while (it != pair_list.end())
    {
        if ((*it).second == bigger)
            return (*it).first;
        it++;
    }

    return -1;
}

static  int is_inside(std::vector<int> list, int nb)
{
    std::vector<int>::iterator it = list.begin();

    while (it != list.end())
    {
        if (*it == nb)
            return 1;   
        it++;
    }
    return 0;
}

void    PmergeMe::take_max(std::vector<int>& main, std::vector<std::pair<int,int> >& pair_list)
{
    std::vector<std::pair<int, int> >::iterator it = pair_list.begin();


    while (it != pair_list.end())
    {
        if (!is_inside(main, (*it).second))
            main.push_back((*it).second);
        it++;
    }
}


void    PmergeMe::show_each_pair(std::vector<std::pair<int,int> >& pair_list)
{
    std::vector<std::pair<int,int> >::iterator it = pair_list.begin();
    while (it != pair_list.end())
    {
        std::pair<int,int> test;
        test = *it;
        std::cout << test.first << " ";
        std::cout << test.second;
        std::cout << " | ";
        it++;
    }
    std::cout << std::endl;
}

void    PmergeMe::show_list(std::vector<int>& list)
{
    std::vector<int>::iterator it = list.begin();

    while (it != list.end())
    {
        std::cout << *it;
        std::cout << " ";
        it++;
    }
    std::cout << std::endl;
}

void    swap_pair(std::pair<int, int>& pair)
{
    int tmp;

    tmp = pair.first;
    pair.first = pair.second;
    pair.second = tmp;
}


void    PmergeMe::sort_pair_list(std::vector<std::pair<int,int> >& pair_list)
{
    std::vector<std::pair<int,int> >::iterator it = pair_list.begin();

    while (it != pair_list.end())
    {
        if ((*it).first > (*it).second)
            swap_pair(*it);
        it++;
    }    
}
