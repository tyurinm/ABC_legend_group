

class ChainedPolynomialHashTable : public IPolynomialTable {
private:
    std::string table_name = "PolynomialHashTable";  // ��� �������, ������������ ��� �������������
    std::vector<std::list<std::pair<std::string, Polynomial>>> hash_table;  // ���-������� � ������� �������

    // ������� ���-������� ��� �����
    size_t hashFunction(const std::string& key) const {
        size_t hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % hash_table.size();
    }

public:
    // ����������� �� ���������
    ChainedPolynomialHashTable() : hash_table(10) {} // ����� ������ ������ 10 ��� ���-������� �� ���������, ����� ������� ���� ������

    // ����������� � �������� �������� �������
    ChainedPolynomialHashTable(size_t table_size) : hash_table(table_size) {}

    // ���������� �������� � �������
    void addPolynomial(const std::string& name, const Polynomial& polynomial) override {
        size_t index = hashFunction(name);
        hash_table[index].push_back({ name, polynomial });
    }

    // ��������� �������� �� �����
    Polynomial& getPolynomial(const std::string& name) override {
        size_t index = hashFunction(name);
        for (auto& pair : hash_table[index]) {
            if (pair.first == name) {
                return pair.second;
            }
        }
        throw std::out_of_range("Polynomial not found");
    }

    // �������� �������� �� �����
    void removePolynomial(const std::string& name) override {
        size_t index = hashFunction(name);
        auto& list = hash_table[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == name) {
                list.erase(it);
                return;
            }
        }
    }

    // ��������� ����� �������
    std::string getTableName() const override {
        return table_name;  // ���������� ��� �������, ������������� � ������������ ��� �� ���������
    }

    // ������ ����������� ������� ���������
    void print(std::ostream& os) const override {
        os << table_name << ":" << std::endl << "-----------" << std::endl;
        for (size_t i = 0; i < hash_table.size(); ++i) {
            for (const auto& pair : hash_table[i]) {
                os << pair.first << ": ";  // ����� ����� ��������
                pair.second.print(os);  // ����� ������ ��������, ������� ��� ����� print
                os << std::endl;
            }
        }
        os << "-----------" << std::endl;
    }
};
