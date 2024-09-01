#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << RED << "Error: Argument count." << RESET << std::endl;
		return 1;
	}

	try
	{
		std::vector<int> vec;
		std::deque<int> deq;
		double vecSortTime;
		double deqSortTime;
		int number;

		for (int index = 1; index < ac; index++)
		{
			std::stringstream readstring(av[index]);

			if (!(readstring >> number) || !(readstring.eof()))
				throw std::runtime_error("Error: invalid input");
			
			if (number < 0)
				throw std::runtime_error("Error: Negative number.");
			
			vec.push_back(number);
			deq.push_back(number);
		}

		PmergeMe pMergeMe;

		std::cout << YELLOW << "---------Before---------" << RESET << std::endl;
		pMergeMe.print(vec, deq);
		pMergeMe.calculateTime(vec, deq, vecSortTime, deqSortTime);

		std::cout << std::endl;
		std::cout << YELLOW << "---------After---------" << RESET << std::endl;
		pMergeMe.print(vec, deq);

		std::cout << std::endl << YELLOW << "Time to process a range of " << ac - 1 << " elements with std::vector : " <<  vecSortTime << " us" << RESET << std::endl;
		std::cout << std::endl << GREEN << "Time to process a range of " << ac - 1 << " elements with std::deque : " << deqSortTime << " us" << RESET << std::endl;

	}catch(const std::exception &e)
	{
		std::cerr << RED << e.what() << RESET << "\n";
	}
}