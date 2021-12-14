#pragma once

#include <vector>
#include <string>

#include "./epTypesAndStructs.hpp"

class ExpressionParser {
public: 
	std::vector<token_t> parse_string_to_tokens(std::string expression);

private:
	std::vector<std::string> split_string(std::string expression);
	token_t create_token_from_char(char c);
	token_t create_token_from_string(std::string s);
	token_t handle_raw_token(std::string s);
	void print_expression_position(std::string expression, size_t pos);
	void validate_parentheses(std::string expression);
};
