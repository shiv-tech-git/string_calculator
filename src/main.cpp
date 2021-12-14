#include <iostream>
#include <sstream>
#include <iomanip>

#include "../include/StringCalculator.hpp"
#include "../include/exceptions/InvalidTokenException.hpp"

int main()
{
    std::string expression;
	float result;
	while(1) {
		std::cout << "expression:  ";
		std::getline(std::cin, expression);
		StringCalculator calc;
		try {
			result = calc.calculate(expression);
		}
		catch (InvalidTokenException ex) {
			continue;
		}
		std::cout << "result: " << std::setprecision(2) << std::setfill('0')<< result << std::endl << std::endl;
	}
}
