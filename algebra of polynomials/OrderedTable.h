

// ����� ��� ���������� �������� ���������, ��������� ������������� ������ ��� ��������.
class PolynomialOrderedTable : public IPolynomialTable {
private:
    std::vector<std::pair<std::string, Polynomial>> table;  // ������, �������� ���� "���-�������", ������������� �� �����
    std::string table_name = "PolynomialOrderedTable";  // ��� �������

public:
    // ���������� �������� � �������
    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        // ���������� std::lower_bound ��� ���������� ����� ������� ��� ���������� ��������
        auto it = std::lower_bound(table.begin(), table.end(), name,
            [](const std::pair<std::string, Polynomial>& element, const std::string& value) {
                return element.first < value;
            });

        if (it != table.end() && it->first == name) {
            // ��������� ������������ �������
            it->second = polynomial;
        }
        else {
            // ��������� ����� ������� �� ��������� �����
            table.insert(it, { name, polynomial });
        }
    }

    // ��������� �������� �� �����
    Polynomial& getPolynomial(const std::string& name) override {
        // ����� �������� � �������������� std::lower_bound
        auto it = std::lower_bound(table.begin(), table.end(), name,
            [](const std::pair<std::string, Polynomial>& element, const std::string& value) {
                return element.first < value;
            });

        if (it != table.end() && it->first == name) {
            // ���������� ��������� �������
            return it->second;
        }
        else {
            // ���� ������� �� ������, ������� ����������
            throw std::out_of_range("Polynomial not found with the name: " + name);
        }
    }

    // �������� �������� �� �����
    void removePolynomial(const std::string& name) override {
        // ����������� ����� �������� ��� ��������
        auto it = std::lower_bound(table.begin(), table.end(), name,
            [](const std::pair<std::string, Polynomial>& element, const std::string& value) {
                return element.first < value;
            });

        if (it != table.end() && it->first == name) {
            // �������� ��������, ���� ������
            table.erase(it);
        }
        else {
            // ���� �� ������, ������� ����������
            throw std::out_of_range("Polynomial not found with the name: " + name);
        }
    }

    // ��������� ����� �������
    std::string getTableName() const override {
        return table_name;
    }

    // ������ ����������� �������
    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        for (const auto& entry : table) {
            os << entry.first << ": ";  // ����� ����� ��������
            entry.second.print(os);  // ����� ������ ��������
        }
        os << "-----------" << std::endl;
    }
};