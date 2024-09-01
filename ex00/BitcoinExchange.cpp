#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other): database(other.database){}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->database = other.database;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::initializeDatabase()
{
    std::ifstream dataFile("data.csv");//to read data from files
    std::string line;

    if (!dataFile.is_open())
        throw std::runtime_error("Error: could not open database file.");
    
    if (dataFile.peek() == std::ifstream::traits_type::eof())
		throw std::runtime_error("Error: database file is empty.");
	
	if (std::getline(dataFile, line) && line != "date,exchange_rate")
		throw std::runtime_error("Error: invalid header in database.");

    while (std::getline(dataFile, line))
	{
		if (line.empty())
			throw std::runtime_error("Error: line in the database is empty.");
		
		if (line.find_first_not_of("0123456789-,. ") != std::string::npos)
			throw std::runtime_error("Error: invalid line in database file => " + line);
		
		size_t delimiterPosition = line.find(",");

		if (delimiterPosition == std::string::npos || std::count(line.begin(), line.end(),',') != 1 || 
		line[0] == ',' || line[0] == '-' || line[line.length() - 1] == ',' || line[line.length() - 1] == '-')
			throw std::runtime_error("Error: invalid line in the database file => " + line);
		
		std::string date = line.substr(0, delimiterPosition);
		std::string rate = line.substr(delimiterPosition + 1);

		database.insert(std::make_pair(date, atof(rate.c_str())));
	}
}

void BitcoinExchange::trim(std::string &str)
{
    std::string::iterator it = str.begin();

	while (it != str.end() && std::isspace(*it))
		++it;
	str.erase(str.begin(), it);

	std::string::reverse_iterator rit = str.rbegin();

	while (rit != str.rend() && std::isspace(*rit))
		++rit;
	
	str.erase(rit.base(), str.end());
}

bool BitcoinExchange::validateDate(std::string &date)
{
	if (date.find_first_not_of("0123456789-") != std::string::npos || std::count(date.begin(), date.end(), '-') != 2)
	{
		std::cerr << RED << "Error: bad input => " << date << RESET << std::endl;
		return false;
	}

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		std::cerr << RED << "Error: bad input => " << date << RESET << std::endl;
		return false;
	}

	std::string year = date.substr(0, 4);
	std::string month = date.substr(5, 2);
	std::string day = date.substr(8, 2);

	int yearValue = std::atoi(year.c_str());
	if(yearValue < 2009 || yearValue > 2022)
	{
		std::cerr << RED << "Error: bad input => " << date << RESET << std::endl;
		return false;
	}

	int monthValue = std::atoi(month.c_str());
	if (monthValue < 1 || monthValue > 12)
	{
		std::cerr << RED << "Error: bad input => " << date << RESET << std::endl;
		return false;
	}

	int dayValue = std::atoi(day.c_str());
	if (dayValue < 1 || dayValue > 31 || 
	(monthValue == 2 && dayValue > 28) || (monthValue == 4 && dayValue > 30) ||
	(monthValue == 6 && dayValue > 30) || (monthValue == 9 && dayValue > 30) ||
	(monthValue == 11 && dayValue > 30))
	{
		std::cerr << RED << "Error: bad input => " << date << RESET << std::endl;
		return false;
	}

	return true;
}

bool BitcoinExchange::validateRate(std::string &rate, bool inputControl)
{
	if (rate.find_first_not_of("0123456789-.") != std::string::npos)
	{
		std::cerr << RED << "Error: bad input => " << rate << RESET << std::endl;
		return false;
	}

	size_t dotCount = std::count(rate.begin(), rate.end(), '.');

	if (dotCount > 1 || (dotCount == 1 && (rate[0] == '.' || rate[rate.length() - 1] == '.')))
	{
		std::cerr << RED << "Error: bad input => " << rate << RESET << std::endl;
		return false;
	}

	size_t minusCount = std::count(rate.begin(), rate.end(), '-');

	if (minusCount > 1 || (minusCount == 1 && (rate[0] != '-')))
	{
		std::cerr << RED << "Error: bad input => " << rate << RESET << std::endl;
		return false;
	}

	double rateValue = atof(rate.c_str());

	if (rateValue < 0)
	{
		std::cerr << RED << "Error: not a positive number." << RESET << std::endl;
		return false;
	}

	if (inputControl && rateValue > 1000)
	{
		std::cerr << RED << "Error: too large a number." << RESET << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::handleInputFile(std::string &input)
{
    std::ifstream inputFile(input.c_str());
	std::string line;

	if (!inputFile.is_open())
		throw std::runtime_error("Error: could not open input file.");
	
	if (inputFile.peek() == std::ifstream::traits_type::eof())
		std::cerr << RED << "Error: input file is empty." << RESET << std::endl;
	
	if (std::getline(inputFile, line) && line != "date | value")
		std::cerr << RED << "Error: invalid header in the input file." << RESET << std::endl;
	
	while (std::getline(inputFile, line))
	{
		if(line.empty())
		{
			std::cerr << RED << "Error: empty line in the input file." << RESET << std::endl;
			continue;
		}

		size_t pipePosition = line.find('|');
		if (pipePosition == std::string::npos || std::count(line.begin(), line.end(), '|') != 1 ||
		line[0] == '|' || line[0] == '-' || line[line.length() - 1] == '|' || line[line.length() - 1] == '-')
		{
			std::cerr << RED << "Error: bad input => " << line << RESET << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipePosition);
		std::string rate = line.substr(pipePosition + 1);

        trim(date);
		trim(rate);

        if(validateDate(date) == false)
			continue;
		
		if(validateRate(rate, true) == false)
			continue;

		std::map<std::string, double>::iterator it = database.lower_bound(date);

		if (it->first != date)
			it--;
		
		double exchange = std::atof(rate.c_str()) * it->second;
		std::cout << GREEN << date << " => " << rate << " = " << exchange << RESET << std::endl;

    }

}