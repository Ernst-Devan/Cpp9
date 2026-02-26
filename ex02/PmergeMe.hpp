#ifndef PmergeMe_HPP
#define PmergeMe_HPP

#include <utility>
#include <vector>

class PmergeMe
{
    private:
        PmergeMe();
        PmergeMe(PmergeMe const& p);
        PmergeMe& operator=(PmergeMe const& p);
        ~PmergeMe();

        static  std::vector<int> create_pair_list(std::vector<int>& list, std::vector<std::pair<int,int> >& raw);
        static  void sort_pair_list(std::vector<std::pair<int, int> >& pair_list);
        static  void take_max(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list);
        static  void insert_small_elements(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list, int remaining);
        static  void insert_with_binary_search(std::vector<int>& main, int value);
        static  std::vector<int> generate_jacobsthal(std::size_t size);

    public:
        static  void create_initial_vector(char **nbs, int ac);
        static  void show_each_pair(std::vector<std::pair<int,int> >& pair_list);
        static  void show_list(std::vector<int>& list);
        static  void insert_first_little(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list);
        static  int  get_little_from_bigger(std::vector<std::pair<int, int> >& pair_list, int bigger);
};

#endif