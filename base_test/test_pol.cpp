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

// ���� ��� ������������ PolynomialTerm
TEST(PolynomialTermTest, Constructor) {
	PolynomialTerm term(2.5, 3, 2, 1);
	EXPECT_EQ(term.coefficient, 2.5);
	EXPECT_EQ(term.x_exp, 3);
	EXPECT_EQ(term.y_exp, 2);
	EXPECT_EQ(term.z_exp, 1);
}

// ���� ��� ��������� ��������� "<"
TEST(PolynomialTermTest, LessThanOperator) {
	PolynomialTerm term1(2.5, 3, 2, 1);
	PolynomialTerm term2(2.5, 3, 3, 1);
	EXPECT_TRUE(term1 < term2);
}

// ���� ��� ��������� ��������� ">"
TEST(PolynomialTermTest, GreaterThanOperator) {
	PolynomialTerm term1(2.5, 3, 2, 1);
	PolynomialTerm term2(2.5, 3, 1, 1);
	EXPECT_TRUE(term1 > term2);
}

// ���� ��� ��������� ��������� "<="
TEST(PolynomialTermTest, LessThanOrEqualOperator) {
	PolynomialTerm term1(2.5, 3, 2, 1);
	PolynomialTerm term2(2.5, 3, 2, 1);
	EXPECT_TRUE(term1 <= term2);
}

// ���� ��� ��������� ��������� ">="
TEST(PolynomialTermTest, GreaterThanOrEqualOperator) {
	PolynomialTerm term1(2.5, 3, 2, 1);
	PolynomialTerm term2(2.5, 3, 1, 1);
	EXPECT_TRUE(term1 >= term2);
}

// ���� ��� ��������� ��������� "=="
TEST(PolynomialTermTest, EqualOperator) {
	PolynomialTerm term1(2.5, 3, 2, 1);
	PolynomialTerm term2(2.5, 3, 2, 1);
	EXPECT_TRUE(term1 == term2);
}

// ���� ��� ��������� ��������� "!="
TEST(PolynomialTermTest, NotEqualOperator) {
	PolynomialTerm term1(2.5, 3, 2, 1);
	PolynomialTerm term2(2.5, 3, 1, 1);
	EXPECT_TRUE(term1 != term2);
}

// ������������ ������������ �� ���������
TEST(PolynomialTest, DefaultConstructor) {
	Polynomial poly;
	EXPECT_EQ(poly.toString(), "0");
}

// ������������ ������������ � ���������� ������
TEST(PolynomialTest, StringConstructor) {
	Polynomial poly("2x^3 + 3y^2 - 4z^1 + 5");

	EXPECT_EQ(poly.toString(), "2x^3 + 3y^2 - 4z^1 + 5");
}

// ������������ ����������� ������������
TEST(PolynomialTest, CopyConstructor) {
	Polynomial poly1("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial poly2(poly1);
	EXPECT_EQ(poly2.toString(), "2x^3 + 3y^2 - 4z^1 + 5");
}

// ������������ ������������� ������������
TEST(PolynomialTest, MoveConstructor) {
	Polynomial poly1("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial poly2(std::move(poly1));
	EXPECT_EQ(poly2.toString(), "2x^3 + 3y^2 - 4z^1 + 5");
	EXPECT_EQ(poly1.toString(), "0"); // ���������, ��� �������� ������ ����
}

// ������������ ������� ��������� ��������
TEST(PolynomialTest, ParseExpression) {
	Polynomial poly;
	poly.parseExpression("2x^3 + 3y^2 - 4z^1 + 5");
	EXPECT_EQ(poly.toString(), "2x^3 + 3y^2 - 4z^1 + 5");
}

// ������������ ��������� �������� ���������
TEST(PolynomialTest, AdditionOperator) {
	Polynomial poly1("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial poly2("x^2 + 2y^1 + z^1");
	Polynomial result = poly1 + poly2;
	EXPECT_EQ(result.toString(), "2x^3 + x^2 + 3y^2 + 2y^1 - 3z^1 + 5");
}

// ������������ ��������� ��������� ���������
TEST(PolynomialTest, SubtractionOperator) {
	Polynomial poly1("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial poly2("x^2 + 2y^1 + z^1");
	Polynomial result = poly1 - poly2;
	EXPECT_EQ(result.toString(), "2x^3 - x^2 + 3y^2 - 2y^1 - 5z^1 + 5");
}

// ������������ ��������� �������� �������� � ������
TEST(PolynomialTest, AdditionWithScalar) {
	Polynomial poly("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial result = poly + 10;
	EXPECT_EQ(result.toString(), "2x^3 + 3y^2 - 4z^1 + 15");
}

// ������������ ��������� ��������� ����� �� ��������
TEST(PolynomialTest, SubtractionWithScalar) {
	Polynomial poly("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial result = poly - 3;
	EXPECT_EQ(result.toString(), "2x^3 + 3y^2 - 4z^1 + 2");
}

TEST(PolynomialTest, MultiplicationOperator_Simple) {
	Polynomial poly1("2x^1 + 3");
	Polynomial poly2("x^1 + 1");
	Polynomial result = poly1 * poly2;
	EXPECT_EQ(result.toString(), "2x^2 + 5x^1 + 3");
}

TEST(PolynomialTest, MultiplicationOperator_Zero) {
	Polynomial poly1("x^2 + 2x^1 + 1");
	Polynomial poly2("0");
	Polynomial result = poly1 * poly2;
	EXPECT_EQ(result.toString(), "0");
}

TEST(PolynomialTest, MultiplicationOperator_One) {
	Polynomial poly1("x^2 + 2x^1 + 1");
	Polynomial poly2("1");
	Polynomial result = poly1 * poly2;
	EXPECT_EQ(result.toString(), "x^2 + 2x^1 + 1");
}

// ������������ ��������� ��������� �������� �� �����
TEST(PolynomialTest, MultiplicationWithScalar) {
	Polynomial poly("2x^3 + 3y^2 - 4z^1 + 5");
	Polynomial result = poly * 2;
	EXPECT_EQ(result.toString(), "4x^3 + 6y^2 - 8z^1 + 10");
}
