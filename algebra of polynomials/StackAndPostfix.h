#include "TableManager.h"


// ��������� ����� �����, ������������ std::vector ��� �������� ���������.
template<typename T>
class Stack {
private:
    std::vector<T> data;  // ������ ��� �������� ��������� �����

public:
    // ����� ��� ���������� �������� � ����
    void push(const T& item) {
        data.push_back(item);  // ���������� �������� � ����� �������
    }

    // ����� ��� ���������� �������� �� �����
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Pop from empty stack");  // ���� ���� ����, ��������� ����������
        }
        T item = data.back();  // ��������� ���������� �������� �� �������
        data.pop_back();  // �������� ���������� �������� �� �������
        return item;  // ����������� ������������ ��������
    }

    // ����� ��� ��������� �������� �������� ����� ��� ��� ��������
    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Top from empty stack");  // ���� ���� ����, ��������� ����������
        }
        return data.back();  // ����������� ���������� �������� �� �������
    }

    // ����� ��� ��������, ���� �� ����
    bool isEmpty() const {
        return data.empty();  // �������� ������� ��������� � �������
    }
};


// ����� ������������ ��� ���������� ��������� � ����������� �������.
class PostfixCalculator {
private:
    TableManager& tableManager;  // ������ �� �������� ������, ���������� ��������

public:
    // �����������, ���������������� ����������� � ���������� ������
    PostfixCalculator(TableManager& tableManager) : tableManager(tableManager) {}

    // �������� ����� ��� ���������� ���������
    // �������� ����� ��� ���������� ���������
    Polynomial evaluate(const std::string& expression) {
        IPolynomialTable* table = tableManager.getActiveTable();  // ��������� �������� �������
        std::istringstream iss(expression);
        std::string token;
        Stack<Polynomial> stack;  // ���� ��� �������� ��������� � �������� ����������

        // ������ � ���������� ���������
        while (iss >> token) {
            if (isOperator(token)) {  // ���� ����� - ��������, ��������� ��������
                Polynomial result = performOperation(token, stack);
                stack.push(result);
            }
            else if (std::regex_match(token, std::regex("^[-+]?[0-9]*\\.?[0-9]+$"))) {  // ���� ����� - �����, ����������� � �������
                double scalar = std::stod(token);
                Polynomial scalarPoly = Polynomial(std::to_string(scalar));
                stack.push(scalarPoly);
            }
            else {  // �����, ����� - ��� ��������, �������� ������� �� �������
                Polynomial& poly = table->getPolynomial(token);
                stack.push(poly);
            }
        }

        // ���� ���� ���� ����� ���������, ��������� �����������
        if (stack.isEmpty()) {
            throw std::runtime_error("Error in expression: no result on stack");
        }

        Polynomial finalResult = stack.pop();  // ��������� ���������� ���������
        return finalResult;
    }

    // �������������� ���������� ��������� � �����������
    std::string infixToPostfix(const std::string& infix) {
        std::stack<char> opStack;
        std::string postfix = "";
        for (size_t i = 0; i < infix.length(); i++) {
            char c = infix[i];
            if (c == ' ') continue;
            if (isdigit(c) || isalpha(c) || c == '.') {
                postfix += c;
                while (i + 1 < infix.length() && (isdigit(infix[i + 1]) || isalpha(infix[i + 1]) || infix[i + 1] == '.')) {
                    postfix += infix[++i];
                }
                postfix += " ";
            }
            else if (c == '(') {
                opStack.push(c);
            }
            else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    postfix += opStack.top();
                    postfix += " ";
                    opStack.pop();
                }
                opStack.pop();
            }
            else if (isOperator(c)) {
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                    postfix += opStack.top();
                    postfix += " ";
                    opStack.pop();
                }
                opStack.push(c);
            }
        }

        while (!opStack.empty()) {
            postfix += opStack.top();
            postfix += " ";
            opStack.pop();
        }

        return postfix;
    }

private:
    // ��������, �������� �� ������ ����������
    bool isOperator(std::string token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    // ��������, �������� �� ������ ����������
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // ����������� ���������� ����������
    int precedence(char op) {
        switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
        }
    }

    // ���������� �������������� �������� ��� ����� ����������
    Polynomial performOperation(const std::string& op, Stack<Polynomial>& stack) {
        Polynomial right = stack.pop();  // ��������� ������� ��������
        Polynomial left = stack.pop();   // ��������� ������ ��������

        if (op == "+") {
            return left + right;
        }
        else if (op == "-") {
            return left - right;
        }
        else if (op == "*") {
            return left * right;
        }
        else if (op == "/") {
            throw std::runtime_error("Division of polynomials is not implemented");
        }

        throw std::runtime_error("Invalid operation");
    }
};
