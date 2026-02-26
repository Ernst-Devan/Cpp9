#include "PmergeMe.hpp"
#include <iostream>
#include <cstdio>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(PmergeMe const& p) { (void)p; }
PmergeMe& PmergeMe::operator=(PmergeMe const& p) { return *this; (void)p; }
PmergeMe::~PmergeMe() {}

bool PmergeMe::is_inside(std::vector<int>& list, int nb)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (list[i] == nb)
            return true;
    }
    return false;
}

void PmergeMe::create_initial_vector(char **nbs, int ac)
{
    std::vector<int> list;

    for(int i = 1; i < ac; i++)
    {
        int tmp;
        if (sscanf(nbs[i], "%d", &tmp) != 1 || tmp < 0)
        {
            std::cerr << "Error" << std::endl;
            return;
        }
        list.push_back(tmp);
    }

    std::vector<int> before = list;

    clock_t start = clock();
    std::vector<int> result = merge_insert_sort(list);
    clock_t end = clock();

    double time_us = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Before: ";
    show_list(before);
    
    std::cout << "After: ";
    show_list(result);
    
    std::cout << std::fixed << std::setprecision(5)
              << "Time to process a range of " << result.size()
              << " elements with std::vector : " << time_us << " us" << std::endl;
}

std::vector<int> PmergeMe::merge_insert_sort(std::vector<int>& list)
{
    if (list.size() <= 1)
        return list;

    std::vector<std::pair<int,int> > pair_list;
    std::vector<int> main;
    int remaining = -1;

    // Créer les paires
    for (size_t i = 0; i + 1 < list.size(); i += 2)
    {
        int first = list[i];
        int second = list[i + 1];
        pair_list.push_back(std::make_pair(first, second));
    }
    
    if (list.size() % 2 == 1)
        remaining = list[list.size() - 1];
    
    // Trier les paires (smaller < larger)
    sort_pair_list(pair_list);
    
    // Extraire les maximums
    take_max(main, pair_list);

    // Cas de base
    if (main.size() <= 1)
    {
        insert_small_elements(main, pair_list, remaining);
        return main;
    }

    // Trier récursivement les maximums
    main = merge_insert_sort(main);

    // Insérer les petits de ce niveau
    insert_small_elements(main, pair_list, remaining);

    return main;
}

std::vector<int> PmergeMe::generate_jacobsthal(std::size_t size)
{
    std::vector<int> result;
    if (size == 0) return result;
    
    int j0 = 0;
    int j1 = 1;
    
    result.push_back(j1);
    
    while ((std::size_t)j1 < size)
    {
        int temp = j1;
        j1 = j1 + 2 * j0;
        j0 = temp;
        if ((std::size_t)j1 <= size)
            result.push_back(j1);
    }
    
    return result;
}

void PmergeMe::insert_small_elements(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list, int remaining)
{
    std::vector<int> jacobsthal = generate_jacobsthal(pair_list.size());
    std::vector<int> inserted(pair_list.size(), 0);
    
    // Insérer selon la suite de Jacobsthal
    for (size_t i = 0; i < jacobsthal.size(); i++)
    {
        int idx = jacobsthal[i] - 1;
        if (idx >= 0 && idx < (int)pair_list.size() && !inserted[idx])
        {
            int small = pair_list[idx].first;
                insert_with_binary_search(main, small);
            inserted[idx] = 1;
        }
    }
    
    // Insérer les éléments restants
    for (size_t i = 0; i < pair_list.size(); i++)
    {
        if (!inserted[i])
        {
            int small = pair_list[i].first;
                insert_with_binary_search(main, small);
        }
    }
    
    // Insérer l'élément solitaire
    if (remaining != -1)
        insert_with_binary_search(main, remaining);
}

void PmergeMe::insert_with_binary_search(std::vector<int>& main, int value)
{
    std::vector<int>::iterator it = std::lower_bound(main.begin(), main.end(), value);
    main.insert(it, value);
}

void PmergeMe::take_max(std::vector<int>& main, std::vector<std::pair<int,int> >& pair_list)
{
    for (size_t i = 0; i < pair_list.size(); i++)
    {
        main.push_back(pair_list[i].second);
    }
}

void PmergeMe::show_list(std::vector<int>& list)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        std::cout << list[i];
        if (i + 1 < list.size())
            std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sort_pair_list(std::vector<std::pair<int,int> >& pair_list)
{
    for (size_t i = 0; i < pair_list.size(); i++)
    {
        if (pair_list[i].first > pair_list[i].second)
            std::swap(pair_list[i].first, pair_list[i].second);
    }    
}