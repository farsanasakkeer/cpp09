#ifndef RPN_HPP
#define RPN_HPP

# define RESET			"\033[0m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define PURPLE			"\033[35m"
# define CYAN           "\033[36m"

#include <iostream>
#include <sstream>
#include <stack>
#include <cstdlib>
#include <climits>

class RPN
{
	private:
		std::stack<int> operandStack;
		int performOperation(int operand1, int operand2, const std::string &op);

	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		int evaluateExpression(const std::string &expr);
		int printResult(std::ostream &out);
};



#endif