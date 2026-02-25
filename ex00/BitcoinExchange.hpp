#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <ctime>

typedef struct s_parse
{
    std::string date;
    std::string value;
    std::string separator;
} t_parse;

class BitcoinExchange
{
    private:
        std::map<time_t, float> requests;
        t_parse                 parse;

        void            adding_data(std::string& line, std::string separator);
        void            parse_data_base();
        int             parse_wallet(std::ifstream& file);
        unsigned int    get_line(std::string line);
        unsigned int    check_validity();
        unsigned int    value_of_wallet();
        float           get_value_date(time_t timestamp);
        float           analyse_price(float value, float wallet);
        void            display_price(float value);
        float           get_value_previous_date(time_t timestamp);
        unsigned int    check_number_day();

    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const& b);
        BitcoinExchange& operator=(BitcoinExchange const& b);
        ~BitcoinExchange();

        void    add_wallet(char *name);
};

#endif
