#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "[Usage]: ./RPN [calcul]" << std::endl;
        return 1;
    }

    try
    {
        std::cout << RPN::calculate(av[1]) << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}