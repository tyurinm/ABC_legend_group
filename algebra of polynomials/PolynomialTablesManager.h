#ifndef POLYNOMIAL_TABLES_MANAGER_H
#define POLYNOMIAL_TABLES_MANAGER_H

#include "Polynomial.h"
#include "PolynomialTable.h"
#include <memory>
#include <string>
#include <vector>
#include <map>

// ����� ��� ���������� ������� ������ ���������
class PolynomialTablesManager {
private:
  std::map<std::string, std::shared_ptr<PolynomialTable>> tables;

public:
  // ������������ ����� ������� � ���������
  void registerTable(const std::string& tableName, std::shared_ptr<PolynomialTable> table) {
    tables[tableName] = table;
  }

  // ��������� ������� �� ��� ������������������ �������
  void addPolynomialToAll(const Polynomial& poly) {
    for (auto& tablePair : tables) {
      tablePair.second->insert(poly);
    }
  }

  // ������� ������� �� ���� ������������������ ������ �� ����� ��������
  void removePolynomialFromAll(const std::string& polyName) {
    for (auto& tablePair : tables) {
      tablePair.second->remove(polyName);
    }
  }

  // ���� ������� � ��������� ������� �� ����� ��������
  std::shared_ptr<Polynomial> findPolynomialInTable(const std::string& tableName, const std::string& polyName) {
    if (tables.find(tableName) != tables.end()) {
      return tables[tableName]->find(polyName);
    }
    return nullptr; // ���� ������� �� �������, ���������� nullptr
  }

  // ������� ���������� ���� ������ �� �����
  void displayAll() const {
    for (const auto& tablePair : tables) {
      std::cout << "Table: " << tablePair.first << std::endl;
      tablePair.second->display();
    }
  }
};

#endif // POLYNOMIAL_TABLES_MANAGER_H
