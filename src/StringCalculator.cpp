#include "include/StringCalculator.hpp"

StringCalculator::StringCalculator() {
	ep = new ExpressionParser();
	et = new ExpressionTree();
	tc = new TreeCalculator();
}

StringCalculator::~StringCalculator() {
	delete ep;
	delete et;
	delete tc;
}

float StringCalculator::calculate(std::string expression) {
    std::vector<token_t> tokens = ep->parse_string_to_tokens(expression);
    etNode* root = et->create(tokens);
    return tc->calculate(root);
}