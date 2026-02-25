#include "RPN.hpp"


unsigned int RPN::calculate(char *l)
{
    std::stack<int> pile;
    std::string line(l);

    for (unsigned int i = 0; i < line.size(); i++)
    {
        if (isdigit(line[i]))
            pile.push(line[i] - '0');

        else if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') && pile.size() > 1)
        {
            int second = pile.top();
            pile.pop();
            int first = pile.top(); 
            pile.pop();

            if (line[i] == '+')
                pile.push(first + second);
            if (line[i] == '-')
                pile.push(first - second);
            if (line[i] == '*')
                pile.push(first * second);
            if (line[i] == '/')
            {
                if (second == 0)
                    throw std::invalid_argument("Division by 0");
                pile.push(first / second);
            }
        }
        else if (line[i] != ' ')
            throw std::invalid_argument("Error inside the line");
    }
    if (pile.size() != 1)
        throw std::invalid_argument("Error inside the line");
    return pile.top();
}