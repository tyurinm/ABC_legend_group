#include "Operators.h"
#include "Stack.h"
#include <string>

class PostfixConverter {
public:
  // �������������� ���������� ��������� � �����������
  std::string ToPostfix(const std::string& infix);
  // �������� ������������ ���������
  bool CheckOfExpression(const std::string& expression);
  // ���������� ������������ ���������
  double Calculate(const std::string& postfix);
private:
  // ���������, ������������ � ���������
  Operators<double> operators;
  // ���� ��� �������� �������� ��� �������������� ���������
  Stack<std::string> stack;
};
