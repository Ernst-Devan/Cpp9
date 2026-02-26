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

    std::vector<int> result = create_pair_list(list, raw_pair_list);
    show_list(result);
}

std::vector<int>    PmergeMe::create_pair_list(std::vector<int>& list, std::vector<std::pair<int,int> >& raw)
{
    std::vector<int>::iterator it = list.begin();
    std::vector<std::pair<int,int> > pair_list;
    std::vector<int> main;
    int remaining = -1;

    
    while (it != list.end())
    {
        int first;
        int second;
        
        first = *it++;
        if (it == list.end())
        {
            remaining = first;
            break;
        }
        second = *it++;
        pair_list.push_back(std::make_pair(first, second));
    }
    
    if (raw.empty())
        raw = pair_list;
    
    sort_pair_list(pair_list);
    take_max(main ,pair_list);

    if (pair_list.size() <= 1)
    {
        if (remaining != -1)
            main.push_back(remaining);
        return main;
    }

    std::vector<int> sorted_main = create_pair_list(main, raw);

    insert_small_elements(sorted_main, raw, remaining);

    return sorted_main;
}


void    PmergeMe::insert_small_elements(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list, int remaining)
{
    // Créer la suite de Jacobsthal pour l'ordre d'insertion optimal
    std::vector<int> jacobsthal = generate_jacobsthal(pair_list.size());
    std::vector<int> inserted(pair_list.size(), 0);
    
    // Insérer les petits éléments dans l'ordre de Jacobsthal
    for (size_t i = 0; i < jacobsthal.size() && i < pair_list.size(); i++)
    {
        int idx = jacobsthal[i] - 1; // Index 0-based
        if (idx >= 0 && idx < (int)pair_list.size() && !inserted[idx])
        {
            int small = pair_list[idx].first;
            insert_with_binary_search(main, small);
            inserted[idx] = 1;
        }
    }
    
    // Insérer les éléments non encore insérés
    for (size_t i = 0; i < pair_list.size(); i++)
    {
        if (!inserted[i])
        {
            int small = pair_list[i].first;
            insert_with_binary_search(main, small);
        }
    }
    
    // Insérer l'élément restant s'il y en a un
    if (remaining != -1)
        insert_with_binary_search(main, remaining);
}


void    PmergeMe::insert_with_binary_search(std::vector<int>& main, int value)
{
    std::vector<int>::iterator it = std::lower_bound(main.begin(), main.end(), value);
    main.insert(it, value);
}

std::vector<int>    PmergeMe::generate_jacobsthal(size_t size)
{
    std::vector<int> result;
    if (size == 0) return result;
    
    int j0 = 0;
    int j1 = 1;
    
    result.push_back(j1);
    
    while ((size_t)j1 < size)
    {
        int temp = j1;
        j1 = j1 + 2 * j0;
        j0 = temp;
        if ((size_t)j1 <= size)
            result.push_back(j1);
    }
    
    return result;
}


void    PmergeMe::insert_first_little(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list)
{
    main.insert(main.begin(), get_little_from_bigger(pair_list ,main[0]));
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
