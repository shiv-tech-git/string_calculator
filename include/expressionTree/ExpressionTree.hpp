#pragma once

#include <vector>
#include <unordered_map>

#include "./etTypesAndStructs.hpp"
#include "../expressionParser/epTypesAndStructs.hpp"


class ExpressionTree {
public:
	ExpressionTree();
	~ExpressionTree();
	etNode* create(std::vector<token_t>& tokens);

private:
	std::unordered_map<char, int> operator_precedences;
	const int max_precedences;
	etNode* root;

	etNode* build_recursively(std::vector<token_t>& tokens, size_t begin, size_t end);
	int get_operator_precedence(char oper);
	int get_min_precedence_operator_index(std::vector<token_t>& tokens, size_t begin, size_t end);
	void delete_recursively(etNode* node);
};