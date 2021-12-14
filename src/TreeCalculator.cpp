#include "include/TreeCalculator.hpp"

TreeCalculator::TreeCalculator() {
	oper['+'] = add;
	oper['-'] = sub;
	oper['*'] = mul;
	oper['/'] = div;
}

float TreeCalculator::calculate(etNode* node) {
	return calculate_node_recursively(node);
}

float TreeCalculator::calculate_node_recursively(etNode* node) {
	if (node->type == EtNodeType::num_node) {
		return node->num;
	}
	return oper[node->oper](calculate_node_recursively(node->left), calculate_node_recursively(node->right));
}


float TreeCalculator::add(float a, float b) {
	return a + b;
}

float TreeCalculator::sub(float a, float b) {
	return a - b;
}

float TreeCalculator::mul(float a, float b) {
	return a * b;
}

float TreeCalculator::div(float a, float b) {
	return a / b;
}