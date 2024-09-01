#ifndef PMERGEME_HPP
#define PMERGEME_HPP

# define RESET			"\033[0m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define PURPLE			"\033[35m"
# define CYAN           "\033[36m"

#include <iostream>
#include <ctime>
#include <sstream>
#include <cstddef>
#include <algorithm>
#include <deque>
#include <vector>

class PmergeMe
{
	public:
		
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		//Vector sort functions

		void mergeInsertSortVector(std::vector<int> &container, int start, int end);
		void mergeSortVector(std::vector<int> &container, int start, int mid, int end);
		void insertSortVector(std::vector<int> &container, int start, int end);

		//Deque sort functions
		
		void mergeInsertSortDeque(std::deque<int> &container, int start, int end);
		void mergeSortDeque(std::deque<int> &container, int start, int mid, int end);
		void insertSortDeque(std::deque<int> &container, int start, int end);

		void runVector(std::vector<int> &container);
		void runDeque(std::deque<int> &container);

		void calculateTime(std::vector<int> &vector, std::deque<int> &deque, double &vecTime, double &deqTime);
		void print(std::vector<int> &vec, std::deque<int> &deq);
		int midPoint(int start, int end);
		
};

#endif