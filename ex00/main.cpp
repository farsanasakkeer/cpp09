#include "BitcoinExchange.hpp"

int main(int ac, char **argv)
{
    if(ac != 2)
    {
        std::cerr << RED << "Error: Missing file name." << RESET << std::endl;
		return 1;
    }
    
    BitcoinExchange btc;

	try
	{
		btc.initializeDatabase();
		std::string input(argv[1]);
		btc.handleInputFile(input);
	}
	catch(const std::exception& e)
	{
		std::cerr << RED << e.what() << RESET << '\n';
	}

	return 0;    
}