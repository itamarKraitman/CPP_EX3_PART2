#include <iostream>

namespace ariel
{
    using namespace std;

    class Fraction
    {
    private:
        int numerator;
        int denominator;
        static int findGcd(int first, int second);

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(float floatNumber);
        int getNumerator() const;
        int getDenominator() const;
        bool reduceFraction();
        static bool checkOverflow(long long first, long long second);

        // overloading +,-,*,/,==,>,<,<=,>=,++,--,<<,>>
        friend Fraction operator+(const Fraction &first, const Fraction &second);
        friend Fraction operator-(const Fraction &first, const Fraction &other);
        friend Fraction operator*(const Fraction &first, const Fraction &other);
        friend Fraction operator/(const Fraction &first, const Fraction &other);

        friend Fraction operator*(const Fraction &fraction, float floatNumber);
        friend Fraction operator+(const Fraction &fraction, float floatNumber);
        friend Fraction operator-(const Fraction &fraction, float floatNumber);
        friend Fraction operator/(const Fraction &fractiob, float floatNumber);

        friend Fraction operator++(Fraction &frac, int);
        friend Fraction operator--(Fraction &frac, int);
        Fraction &operator++();
        Fraction &operator--();

        friend Fraction operator+(float floatNumber, const Fraction &frac1);
        friend Fraction operator-(float floatNumber, const Fraction &frac1);
        friend Fraction operator*(float floatNumber, const Fraction &frac1);
        friend Fraction operator/(float floatNumber, const Fraction &frac1);

        friend bool operator==(const Fraction &frac1, const Fraction &frac2);
        friend bool operator>=(const Fraction &frac1, const Fraction &frac2);
        friend bool operator<=(const Fraction &frac1, const Fraction &frac2);
        friend bool operator>(const Fraction &frac1, const Fraction &frac2);
        friend bool operator<(const Fraction &frac1, const Fraction &frac2);
        friend bool operator==(float floatNumber, const Fraction &frac1);
        friend bool operator>=(float floatNumber, const Fraction &frac1);
        friend bool operator<=(float floatNumber, const Fraction &frac1);
        friend bool operator>(float floatNumber, const Fraction &frac1);
        friend bool operator<(float floatNumber, const Fraction &frac1);
        friend bool operator==(const Fraction &frac1, float floatNumber);
        friend bool operator>=(const Fraction &frac1, float floatNumber);
        friend bool operator<=(const Fraction &frac1, float floatNumber);
        friend bool operator>(const Fraction &frac1, float floatNumber);
        friend bool operator<(const Fraction &frac1, float floatNumber);

        friend std::ostream &operator<<(std::ostream &output, const Fraction &frac);
        friend std::istream &operator>>(std::istream &input, Fraction &frac);
    };
}