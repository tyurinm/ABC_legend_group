#include <list>

template <typename T>
class Stack {
public:
  // ���������� �������� � ����
  void push(const T& value);
  // �������� �������� �� �����
  void pop();
  // ��������� �������� �������� �����
  T getTop();
  // �������� ����� �� �������
  bool empty();
private:
  // ������, ���������� � �����
  std::list<T> data;
};
