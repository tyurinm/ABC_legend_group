#include <list>

template <typename T>
class Sequence {
public:
  // ������� �������� � ������������� ������������������
  void insertInOrder(const T& value);
  // �������� �������� �� ������������������
  void erase(const T& value);
  // ������ � �������� �� �������
  T operator;
private:
  // ������, ���������� � ������������������
  std::list<T> data;
};
