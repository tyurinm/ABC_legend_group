#ifndef ARRAY_POLYNOMIAL_TABLE_H
#define ARRAY_POLYNOMIAL_TABLE_H

#include "PolynomialTable.h"
#include <vector>
#include <algorithm>
#include <iterator>

// Конкретная реализация таблицы полиномов на основе динамического массива
class ArrayPolynomialTable : public PolynomialTable {
private:
    // Структура для хранения полинома с его именем
    struct NamedPolynomial {
        std::string name;
        std::shared_ptr<Polynomial> polynomial;

        NamedPolynomial(const std::string& name, std::shared_ptr<Polynomial> polynomial)
            : name(name), polynomial(polynomial) {}

        // Оператор сравнения для поиска по имени
        bool operator==(const std::string& otherName) const {
            return name == otherName;
        }
    };

    std::vector<NamedPolynomial> table; // Вектор для хранения именованных полиномов

public:
    // Деструктор
    virtual ~ArrayPolynomialTable() override {}

    // Вставка полинома в таблицу
    void insert(const Polynomial& polynomial) override {
        auto it = std::find_if(table.begin(), table.end(),
                               [&](const NamedPolynomial& item) { return item.name == polynomial.getName(); });
        if (it != table.end()) {
            // Если полином с таким именем уже существует, заменяем его
            it->polynomial = std::make_shared<Polynomial>(polynomial);
        } else {
            // Иначе добавляем новый полином в таблицу
            table.push_back(NamedPolynomial(polynomial.getName(), std::make_shared<Polynomial>(polynomial)));
        }
    }

    // Удаление полинома из таблицы
    bool remove(const std::string& name) override {
        auto it = std::find(table.begin(), table.end(), name);
        if (it != table.end()) {
            table.erase(it);
            return true;
        }
        return false;
    }

    // Поиск полинома по имени
    std::shared_ptr<Polynomial> find(const std::string& name) const override {
        auto it = std::find(table.begin(), table.end(), name);
        if (it != table.end()) {
            return it->polynomial;
        }
        return nullptr;
    }

    // Вывод содержимого таблицы на экран
    void display() const override {
        for (const auto& item : table) {
            std::cout << "Name: " << item.name << ", Polynomial: " << *(item.polynomial) << std::endl;
        }
    }

    // Получение всех имен полиномов в таблице
    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        std::transform(table.begin(), table.end(), std::back_inserter(names),
                       [](const NamedPolynomial& item) { return item.name; });
        return names;
    }

    // Батчевое добавление
    void insertBatch(const std::vector<Polynomial>& polynomials) override {
      for (const auto& polynomial : polynomials) {
        insert(polynomial);
      }
    }

    // Батчевое удаление
    void removeBatch(const std::vector<std::string>& names) override {
      for (const auto& name : names) {
        remove(name);
      }
    }
};

#endif // ARRAY_POLYNOMIAL_TABLE_H
