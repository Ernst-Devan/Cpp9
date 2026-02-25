#include "PmergeMe.hpp"
#include <iostream>
#include <cstdio>

void    PmergeMe::create_initial_vector(char **nbs, int ac)
{
    std::vector<int> list;

    for(int i = 1; i < ac; i++)
    {
        int tmp;

        sscanf(nbs[i], "%d", &tmp);
        list.push_back(tmp);
    }
    create_pair_list(list);
    
}

void    PmergeMe::create_pair_list(std::vector<int>& list)
{
    std::vector<int>::iterator it = list.begin();
    std::vector<std::pair<int,int> > pair_list;
    std::vector<int> main;

    if (list.size() <= 1)
        return;

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

    sort_pair_list(pair_list);
    main = take_max(pair_list);
    show_each_pair(pair_list);

    create_pair_list(main);
    
    // show_list(max_list);
    // pair_list = reorder_pair_list(max_list, pair_list);
    insert_first_littlefyuxhj
    main.insert(main.begin());
}

void    PmergeMe::insert_first_little(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list)
{

}

std::vector<std::pair<int, int> >   PmergeMe::reorder_pair_list(std::vector<int>& max_list, std::vector<std::pair<int, int> >& pair_list)
{
    std::vector<std::pair<int,int> > ordered_pair;

    std::vector<std::pair<int, int> >::iterator it_pair = pair_list.begin(); 

    // show_list(max_list);

    while (max_list.size() >= 1)
    {
        while ((*it_pair).second != max_list.back())
        {
            it_pair++;
        }
        ordered_pair.push_back(*it_pair);
        max_list.pop_back();
        it_pair = pair_list.begin();
        
    }

    std::cout << std::endl;
    show_each_pair(ordered_pair);
    return ordered_pair;
}

std::vector<int>   PmergeMe::take_max(std::vector<std::pair<int,int> >& pair_list)
{
    std::vector<int> list;
    std::vector<std::pair<int, int> >::iterator it = pair_list.begin();

    while (it != pair_list.end())
    {
        list.push_back((*it).second);
        it++;
    }
    return list;
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
