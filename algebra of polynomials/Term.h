#include <map>

class Term {
public:
  // �������� � ������ ������
  void operator+=(const Term& other);
  // ��������� �� ������ ����
  void operator*=(const Term& other);
  // ����������������� �����
  void Differentiation();
  // �������������� �����
  void Integration();
private:
  // ����������� �����
  double coefficient;
  // ���������� � �� �������
  std::map<char, int> variables;
};
