#include "PmergeMe.hpp"
#include <iostream>


int main(int ac, char **av)
{
    if (ac < 3)
    {
        std::cerr << "Correct usage: ./PmergeMe [nb] [nb] [nb].." << std::endl;
        return 1;
    }
    try
    {
        PmergeMe::create_initial_vector(av, ac);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
