#include <iostream>
#include <vector>
#include "AbstractTable.h"
#include "ArrayTable.h"
#include "LinkedTable.h"
#include "OrderedArrayTable.h"
#include "ChainedHashTable.h"
#include "OpenAddressingHashTable.h"
#include "RedBlackTree.h"


class tablesControl {
private:
    int activeIdx = 0;
    vector<shared_ptr<AbstractTable>> vec;

public:
    tablesControl(int activeIdx) : activeIdx(activeIdx) {

        shared_ptr<AbstractTable> table1 = make_shared<ArrayTable>();
        shared_ptr<AbstractTable> table2 = make_shared<LinkedTable>();
        shared_ptr<AbstractTable> table3 = make_shared<OrderedArrayTable>();
        shared_ptr<AbstractTable> table4 = make_shared<ChainedHashTable>();
        shared_ptr<AbstractTable> table5 = make_shared<OpenAddressingHashTable>();
        insertTable(table1);
        insertTable(table2);
        insertTable(table3);
        insertTable(table4);
        insertTable(table5);
    }

    void insertTable(shared_ptr<AbstractTable> table) {

        vec.push_back(table);
    }

    int getActiveIndex() { return activeIdx; }

    void setActiveIndex(int idx) { activeIdx = idx; }

    int getSize() { return vec.size(); }

    void changeKeyFromAll(string oldKey, string newKey) {

        for (size_t i = 0; i < vec.size(); i++)
        {
            vec[i]->changeKey(oldKey, newKey);
        }
    }

    void deleteFromAll(string key) {

        for (int i = 0; i < vec.size(); i++)
        {
            vec[i]->deleteData(key);
        }
    }

    void insertIntoAll(string key, TList<Monom> data) {

        for (int i = 0; i < vec.size(); i++)
        {
            vec[i]->insert(key, data);
        }
    }

    TList<Monom>& getDataFromActive(string key) {

        TList<Monom>* foundList = vec[activeIdx]->find(key);

        if (foundList == nullptr) { throw runtime_error("Data not found for key: " + key); }
        return *foundList;
    }

    friend ostream& operator<<(ostream& stream, const tablesControl& source) {

        stream << *source.vec[source.activeIdx];
        return stream;
    }
};