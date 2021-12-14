#include <gtest/gtest.h>

#include "../include/StringCalculator.hpp"
#include "../include/exceptions/InvalidTokenException.hpp"
 
TEST(TestExpression1, Valid) {
	std::string expression = "-1 + 5 - 3";
	StringCalculator calc;
	float result = 0;
	bool exception = 0;
	try {
		result = calc.calculate(expression);
	}
	catch (InvalidTokenException ex) {
		exception = true;
	}
    ASSERT_EQ(result, 1);
    ASSERT_EQ(exception, 0);
}

TEST(TestExpression2, Valid) {
	std::string expression = "-10+ (8*2.5)-(3/1,5)";
	StringCalculator calc;
	float result = 0;
	bool exception = 0;
	try {
		result = calc.calculate(expression);
	}
	catch (InvalidTokenException ex) {
		exception = true;
	}
    ASSERT_EQ(result, 8);
    ASSERT_EQ(exception, 0);
}

TEST(TestExpression3, Valid) {
	std::string expression = "1 +(2*(2.5+2.5+(3-2)))-(3/1.5)";
	StringCalculator calc;
	float result = 0;
	bool exception = 0;
	try {
		result = calc.calculate(expression);
	}
	catch (InvalidTokenException ex) {
		exception = true;
	}
    ASSERT_EQ(result, 11);
    ASSERT_EQ(exception, 0);
}

TEST(TestExpression4, Invalid) {
	std::string expression = "1.1 + 2.1 + abc";
	StringCalculator calc;
	float result = 0;
	bool exception = 0;
	try {
		result = calc.calculate(expression);
	}
	catch (InvalidTokenException ex) {
		exception = true;
	}
    ASSERT_EQ(exception, 1);
}

TEST(TestExpression5, Invalid) {
	std::string expression = "1 +(2*(2.5+2.5+(3-2))-(3/1.5)";
	StringCalculator calc;
	float result = 0;
	bool exception = 0;
	try {
		result = calc.calculate(expression);
	}
	catch (InvalidTokenException ex) {
		exception = true;
	}
    ASSERT_EQ(exception, 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}