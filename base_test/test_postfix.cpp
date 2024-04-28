#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <stack>
#include "StackAndPostfix.h"

// ���� ��� ���������� ��������� � ����� �������
TEST(PostfixCalculatorTest, Evaluate_TwoNumbers) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "5 3 +";
	Polynomial expected("8");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� ���������� ��������� � �������������� ���������� �� �������
TEST(PostfixCalculatorTest, Evaluate_WithVariableFromTable) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	// ��������� ������� "2x" � �������
	tableManager.addPolynomialToAllTables("2x", Polynomial("2x"));

	std::string postfixExpression = "3 2x *";
	Polynomial expected("6x");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� �������� ������� ��������� (��������� ����������)
TEST(PostfixCalculatorTest, Division_NotImplemented) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	// ��������� �������� � �������
	tableManager.addPolynomialToAllTables("x", Polynomial("x"));
	tableManager.addPolynomialToAllTables("x^2", Polynomial("x^2"));

	std::string postfixExpression = "x x^2 /";

	EXPECT_THROW(calculator.evaluate(postfixExpression), std::runtime_error);
}

// ���� ��� �������� ���������� ��������� � ������������� ������
TEST(PostfixCalculatorTest, Evaluate_NegativeNumber) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "-5";
	Polynomial expected("-5");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� �������� ���������� ��������� � ���������� "-"
TEST(PostfixCalculatorTest, Evaluate_Subtraction) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "10 7 -";
	Polynomial expected("3");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� �������� ���������� ��������� � ���������� "*"
TEST(PostfixCalculatorTest, Evaluate_Multiplication) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "10 3 *";
	Polynomial expected("30");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� �������� ���������� ��������� � ���������� �� ������� � ������
TEST(PostfixCalculatorTest, Evaluate_VariableAndNumber) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	// ��������� ������� "2x" � �������
	tableManager.addPolynomialToAllTables("2x", Polynomial("2x"));

	std::string postfixExpression = "2 2x *";
	Polynomial expected("4x");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� �������� ���������� �������� ���������
TEST(PostfixCalculatorTest, Evaluate_ComplexExpression) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "2 3 + 5 *";
	Polynomial expected("25");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// ���� ��� �������� ���������� ��������� � ������� ����������� ��������
TEST(PostfixCalculatorTest, Evaluate_LargeExpression) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "2 3 * 5 6 + -";
	Polynomial expected("-5");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

