#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN
{
    private:
        RPN();
        RPN(RPN const&);
        ~RPN();
        RPN& operator=(RPN const&);

    public:
        static unsigned int calculate(char *l);
};

#endif
