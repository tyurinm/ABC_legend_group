#include <iostream>
#include "Polynomial.h"
#include "RBTreePolynomialTable.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru_RU");

  std::cout << "������������ �������� ��� ���������� � ������ � ���������." << std::endl;

  // ���� �������� ������������� (������������ ���������� ������� ��� ������������)
  Polynomial userInputPolynomial;
  userInputPolynomial.addMonomial(Monomial(1, 2, 0, 1)); // 1x^2z
  userInputPolynomial.addMonomial(Monomial(-2, 0, 1, 2)); // -2yz^2
  userInputPolynomial.setName("userInput");
  std::cout << "��������� ������������� �������: " << userInputPolynomial << std::endl;

  // �������� ��� ����������
  Polynomial p1, p2;
  p1.addMonomial(Monomial(3, 2, 0, 0)); // 3x^2
  p1.setName("p1");
  p2.addMonomial(Monomial(-1, 0, 1, 2)); // -y^1z^2
  p2.setName("p2");

  Polynomial sum = p1 + p2;
  Polynomial diff = p1 - p2;
  Polynomial prod = p1 * p2;

  std::cout << "����� p1 + p2: " << sum << std::endl;
  std::cout << "�������� p1 - p2: " << diff << std::endl;
  std::cout << "������������ p1 * p2: " << prod << std::endl;

  // ������ � ���������
  RBTreePolynomialTable table;
  table.insert(p1);
  table.insert(p2);

  std::cout << "���������� ������� ����� ���������� p1 � p2:" << std::endl;
  table.display();

  // ����� � �������� ��������
  auto found = table.find("p1");
  if (found) {
    std::cout << "������ ������� 'p1': " << *found << std::endl;
  }
  else {
    std::cout << "'p1' �� ������." << std::endl;
  }

  table.remove("p1");
  std::cout << "���������� ������� ����� �������� 'p1':" << std::endl;
  table.display();

  return 0;
}