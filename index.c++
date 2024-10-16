#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

class Fraction {
private:
    int numerator;
    int denominator;

    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    void reduce() {
        int gcdValue = gcd(numerator, denominator);
        numerator /= gcdValue;
        denominator /= gcdValue;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denom == 0) throw std::invalid_argument("Denominator cannot be zero");
        reduce();
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    bool operator==(const Fraction& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    bool operator<(const Fraction& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    std::string toString() const {
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.toString();
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& frac) {
        char slash;
        is >> frac.numerator >> slash >> frac.denominator;
        if (frac.denominator == 0) throw std::invalid_argument("Denominator cannot be zero");
        frac.reduce();
        return is;
    }
};

void readFractions(const std::string& filename, std::vector<Fraction>& fractions) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    Fraction frac;
    while (infile >> frac) {
        fractions.push_back(frac);
        std::cout << "Read: " << frac.toString() << std::endl;
    }
}

void writeResults(const std::string& filename, const std::vector<std::string>& results) {
    std::ofstream outfile(filename);
    for (const auto& result : results) {
        outfile << result << std::endl;
    }
}

int main() {
    std::vector<Fraction> fractions;
    std::vector<std::string> results;

    readFractions("Fractions.txt", fractions);

    for (size_t i = 0; i < fractions.size(); i += 2) {
        if (i + 1 < fractions.size()) {
            Fraction sum = fractions[i] + fractions[i + 1];
            results.push_back(fractions[i].toString() + " + " + fractions[i + 1].toString() + " = " + sum.toString());
            results.push_back(fractions[i].toString() + (fractions[i] == fractions[i + 1] ? " is equal to " : " is not equal to ") + fractions[i + 1].toString());
        }
    }

    writeResults("results.txt", results);
    return 0;
}
