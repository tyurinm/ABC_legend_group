

// ����������� ������ ��� ������ ��������.
class PolynomialTerm {
public:
    double coefficient;  // ����������� ����� ��������.
    int x_exp, y_exp, z_exp;  // ������� ���������� x, y, z.

    // ����������� ������ � �������������� ������������ � �������� ����������.
    PolynomialTerm(double coef, int x, int y, int z)
        : coefficient(coef), x_exp(x), y_exp(y), z_exp(z) {}

    // �������� ��������� "������", ������������ ��� ��������� ������ �� ��������.
    bool operator<(const PolynomialTerm& other) const {
        if (x_exp != other.x_exp) return x_exp < other.x_exp;  // ������� ���������� �� x.
        if (y_exp != other.y_exp) return y_exp < other.y_exp;  // ����� �� y.
        return z_exp < other.z_exp;                            // �������, �� z.
    }


    // �������� ��������� "������", ���������� �� ��������� "������".
    bool operator>(const PolynomialTerm& other) const {
        return other < *this;  // ���������� �������� "������" ��� ��������� � �������� �������.
    }

    // �������� ��������� "������ ��� �����", ���������� �� ��������� "������".
    bool operator<=(const PolynomialTerm& other) const {
        return !(*this > other);  // ���� ���� �� ������ �������, �� �� ���� ������, ���� �����.
    }

    // �������� ��������� "������ ��� �����", ����� ���������� �� ��������� "������".
    bool operator>=(const PolynomialTerm& other) const {
        return !(*this < other);  // ���� ���� �� ������ �������, �� �� ���� ������, ���� �����.
    }

    // �������� ��������� �� ���������, ��������� ��������� ���� ����� �����.
    bool operator==(const PolynomialTerm& other) const {
        return x_exp == other.x_exp && y_exp == other.y_exp && z_exp == other.z_exp && coefficient == other.coefficient;
    }

    // �������� ��������� �� �����������, ���������� �� ��������� ���������.
    bool operator!=(const PolynomialTerm& other) const {
        return !(*this == other);  // ������ ����������� ��������� ��������� ���������.
    }
};
// ����� �������������� �������, ���������� ������ ������.
class Polynomial {
    std::list<PolynomialTerm> terms; // ������ ������ ��������, ��������� STL ��������� std::list

public:
    const std::list<PolynomialTerm> getTerms() const {
        return terms;
    }

    bool isNumber() const {
        return terms.size() == 1 && terms.front().x_exp == 0 && terms.front().y_exp == 0 && terms.front().z_exp == 0;
    }
    // ����������� �� ���������
    Polynomial() = default; // ���������� ����������� ����������� ��� ������������� ������

    // ����������� � ���������� ������, ������� ������ ������ � ���������� ��������
    Polynomial(const std::string& expression) {
        parseExpression(expression); // ������� ���������� ������ ��� �������� �������
    }

    // ����������� �����������
    Polynomial(const Polynomial& other) : terms(other.terms) {} // �������� ������ ������ �� ������� ��������

    // ����������� �����������
    Polynomial(Polynomial&& other) noexcept : terms(std::move(other.terms)) {} // ���������� ������ ������, ��������� move-���������

    // ����������
    ~Polynomial() = default; // ���������� ����������� ����������

    std::string toString() const {
        std::ostringstream oss;
        bool isFirst = true;
        for (auto it = terms.rbegin(); it != terms.rend(); ++it) {
            const auto& term = *it;
            if (term.coefficient == 0) continue; // ������� ������ � ������� �������������

            if (!isFirst) {
                oss << (term.coefficient > 0 ? " + " : " - ");
            }
            else {
                if (term.coefficient < 0) oss << "-";
                isFirst = false;
            }

            if (fabs(term.coefficient) != 1 || (term.x_exp == 0 && term.y_exp == 0 && term.z_exp == 0)) {
                oss << fabs(term.coefficient);
            }
            if (term.x_exp > 0) {
                oss << "x";
                if (term.x_exp != 1) oss << "^" << term.x_exp;
                else oss << "^1"; // ��������� ����� �������� ������� 1
            }
            if (term.y_exp > 0) {
                oss << "y";
                if (term.y_exp != 1) oss << "^" << term.y_exp;
                else oss << "^1"; // ��������� ����� �������� ������� 1
            }
            if (term.z_exp > 0) {
                oss << "z";
                if (term.z_exp != 1) oss << "^" << term.z_exp;
                else oss << "^1"; // ��������� ����� �������� ������� 1
            }
        }
        if (isFirst) oss << "0";
        return oss.str();
    }

    // ������ ��������� ��������
    void parseExpression(const std::string& input_poly) {
        // �������� ���� �������� �� ������� ������ � ������ "-" �� "+-", ����� ��������� ��������� �� �����
        std::string processed_poly = std::regex_replace(input_poly, std::regex("\\s+"), "");
        processed_poly = std::regex_replace(processed_poly, std::regex(","), ".");
        processed_poly = std::regex_replace(processed_poly, std::regex("-"), "+-");

        // ���������� ��������� ��� ��������� �������� �� �����
        std::regex pattern(R"(([-+]?\d*\.?\d*)(x\^(\d*))?(y\^(\d*))?(z\^(\d*))?)");
        std::regex plus_regex("\\+");
        std::sregex_token_iterator iter(std::begin(processed_poly), std::end(processed_poly), plus_regex, -1);
        std::sregex_token_iterator end;

        for (; iter != end; ++iter) {
            std::string monom = *iter;
            if (monom.empty()) continue;
            std::smatch match;
            if (std::regex_match(monom, match, pattern)) {
                // ��������� ������������ � ��������, � ���������� ����� � ������
                double coef = match.str(1).empty() || match.str(1) == "+" ? 1.0 : match.str(1) == "-" ? -1.0 : std::stod(match.str(1));
                int x_deg = match.length(3) > 0 ? std::stoi(match.str(3)) : 0;
                int y_deg = match.length(5) > 0 ? std::stoi(match.str(5)) : 0;
                int z_deg = match.length(7) > 0 ? std::stoi(match.str(7)) : 0;

                addTerm(coef, x_deg, y_deg, z_deg);
            }
        }
    }


    // ���������� ����� � �������
    void addTerm(double coefficient, int x_exp, int y_exp, int z_exp) {
        if (coefficient == 0) {
            return; // ���� ����������� ����� ����, ���� �� �����������
        }

        PolynomialTerm newTerm(coefficient, x_exp, y_exp, z_exp);
        // ����� ����� ��� ������� ����� � ������������� ������
        auto it = std::find_if(terms.begin(), terms.end(), [&](const PolynomialTerm& term) {
            return (term.x_exp > x_exp) ||
                (term.x_exp == x_exp && term.y_exp > y_exp) ||
                (term.x_exp == x_exp && term.y_exp == y_exp && term.z_exp >= z_exp);
            });

        if (it != terms.end() && it->x_exp == x_exp && it->y_exp == y_exp && it->z_exp == z_exp) {
            // ���� ���� � ������ �� ��������� ��� ����������, ����������� ��� �����������
            it->coefficient += coefficient;
            if (it->coefficient == 0) {
                // ���� ����������� ���������� �������, ���� ���������
                terms.erase(it);
            }
        }
        else {
            // ������� ������ ����� �� ������ �����
            terms.insert(it, newTerm);
        }
    }

    double evaluate(double x, double y, double z) const {
        double result = 0.0;
        for (const auto& term : terms) {
            result += term.coefficient * pow(x, term.x_exp) * pow(y, term.y_exp) * pow(z, term.z_exp);
        }
        return result;
    }

    // �������� �������� ���� ���������
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result = *this; // �������� ������� ������� � ���������
        for (const auto& term : other.terms) {
            result.addTerm(term.coefficient, term.x_exp, term.y_exp, term.z_exp);
        }
        return result;
    }

    // �������� ��������� ���� ��������� �� ���������
    bool operator==(const Polynomial& other) const {
        return terms == other.terms; // ���������� ������ ������
    }

    // �������� ��������� ���� ���������
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result = *this; // �������� ������� ������� � ���������
        for (const auto& term : other.terms)
            result.addTerm(-term.coefficient, term.x_exp, term.y_exp, term.z_exp); // ��������� � ��������������� ������
        return result;
    }

    // �������� ��������� ����� �� ��������
    Polynomial operator-(double scalar) const {
        Polynomial result = *this;
        result.addTerm(-scalar, 0, 0, 0); // ��������� ����������� ����
        return result;
    }

    // �������� �������� ����� � ���������
    Polynomial operator+(double scalar) const {
        Polynomial result = *this;
        result.addTerm(scalar, 0, 0, 0); // ��������� ����������� ����
        return result;
    }

    // �������� ��������� ���������
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        for (const auto& term1 : terms) {
            for (const auto& term2 : other.terms) {
                double new_coef = term1.coefficient * term2.coefficient;
                int new_x_exp = term1.x_exp + term2.x_exp;
                int new_y_exp = term1.y_exp + term2.y_exp;
                int new_z_exp = term1.z_exp + term2.z_exp;
                result.addTerm(new_coef, new_x_exp, new_y_exp, new_z_exp);
            }
        }
        return result;
    }



    // �������� ��������� �������� �� ����� (������� * �����)
    Polynomial operator*(double scalar) const {
        Polynomial result;
        for (const auto& term : terms) {
            double new_coef = term.coefficient * scalar;
            if (new_coef != 0) {  // �������� ���������� �������� �����
                result.addTerm(new_coef, term.x_exp, term.y_exp, term.z_exp);
            }
        }
        return result;
    }

    // �������� ��������� ����� �� ������� (����� * �������)
    friend Polynomial operator*(double scalar, const Polynomial& poly) {
        return poly * scalar;
    }

    // ��������� ������������ ������������
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {  // �������� �� ����������������
            terms.clear();  // �������� ������� ������ ������
            terms = other.terms;  // ���������� ����� �� ������� ��������
        }
        return *this;
    }

    // ����� �������
    void print() const {
        bool isFirst = true;
        for (const auto& term : terms) {
            if (term.coefficient == 0) continue;  // Skip zero coefficients

            if (!isFirst) {
                std::cout << (term.coefficient > 0 ? " + " : " - ");
            }
            else {
                if (term.coefficient < 0) std::cout << "-";
                isFirst = false;
            }

            // Print absolute value of the coefficient if it's not 1 or -1, except when all exponents are 0
            if (fabs(term.coefficient) != 1 || (term.x_exp == 0 && term.y_exp == 0 && term.z_exp == 0)) {
                std::cout << fabs(term.coefficient);
            }
            if (term.x_exp > 0) std::cout << "x" << (term.x_exp > 1 ? "^" + std::to_string(term.x_exp) : "");
            if (term.y_exp > 0) std::cout << "y" << (term.y_exp > 1 ? "^" + std::to_string(term.y_exp) : "");
            if (term.z_exp > 0) std::cout << "z" << (term.z_exp > 1 ? "^" + std::to_string(term.z_exp) : "");
        }
        if (isFirst) std::cout << "0";  // If all terms were zero, print "0"
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
        p.print(os);
        return os;
    }

    void print(std::ostream& os) const {
        bool isFirst = true;
        for (const auto& term : terms) {
            if (term.coefficient == 0) continue; // ������� ������ � ������� �������������

            if (!isFirst) {
                os << (term.coefficient > 0 ? " + " : " - ");
            }
            else {
                if (term.coefficient < 0) os << "-";
                isFirst = false;
            }

            if (fabs(term.coefficient) != 1 || (term.x_exp == 0 && term.y_exp == 0 && term.z_exp == 0)) {
                os << fabs(term.coefficient);
            }
            if (term.x_exp > 0) os << "x" << (term.x_exp > 1 ? "^" + std::to_string(term.x_exp) : "");
            if (term.y_exp > 0) os << "y" << (term.y_exp > 1 ? "^" + std::to_string(term.y_exp) : "");
            if (term.z_exp > 0) os << "z" << (term.z_exp > 1 ? "^" + std::to_string(term.z_exp) : "");
        }
        if (isFirst) os << "0";
        os << std::endl;
    }
};
