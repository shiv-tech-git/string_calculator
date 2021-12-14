#include <cctype>
#include <iostream>

#include "include/expressionParser/ExpressionParser.hpp"
#include "include/exceptions/InvalidTokenException.hpp"

//big ugly function_1
std::vector<std::string> ExpressionParser::split_string(std::string expression) {
	std::vector<std::string> result;
	size_t end = 0;
	size_t begin = 0;
	
	while (end < expression.size()) {

		//skip spaces
		if (expression[end] == ' ') {
			end++;
			begin = end;
		}
		//syntax sugar 9(5 + 4) => 9 * (5 + 4)
		else if (expression[end] == '(' && result.size() > 0 && isdigit(result.back()[result.back().size() - 1])) {
			result.push_back("*");
			result.push_back("(");
			end++;
			begin = end;
		}
		//parantheses
		else if (expression[end] == '(' || expression[end] == ')') {
			end++;
			result.push_back(expression.substr(begin, end - begin));
			begin = end;
		}
		//numbers (start from digit, or from minus if there is no ')' before and next char is digit or this is first token but not if this is the last one) Yes, this is disgusting. Shame on me
		else if (isdigit(expression[end]) || (expression[end] == '-' && (end > 0 && result.back()[result.back().size()- 1] != ')') && isdigit(expression[end + 1]) && (result.size() == 0 || !isdigit(result.back()[result.back().size()- 1]))) ) {
			do {
				end++;
				if (expression[end] == ',')
					expression[end] = '.';

				if (expression[end] == '.' && (end == (expression.size() - 1) || !isdigit(expression[end + 1]))) {
					std::cout << "Invalid input:" <<std::endl;
					print_expression_position(expression, end);
					throw InvalidTokenException();
				}
			} while ((isdigit(expression[end]) || expression[end] == '.') && end < expression.size());
			result.push_back(expression.substr(begin, end - begin));
			begin = end;
		}
		//operators
		else if (expression[end] == '-' || expression[end] == '+' || expression[end] == '*' || expression[end] == '/') {
			end++;
			result.push_back(expression.substr(begin, end - begin));
			begin = end;
		} else {
			std::cout << "Invalid input:" <<std::endl;
			print_expression_position(expression, end);
			throw InvalidTokenException();
		}

	}

	if (begin != end) {
		result.push_back(expression.substr(begin, begin - end));
	}
	return result;
}

token_t ExpressionParser::create_token_from_char(char c) {
	switch (c) {
		case '(':
			return token_t{ TokenType::l_par_tok };
		case ')':
			return token_t{ TokenType::r_par_tok };
		case '+':
		case '-':
		case '/':
		case '*':
			token_t tmp;
			tmp.type = TokenType::oper_tok;
			tmp.oper = static_cast<oper_t>(c);
			return tmp;
	}
}

token_t ExpressionParser::create_token_from_string(std::string s) {
	int sign = 1;
	if (s[0] == '-') {
		sign = -1;
		s = s.substr(1, s.size() - 1);
	}
	float num = sign * std::stof(s);
	token_t token{ TokenType::num_tok };
	token.num = num;
	return token;
}

token_t ExpressionParser::handle_raw_token(std::string s) {
	if (s.size() == 1 && !isdigit(s[0])) {
		return create_token_from_char(s[0]);
	} else {
		return create_token_from_string(s);
	}
}

void ExpressionParser::print_expression_position(std::string expression, size_t pos) {
	std::cout << '\t' << expression << std::endl;
	std::cout << '\t' << std::string(pos, ' ') << "^" << std::endl;
}

//big ugly function_2
void ExpressionParser::validate_parentheses(std::string expression) {	
	size_t begin = 0;
	size_t end = expression.size() - 1;
	int from_begin = 0;
	int from_end = 0;
	
	while (begin <= end) {
		//going from begin to end
		while(begin <= end) {
			if (expression[begin] == '(') {
				from_begin++;
				break;
			} else if (expression[begin] == ')') {
				if (from_begin == 0) {
					std::cout << "Unmatched parenthese:" << std::endl;
					print_expression_position(expression, begin);
					throw InvalidTokenException();
				} else {
					from_begin--;
					begin++;
					break;
				}
			} else {
				begin++;
			}
		}
		//going from end to begin
		while(begin <= end) {
			if (expression[end] == ')') {
				from_end++;
				break;
			} else if (expression[end] == '(') {
				if (from_end == 0) {
					std::cout << "Unmatched parenthese:" << std::endl;
					print_expression_position(expression, end);
					throw InvalidTokenException();
				} else {
					from_end--;
					end--;
					break;
				}
			} else {
				end--;
			}
		}
		begin++;
		end--;
	}
	if (from_begin != from_end) {
		std::cout << "Unmatched parenthese:" << std::endl;
		print_expression_position(expression, begin - 1);
		throw InvalidTokenException();
	}
}

std::vector<token_t> ExpressionParser::parse_string_to_tokens(std::string expression) {
	std::vector<token_t> result;
	validate_parentheses(expression);
	std::vector<std::string> raw_tokens = split_string(expression);

	token_t token;
	for (size_t i = 0; i < raw_tokens.size(); i++) {
		token = handle_raw_token(raw_tokens[i]);
		result.push_back(token);
	}

	return result;
}


