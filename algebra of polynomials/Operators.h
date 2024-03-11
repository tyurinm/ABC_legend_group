#include <string>

template <typename T>
class Operators {
public:
  // ��������, �������� �� ������ ���������
  bool IfIsOperation(const std::string& str);
  // ��������� ���������� ��������
  int GetPriority(const std::string& operation);
  // ���������� �������� ��� ����������
  T Calculation(const T& left, const T& right, const std::string& operation);
};
