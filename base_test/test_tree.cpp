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

// ���� ��� �������� ���������� �������� � ������ �������
TEST(PolynomialTableWithRedBlackTreeTest, AddPolynomialToEmptyTable) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly1", polynomial);
	EXPECT_EQ(table.getPolynomial("poly1"), polynomial);
}

// ���� ��� �������� ��������� �������� �� �������
TEST(PolynomialTableWithRedBlackTreeTest, GetPolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly", polynomial);
	EXPECT_EQ(table.getPolynomial("poly"), polynomial);
}

// ���� ��� �������� ��������� ��������������� �������� �� �������
TEST(PolynomialTableWithRedBlackTreeTest, GetNonexistentPolynomial) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_THROW(table.getPolynomial("nonexistent_poly"), std::out_of_range);
}

// ���� ��� �������� �������� ������������� �������� �� �������
TEST(PolynomialTableWithRedBlackTreeTest, RemoveExistingPolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial({ 3, 2, -1 });
	table.addPolynomial("poly1", polynomial);
	table.addPolynomial("poly2", Polynomial({ 1, 2, 3 }));
	table.removePolynomial("poly1");
	EXPECT_THROW(table.getPolynomial("poly1"), std::out_of_range);
	EXPECT_EQ(table.getPolynomial("poly2"), Polynomial({ 1, 2, 3 }));
}

// ���� ��� �������� �������� ��������������� �������� �� �������
TEST(PolynomialTableWithRedBlackTreeTest, RemoveNonexistentPolynomial) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_THROW(table.removePolynomial("nonexistent_poly"), std::out_of_range);
}

// ���� ��� �������� ��������� ����� �������
TEST(PolynomialTableWithRedBlackTreeTest, GetTableName) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_EQ(table.getTableName(), "PolynomialTableWithRedBlackTree");
}

// ���� ��� �������� ������ ������ �������
TEST(PolynomialTableWithRedBlackTreeTest, PrintEmptyTable) {
	PolynomialTableWithRedBlackTree table;
	std::ostringstream oss;
	table.print(oss);
	std::string expected_output = "PolynomialTableWithRedBlackTree:\n-----------\n-----------\n";
	EXPECT_EQ(oss.str(), expected_output);
}

// ���� ��� �������� ������ ������� � ����� ���������
TEST(PolynomialTableWithRedBlackTreeTest, PrintTableWithOnePolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly", polynomial);
	std::ostringstream oss;
	table.print(oss);
	std::string expected_output = "PolynomialTableWithRedBlackTree:\n-----------\npoly: -z + 2y + 3x^2\n\n-----------\n";
	EXPECT_EQ(oss.str(), expected_output);
}

// ���� ��� �������� �������� �������� �� ������� � ����������� ����������
TEST(PolynomialTableWithRedBlackTreeTest, RemovePolynomialWithMultiplePolynomials) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial1("3x^2 + 2y^1 - z^1");
	Polynomial polynomial2("x^1 + y^1 + z^1");
	table.addPolynomial("poly1", polynomial1);
	table.addPolynomial("poly2", polynomial2);
	table.removePolynomial("poly1");
	EXPECT_THROW(table.getPolynomial("poly1"), std::out_of_range);
	EXPECT_EQ(table.getPolynomial("poly2"), polynomial2);
}



// ���� ��� �������� �������� ��������������� �������� �� �������
TEST(PolynomialTableWithRedBlackTreeTest, RemoveNonexistentPolynomial1) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	Polynomial polynomial1("x^1 + y^1 + z^1");
	table.addPolynomial("poly1", polynomial);
	table.addPolynomial("poly2", polynomial1);
	// ������� �������������� �������
	EXPECT_THROW(table.removePolynomial("nonexistent_poly"), std::out_of_range);
	// ���������, ��� ��������� ������� �� ����������
	EXPECT_EQ(table.getPolynomial("poly1"), polynomial);
	EXPECT_EQ(table.getPolynomial("poly2"), polynomial1);
}
