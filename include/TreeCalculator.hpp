#pragma once

#include <unordered_map>

#include "./expressionTree/etTypesAndStructs.hpp"

class TreeCalculator {
public:
	TreeCalculator();
	float calculate(etNode*);

private:
	std::unordered_map<char, float (*)(float a, float b)> oper;
	float calculate_node_recursively(etNode* node);

	static float add(float a, float b);
	static float sub(float a, float b);
	static float mul(float a, float b);
	static float div(float a, float b);
};