#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Correct usage: ./btc [file.txt]" << std::endl;
        return 1;
    }

    try 
    {
        BitcoinExchange program;
        
        program.add_wallet(av[1]);
    }
    catch (std::exception &e) 
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}
