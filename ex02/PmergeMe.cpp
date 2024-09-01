#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	(void)other;
	return (*this);
}

PmergeMe::~PmergeMe(){}

void PmergeMe::mergeInsertSortVector(std::vector<int> &container, int start, int end)
{
	if (start < end)
	{
		if ((end - start) < 10)
			insertSortVector(container, start, end);
		else
		{
			int newEnd = start + (end - start) / 2;
			mergeInsertSortVector(container, start, newEnd);
			mergeInsertSortVector(container, newEnd + 1, end);
			mergeSortVector(container, start, newEnd, end);
		}
	}
}

void PmergeMe::mergeSortVector(std::vector<int> &container, int start, int mid, int end)
{
	int i, j, k;

	std::vector<int> left(mid - start + 1);
	std::vector<int> right(end - mid);

	for (i = 0; i < (mid - start + 1); ++i)
		left[i] = container[start + i];
	for (j = 0; j < (end - mid); ++j)
		right[j] = container[mid + 1 + j];
	
	i = 0;
	j = 0;
	k = start;
	while (i < (mid - start + 1) && j < (end - mid))
	{
		if (left[i] <= right[j])
			container[k++] = left[i++];
		else
			container[k++] = right[j++];
	}

	while (i < (mid - start + 1))
		container[k++] = left[i++];
	while (j < (end - mid))
		container[k++] = right[j++];

}

void PmergeMe::insertSortVector(std::vector<int> &container, int start, int end)
{
	for (int index = start; index <= end; index++)
	{
		int hold = container[index];
		int j = index - 1;
		for (; j >=start && container[j] > hold; --j)
			container[j + 1] = container[j];
		container[j + 1] = hold;
	}
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &container, int start, int end)
{
	if (start < end)
	{
		if ((end - start) < 10)
			insertSortDeque(container, start, end);
		else
		{
			int newEnd = start + (end - start) / 2;
			mergeInsertSortDeque(container, start, newEnd);
			mergeInsertSortDeque(container, newEnd + 1, end);
			mergeSortDeque(container, start, newEnd, end);
		}
	}
}

void PmergeMe::mergeSortDeque(std::deque<int> &container, int start, int mid, int end)
{
	int i, j, k = 0;

	std::deque<int> left(mid - start + 1);
	std::deque<int> right(end - mid);

	for (i = 0; i < (mid - start + 1); ++i)
		left[i] = container[start + i];
	for (j = 0; j < (end - mid); ++j)
		right[j] = container[mid + 1 + j];
	
	i = 0;
	j = 0;
	k = start;

	while (i < (mid - start + 1) && j < (end - mid))
	{
		if (left[i] <= right[j])
			container[k++] = left[i++];
		else
			container[k++] = right[j++];
	}

	while (i < (mid - start + 1))
		container[k++] = left[i++];
	while (j < (end - mid))
		container[k++] = right[j++];

}

void PmergeMe::insertSortDeque(std::deque<int> &container, int start, int end)
{
	for (int index = start; index <= end; index++)
	{
		int hold = container[index];
		int j = index - 1;
		for (; j >= start && container[j] > hold; --j)
			container[j + 1] = container[j];
		container[j + 1] = hold;
	}
}

void PmergeMe::runVector(std::vector<int> &container)
{
	mergeInsertSortVector(container, 0, container.size() - 1);
}

void PmergeMe::runDeque(std::deque<int> &container)
{
	mergeInsertSortDeque(container, 0, container.size() - 1);
}

void PmergeMe::calculateTime(std::vector<int> &vector, std::deque<int> &deque, double &vecTime, double &deqTime)
{
	std::clock_t start = std::clock();
	runVector(vector);
	std::clock_t end = std::clock();
	double elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC) * 100.0;
	vecTime = elapsed;

	start = std::clock();
	runDeque(deque);
	end = std::clock();
	elapsed = static_cast<double>(end - start) / (CLOCKS_PER_SEC) * 100.0;
	deqTime = elapsed;

}

void PmergeMe::print(std::vector<int> &vec, std::deque<int> &deq)
{
	std::cout << GREEN << "Vector : ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << RESET << std::endl;

	

	std::cout << GREEN << "Deque  : ";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		std::cout << *it << " ";
	std::cout << RESET << std::endl;
}

int PmergeMe::midPoint(int start, int end)
{
	return (start + (end - start) / 2);
}