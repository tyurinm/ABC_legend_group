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


// ���� �������� ���������� �������� � ��� ���������
TEST(PolynomialArrayTableTest, AddAndGetPolynomial) {
    PolynomialArrayTable table;
    Polynomial p1("2x+5y");
    table.addPolynomial("poly1", p1);

    // �������� ������� �� �����
    Polynomial retrieved = table.getPolynomial("poly1");

    // ���������, ��� ���������� ������� ��������� � �����������
    ASSERT_EQ(retrieved, p1);
}

// ���� �������� �������� ��������
TEST(PolynomialArrayTableTest, RemovePolynomial) {
    PolynomialArrayTable table;
    Polynomial p1("2x+5y");
    table.addPolynomial("poly1", p1);

    // ������� �������
    ASSERT_NO_THROW(table.removePolynomial("poly1"));

    // ������� �������� ��������� ������� ������ ������� ����������
    ASSERT_THROW(table.getPolynomial("poly1"), std::out_of_range);
}

// ���� �������� ��������� ��������������� ��������
TEST(PolynomialArrayTableTest, GetNonexistentPolynomial) {
    PolynomialArrayTable table;

    // ������� �������� �������������� ������� ������ ������� ����������
    ASSERT_THROW(table.getPolynomial("nonexistent_poly"), std::out_of_range);
}

// ���� �������� ���������� ��������
TEST(PolynomialArrayTableTest, UpdatePolynomial) {
    PolynomialArrayTable table;
    Polynomial p1("2x+5y");
    Polynomial p2("3x+6y");

    // ��������� �������
    table.addPolynomial("poly1", p1);

    // ��������� �������
    table.addPolynomial("poly1", p2);

    // �������� ����������� �������
    Polynomial retrieved = table.getPolynomial("poly1");

    // ���������, ��� ���������� ������� ��������� � ����� ���������
    ASSERT_EQ(retrieved, p2);
}

// ���� �������� ��������� ����� �������
TEST(PolynomialArrayTableTest, GetTableName) {
    PolynomialArrayTable table;

    // ���������, ��� ��� ������� ��������� ������������
    ASSERT_EQ(table.getTableName(), "PolynomialArrayTable");
}
