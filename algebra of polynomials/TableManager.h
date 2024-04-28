#include "Polinomial.h"
#include "IPolynomialTable.h"
#include "ListTable.h"
#include "ArrayTable.h"
#include "OrderedTable.h"
#include "RBTreeTable.h"
#include "HachTable.h"
#include "ChainedlHashTable.h"

// ����� ��� ���������� ���������� ������ ���������
class TableManager {
private:
    std::vector<IPolynomialTable*> tables;  // ������ ���������� �� ������� ���������
    IPolynomialTable* activeTable = nullptr;  // ��������� �� ������� �������� �������

public:
    // �����������
    TableManager() {
        // �������� � ���������� ������ � ������ ����������
        tables.push_back(new PolynomialListTable());
        tables.push_back(new PolynomialArrayTable());
        tables.push_back(new PolynomialOrderedTable());
        tables.push_back(new PolynomialTableWithRedBlackTree());
        tables.push_back(new PolynomialHashTable());
        tables.push_back(new ChainedPolynomialHashTable());

        // ��������� ������ ������� � ������ ��� ��������
        setActiveTable(tables[0]);  // ��������� �������� ������� �� ���������
    }

    // ����������
    ~TableManager() {
        // ������� ������: �������� ���� ������
        for (auto& table : tables) {
            delete table;  // �������� ��������, �� ������� ��������� ���������
        }
    }

    // ��������� �������� ������� �� ���������
    void setActiveTable(IPolynomialTable* table) {
        activeTable = table;
    }

    // ��������� �������� ������� �� �����
    void setActiveTableByName(const std::string& name) {
        for (auto& table : tables) {
            if (table->getTableName() == name) {
                activeTable = table;
                return;
            }
        }
        std::cout << "Table not found with the name: " << name << std::endl;
    }

    // ���������� �������� �� ��� �������
    void addPolynomialToAllTables(const std::string& name, const Polynomial& polynomial) {
        for (auto& table : tables) {
            table->addPolynomial(name, polynomial);
        }
    }

    // �������� �������� �� ���� ������
    void removePolynomialFromAllTables(const std::string& name) {
        for (auto& table : tables) {
            table->removePolynomial(name);
        }
    }

    // ��������� �������� �������
    IPolynomialTable* getActiveTable() const {
        return activeTable;
    }

    // ����� ����������� �������� �������
    void printActiveTable() const {
        if (activeTable) {
            std::cout << *activeTable;
        }
    }
};