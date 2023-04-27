#include <iostream>

namespace ariel
{
    using namespace std;

    class Fraction
    {
    private:
        int numerator;
        int denominator;
        int findGcd() const;

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(double floatNumber);
        int getNumerator() const;
        int getDenominator() const;
        void reduceFraction();

        // overloading +,-,*,/,==,>,<,<=,>=,++,--,<<,>>
        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;

        Fraction operator*(double floatNumber) const;
        Fraction operator+(double floatNumber) const;
        Fraction operator-(double floatNumber) const;
        Fraction operator/(double floatNumber) const;

        Fraction operator++(int dummy_flag);
        Fraction operator--(int dummy_flag);
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