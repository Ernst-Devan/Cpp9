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
        static  void pair_sort();
        static  void make_pair();
        static  void sort_pair_list(std::vector<std::pair<int, int> >& pair_list);
        static  void take_max(std::vector<int>& main, std::vector<std::pair<int, int> >& pair_list);

    public:
        static  void create_initial_vector(char **nbs, int ac);
        static  void show_each_pair(std::vector<std::pair<int,int> >& pair_list);
        static  void show_list(std::vector<int>& list);
        static  std::vector<std::pair<int, int> > reorder_pair_list(std::vector<int>& max_list, std::vector<std::pair<int, int> >& pair_list);
        static  void insert_first_little(std::vector<int>& main,  std::vector<std::pair<int, int> >& pair_list);
        static  int  get_little_from_bigger(std::vector<std::pair<int, int> >& pair_list, int bigger);
    };

#endif