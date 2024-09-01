#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

# define RESET			"\033[0m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define PURPLE			"\033[35m"
# define CYAN           "\033[36m"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, double> database;
        void trim(std::string &str);
		bool validateDate(std::string &date);
		bool validateRate(std::string &rate, bool inputControl);        

    public:
        BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void initializeDatabase();
		void handleInputFile(std::string &input);
};



#endif