#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include "Fraction.hpp"

namespace ariel
{
    Fraction::Fraction() {}

    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
    {
        if (denominator == 0)
        {
            throw logic_error("Dividing by zero");
        }
        reduceFraction();
    }
    Fraction::Fraction(double floatNumber) // https://www.geeksforgeeks.org/convert-given-float-value-to-equivalent-fraction/
    {
        // find the number of digits after decimal point
        size_t decimalPointPos = std::to_string(floatNumber).find(".");
        size_t numbrOfDigitsAfterPoint = std::to_string(floatNumber).size() - decimalPointPos - 1;

        // round to 3 decimal places at most
        double limitedToThreeNumber;
        if (numbrOfDigitsAfterPoint > 3)
        {
            std::ostringstream stream;
            stream << std::fixed << std::setprecision(3) << floatNumber;
            limitedToThreeNumber = std::stod(stream.str());
        }

        // convert to numerator and denominator
        this->denominator = std::pow(10, numbrOfDigitsAfterPoint);
        this->numerator = std::round(limitedToThreeNumber * denominator);

        // reduce
        reduceFraction();

        // check if the number is rational ,if not, its denominator equals to 0
        if (this->denominator == 0)
        {
            throw runtime_error("irretional number, dividing by zero");
        }
    }
    int Fraction::getNumerator() const { return this->numerator; }
    int Fraction::getDenominator() const { return this->denominator; }

    void Fraction::reduceFraction()
    {
        int gcd = findGcd();
        // cout << gcd << endl;
        this->numerator /= gcd;
        this->denominator /= gcd;
    }

    int Fraction::findGcd() const // for fraction reduce
    {
        int nume = this->numerator;
        int deno = this->denominator;
        while (deno != 0)
        {
            int temp = deno;
            deno = nume % deno;
            nume = temp;
        }
        return abs(nume); // for sometimes returns negative number, eg -1 and 2
    }

    // overloading +,-,*,/,==,>,<,<=,>=,++,--,<<,>>
    Fraction Fraction::operator+(const Fraction &other) const
    {
        Fraction temp(this->numerator * other.getDenominator() + other.getNumerator() * this->denominator, this->denominator * other.denominator);
        temp.reduceFraction();
        return temp;
    }
    Fraction Fraction::operator-(const Fraction &other) const
    {
        Fraction temp((this->numerator * other.getDenominator()) - (other.getNumerator() * this->denominator), this->denominator * other.denominator);
        temp.reduceFraction();
        return temp;
    }
    Fraction Fraction::operator*(const Fraction &other) const
    {
        Fraction temp(this->numerator * other.getNumerator(), this->denominator * other.getDenominator());
        temp.reduceFraction();
        return temp;
    }
    Fraction Fraction::operator/(const Fraction &other) const
    {
        Fraction temp(this->numerator * other.getDenominator(), this->denominator * other.getNumerator());
        temp.reduceFraction();
        return temp;
    }

    Fraction Fraction::operator*(double floatNumber) const
    {
        Fraction floatAsFraction(floatNumber);
        floatAsFraction.reduceFraction();
        return this->operator*(floatAsFraction);
    }
    Fraction Fraction::operator+(double floatNumber) const
    {
        Fraction floatAsFraction(floatNumber);
        floatAsFraction.reduceFraction();
        return this->operator+(floatAsFraction);
    }
    Fraction Fraction::operator-(double floatNumber) const
    {
        Fraction floatAsFraction(floatNumber);
        floatAsFraction.reduceFraction();
        return this->operator-(floatAsFraction);
    }
    Fraction Fraction::operator/(double floatNumber) const
    {
        Fraction floatAsFraction(floatNumber);
        floatAsFraction.reduceFraction();
        return this->operator/(floatAsFraction);
    }

    // postfix incerment and decement
    Fraction Fraction::operator++(int dummy_flag)
    {
        Fraction copy = *this;
        copy.operator+(Fraction(copy.denominator, copy.denominator));
        return copy;
    }
    Fraction Fraction::operator--(int dummy_flag)
    {
        Fraction copy = *this;
        copy.operator-(Fraction(copy.denominator, copy.denominator));
        return copy;
    }

    // prefix incerment and decement
    Fraction &Fraction::operator++() { return *this; }
    Fraction &Fraction::operator--() { return *this; }

    Fraction operator+(double floatNumber, const Fraction &frac1)
    {

        Fraction floatAsFraction(floatNumber);
        Fraction temp(floatAsFraction.operator+(frac1));
        temp.reduceFraction();
        return temp;
    }
    Fraction operator-(double floatNumber, const Fraction &frac1)
    {

        Fraction floatAsFraction(floatNumber);
        Fraction temp(floatAsFraction.operator-(frac1));
        temp.reduceFraction();
        return temp;
    }
    Fraction operator*(double floatNumber, const Fraction &frac1)
    {
        Fraction floatAsFraction(floatNumber);
        Fraction temp(floatAsFraction.operator*(frac1));
        temp.reduceFraction();
        return temp;
    }
    Fraction operator/(double floatNumber, const Fraction &frac1)
    {

        Fraction floatAsFraction(floatNumber);
        Fraction temp(floatAsFraction.operator/(frac1));
        temp.reduceFraction();
        return temp;
    }

    static int findGcd(int firstDenominator, int secondDenominator) // for finding lcm
    {
        if (secondDenominator == 0) // 5/2 and 6/1, lcm of  2 and 1 is 2
        {
            return firstDenominator;
        }
        return findGcd(secondDenominator, firstDenominator % secondDenominator);
    }

    static int findLcm(Fraction first, Fraction second)
    {
        int firstDenominator = first.getDenominator();
        int secondDenominator = second.getDenominator();

        return abs(firstDenominator * secondDenominator) / findGcd(firstDenominator, secondDenominator);
    }

    bool operator==(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.getDenominator() == frac2.getDenominator())
        {
            return frac1.getNumerator() == frac2.getNumerator();
        }

        int lcm = findLcm(frac1, frac2);
        int firstFracLcmMultiply = frac1.getNumerator() * lcm / frac1.getDenominator();
        int secondFracLcmMultiply = frac2.getNumerator() * lcm / frac2.getDenominator();

        return (firstFracLcmMultiply == secondFracLcmMultiply);
    }
    bool operator>=(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.getDenominator() == frac2.getDenominator())
        {
            return frac1.getNumerator() >= frac2.getNumerator();
        }

        int lcm = findLcm(frac1, frac2);
        int firstFracLcmMultiply = frac1.getNumerator() * lcm / frac1.getDenominator();
        int secondFracLcmMultiply = frac2.getNumerator() * lcm / frac2.getDenominator();

        return (firstFracLcmMultiply >= secondFracLcmMultiply);
    }
    bool operator<=(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.getDenominator() == frac2.getDenominator())
        {
            return frac1.getNumerator() <= frac2.getNumerator();
        }

        int lcm = findLcm(frac1, frac2);
        int firstFracLcmMultiply = frac1.getNumerator() * lcm / frac1.getDenominator();
        int secondFracLcmMultiply = frac2.getNumerator() * lcm / frac2.getDenominator();

        return (firstFracLcmMultiply <= secondFracLcmMultiply);
    }
    bool operator>(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.getDenominator() == frac2.getDenominator())
        {
            return frac1.getNumerator() > frac2.getNumerator();
        }

        int lcm = findLcm(frac1, frac2);
        int firstFracLcmMultiply = frac1.getNumerator() * lcm / frac1.getDenominator();
        int secondFracLcmMultiply = frac2.getNumerator() * lcm / frac2.getDenominator();

        return (firstFracLcmMultiply > secondFracLcmMultiply);
    }
    bool operator<(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.getDenominator() == frac2.getDenominator())
        {
            return frac1.getNumerator() < frac2.getNumerator();
        }

        int lcm = findLcm(frac1, frac2);
        int firstFracLcmMultiply = frac1.getNumerator() * lcm / frac1.getDenominator();
        int secondFracLcmMultiply = frac2.getNumerator() * lcm / frac2.getDenominator();

        return (firstFracLcmMultiply < secondFracLcmMultiply);
    }

    bool operator==(double floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) == frac1;
    }
    bool operator>=(double floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) >= frac1;
    }
    bool operator<=(double floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) <= frac1;
    }
    bool operator>(double floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) > frac1;
    }
    bool operator<(double floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) < frac1;
    }

    bool operator==(const Fraction &frac1, double floatNumber)
    {
        return frac1 == Fraction(floatNumber);
    }
    bool operator>=(const Fraction &frac1, double floatNumber)
    {
        return frac1 >= Fraction(floatNumber);
    }
    bool operator<=(const Fraction &frac1, double floatNumber)
    {
        return frac1 <= Fraction(floatNumber);
    }
    bool operator>(const Fraction &frac1, double floatNumber)
    {
        return frac1 > Fraction(floatNumber);
    }
    bool operator<(const Fraction &frac1, double floatNumber)
    {
        return frac1 < Fraction(floatNumber);
    }

    std::ostream &operator<<(std::ostream &output, const Fraction &frac) { return (output << frac.getNumerator() << '/' << frac.getDenominator()); }
    std::istream &operator>>(std::istream &input, Fraction &frac)
    {
        input >> frac.numerator >> frac.denominator;

        // Check if denominator is zero
        if (frac.denominator == 0)
        {
            input.setstate(std::ios_base::failbit);
        }
        else
        {
            frac.reduceFraction();
        }
        return input;
    }

}
