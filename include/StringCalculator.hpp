#include <string>

#include "./expressionParser/ExpressionParser.hpp"
#include "./expressionTree/ExpressionTree.hpp"
#include "./TreeCalculator.hpp"


class StringCalculator {
public:
	StringCalculator();
	~StringCalculator();
	float calculate(std::string expression);

private:
	ExpressionParser* ep;
	ExpressionTree* et;
	TreeCalculator* tc;
};