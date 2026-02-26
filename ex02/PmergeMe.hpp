#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

class PmergeMe
{
    private:
        PmergeMe();
        PmergeMe(PmergeMe const& p);
        PmergeMe& operator=(PmergeMe const& p);
        ~PmergeMe();

        static std::vector<int> merge_insert_sort(std::vector<int>& list);
        static void sort_pair_list(std::vector<std::pair<int, int> >& pair_list);
        static void take_max(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list);
        static void insert_small_elements(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list, int remaining);
        static void insert_with_binary_search(std::vector<int>& main, int value);
        static std::vector<int> generate_jacobsthal(std::size_t size);
        static bool is_inside(std::vector<int>& list, int nb);


    public:
        static void create_initial_vector(char **nbs, int ac);
        static void show_list(std::vector<int>& list);
};

#endif