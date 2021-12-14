#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "../include/expressionTree/ExpressionTree.hpp"
#include "../include/exceptions/InvalidTokenException.hpp"

ExpressionTree::ExpressionTree(): max_precedences(2), root(nullptr) {
	operator_precedences['-'] = 1;
	operator_precedences['+'] = 1;
	operator_precedences['*'] = 2;
	operator_precedences['/'] = 2;
}

ExpressionTree::~ExpressionTree() {
	delete_recursively(root);
}

void ExpressionTree::delete_recursively(etNode* node) {
	if (!node) {
		return;
	}
	delete_recursively(node->left);
	delete_recursively(node->right);
	delete node;
}

int ExpressionTree::get_min_precedence_operator_index(std::vector<token_t>& tokens, size_t begin, size_t end) {
	int min_precedence = max_precedences * 2;
	int precedence_offset = 0;
	size_t min_precedence_oper_index = 0;
	for (size_t i = begin; i <= end; i++) {
		if (tokens[i].type == TokenType::l_par_tok)
			precedence_offset += max_precedences;
		if (tokens[i].type == TokenType::r_par_tok)
			precedence_offset -= max_precedences;
		if (tokens[i].type == TokenType::oper_tok) {
			int oper_precedence = operator_precedences[tokens[i].oper] + precedence_offset;
			if (oper_precedence <= min_precedence) {
				min_precedence = oper_precedence;
				min_precedence_oper_index = i;
			}
		}
	}
	return min_precedence_oper_index;
}

void print_expression_position(std::vector<token_t>& tokens, size_t err_i) {
	std::string expression;
	size_t begin = 0;
	size_t end = 0;
	
	for (size_t i = 0; i < tokens.size(); i++) {
		if (tokens[i].type == TokenType::l_par_tok) {
			expression += "(";
		} else if (tokens[i].type == TokenType::r_par_tok) {
			expression += ")";	
		} else if (tokens[i].type == TokenType::oper_tok) {
			expression += tokens[i].oper;	
		} else if (tokens[i].type == TokenType::num_tok) {
			std::stringstream sstream;
			sstream << std::setprecision(2) << tokens[i].num;
			expression += sstream.str();
		}
		expression += " ";
		if (i == (err_i - 1))
			begin = expression.size();
		if (i >= (err_i) && end == 0 && (tokens[i].type == TokenType::r_par_tok))
			end = expression.size();
	}
	std::cout << '\t' << expression << std::endl;
	std::cout << '\t' << std::string(begin - 1, ' ') << std::string(end - begin, '^')<< std::endl;
}

etNode* ExpressionTree::build_recursively(std::vector<token_t>& tokens, size_t begin, size_t end) {
	if (tokens[begin].type == TokenType::l_par_tok && tokens[end].type == TokenType::r_par_tok) {
		begin++;
		end--;
	}
	if ((end - begin) == 1) {
		std::cout << "Logic error:" << std::endl;
		print_expression_position(tokens, begin);
		throw InvalidTokenException(); //memory leak?
	}
	etNode* node = new etNode;
	if (begin == end) {
		node->type = EtNodeType::num_node;
		node->num = tokens[begin].num;
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}
	size_t min_precedence_oper_index = get_min_precedence_operator_index(tokens, begin, end);
	node->type = EtNodeType::oper_node;
	node->oper = tokens[min_precedence_oper_index].oper;
	node->left = build_recursively(tokens, begin, min_precedence_oper_index - 1);
	node->right = build_recursively(tokens, min_precedence_oper_index + 1, end);
	return node;
}


etNode* ExpressionTree::create(std::vector<token_t>& tokens) {
	delete_recursively(root);
	root = build_recursively(tokens, 0, tokens.size() - 1);
	return root;
}

int ExpressionTree::get_operator_precedence(char oper) {
	return operator_precedences[oper];
}