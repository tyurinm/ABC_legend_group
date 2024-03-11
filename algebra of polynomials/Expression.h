#include "Sequence.h"
#include "Term.h"

class Expression {
public:
  // �������� � ������ ����������
  void operator+=(const Expression& other);
  // ��������� �� ������ ���������
  void operator*=(const Expression& other);
  // ����������������� ���������
  void Differentiation();
  // �������������� ���������
  void Integration();
private:
  // �����, ������������ ���������
  Sequence<Term> terms;
};
