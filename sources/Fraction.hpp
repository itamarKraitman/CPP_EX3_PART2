#include <iostream>

namespace ariel
{
    using namespace std;

    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(double floatNumber);
        int getNumerator() const;
        int getDenominator() const;
        bool reduceFraction();
        int findGcd(int numerator, int denominator) const;

        // overloading +,-,*,/,==,>,<,<=,>=,++,--,<<,>>
        friend Fraction operator+(const Fraction &other1, const Fraction &other);
        friend Fraction operator-(const Fraction &other1, const Fraction &other);
        friend Fraction operator*(const Fraction &other1, const Fraction &other);
        friend Fraction operator/(const Fraction &other1, const Fraction &other);

        friend Fraction operator*(const Fraction &fraction, double floatNumber);
        friend Fraction operator+(const Fraction &fraction, double floatNumber);
        friend Fraction operator-(const Fraction &fraction, double floatNumber);
        friend Fraction operator/(const Fraction &fractiob, double floatNumber);

        friend Fraction operator++(Fraction& frac, int);
        friend Fraction operator--(Fraction& frac, int);
        Fraction &operator++();
        Fraction &operator--();

        friend Fraction operator+(double floatNumber, const Fraction &frac1);
        friend Fraction operator-(double floatNumber, const Fraction &frac1);
        friend Fraction operator*(double floatNumber, const Fraction &frac1);
        friend Fraction operator/(double floatNumber, const Fraction &frac1);

        friend bool operator==(const Fraction &frac1, const Fraction &frac2);
        friend bool operator>=(const Fraction &frac1, const Fraction &frac2);
        friend bool operator<=(const Fraction &frac1, const Fraction &frac2);
        friend bool operator>(const Fraction &frac1, const Fraction &frac2);
        friend bool operator<(const Fraction &frac1, const Fraction &frac2);
        friend bool operator==(double floatNumber, const Fraction &frac1);
        friend bool operator>=(double floatNumber, const Fraction &frac1);
        friend bool operator<=(double floatNumber, const Fraction &frac1);
        friend bool operator>(double floatNumber, const Fraction &frac1);
        friend bool operator<(double floatNumber, const Fraction &frac1);
        friend bool operator==(const Fraction &frac1, double floatNumber);
        friend bool operator>=(const Fraction &frac1, double floatNumber);
        friend bool operator<=(const Fraction &frac1, double floatNumber);
        friend bool operator>(const Fraction &frac1, double floatNumber);
        friend bool operator<(const Fraction &frac1, double floatNumber);

        friend std::ostream &operator<<(std::ostream &output, const Fraction &frac);
        friend std::istream &operator>>(std::istream &input, Fraction &frac);
    };
}