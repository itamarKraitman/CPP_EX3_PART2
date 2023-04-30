#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "Fraction.hpp"

namespace ariel
{
    Fraction::Fraction() {}

    Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
    {
        if (denominator < 0)
        {
            this->numerator *= -1;
            this->denominator *= -1;
        }

        if (denominator == 0)
        {
            throw std::invalid_argument("Dividing by zero");
        }
        reduceFraction();
    }
    Fraction::Fraction(double floatNumber) // https://www.geeksforgeeks.org/convert-given-float-value-to-equivalent-fraction/
    {
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
    }
    int Fraction::getNumerator() const { return this->numerator; }
    int Fraction::getDenominator() const { return this->denominator; }

    bool Fraction::reduceFraction()
    {

        int gcd = findGcd(this->numerator, this->denominator);
        if (gcd > 1)
        {
            this->numerator /= gcd;
            this->denominator /= gcd;
            return true;
        }
        return false; // did not make any redue operation
    }

    int Fraction::findGcd(int numerator, int denominator) const // for fraction reduce
    {
        return __gcd(numerator, denominator);
    }

    // overloading +,-,*,/,==,>,<,<=,>=,++,--,<<,>>
    Fraction operator+(const Fraction &other1, const Fraction &other)
    {
        if (other1.denominator == other.denominator)
        {
            return Fraction(other1.numerator + other.numerator, other1.denominator);
        }
        else
        {
            int newNumerator = (other1.numerator * other.denominator) + (other.numerator * other1.denominator);
            int newDenominator = other1.denominator * other.denominator;
            return Fraction(newNumerator, newDenominator);
        }
    }
    Fraction operator-(const Fraction &other1, const Fraction &other)
    {
        if (other1.denominator == other.denominator)
        {
            return Fraction(other1.numerator - other.numerator, other1.denominator);
        }
        else
        {
            int newNumerator = (other1.numerator * other.denominator) - (other.numerator * other1.denominator);
            int newDenominator = other1.denominator * other.denominator;
            return Fraction(newNumerator, newDenominator);
        }
    }
    Fraction operator*(const Fraction &other1, const Fraction &other)
    {
        int nume = other1.numerator * other.numerator;
        int deno = other1.denominator * other.denominator;
        return Fraction(nume, deno);
    }
    Fraction operator/(const Fraction &other1, const Fraction &other)
    {
        if (other.numerator == 0)
        {
            throw std::runtime_error("Dividing by zero");
        }
        else
        {
            int nume = other1.numerator * other.denominator;
            int deno = other1.denominator * other.numerator;
            return Fraction(nume, deno);
        }
    }

    Fraction operator*(const Fraction &fraction, double floatfloatNumber)
    {
        Fraction temp = fraction * Fraction(floatfloatNumber);
        Fraction reduced(temp.numerator, temp.denominator);
        return reduced;
    }
    Fraction operator+(const Fraction &fraction, double floatfloatNumber)
    {
        Fraction temp = fraction + Fraction(floatfloatNumber);
        return temp;
    }
    Fraction operator-(const Fraction &fraction, double floatfloatNumber)
    {
        Fraction temp = fraction - Fraction(floatfloatNumber);
        return temp;
    }
    Fraction operator/(const Fraction &fraction, double floatfloatNumber)
    {
        if (floatfloatNumber == 0.0)
        {
            throw std::runtime_error("Dividing by zero");
        }

        Fraction temp = fraction / Fraction(floatfloatNumber);
        return temp;
    }

    // postfix incerment and decement
    Fraction operator++(Fraction &frac, int)
    {
        Fraction copy(frac.getNumerator(), frac.getDenominator());
        ++frac;
        return copy;
    }
    Fraction operator--(Fraction &frac, int)
    {
        Fraction copy(frac.getNumerator(), frac.getDenominator());
        --frac;
        return copy;
    }

    // prefix incerment and decement
    Fraction &Fraction::operator++()
    {
        this->numerator += denominator;
        return *this;
    }
    Fraction &Fraction::operator--()
    {
        this->numerator -= this->denominator;
        return *this;
    }

    Fraction operator+(double floatNumber, const Fraction &frac1)
    {
        double roundedNumber = round(floatNumber * 1000) / 1000;
        int newNumerator = round(roundedNumber * 1000);
        Fraction floatAsFraction(newNumerator, 1000);
        return floatAsFraction + frac1;
    }
    Fraction operator-(double floatNumber, const Fraction &frac1)
    {

        Fraction floatAsFraction(floatNumber);
        Fraction temp = floatAsFraction - frac1;
        temp.reduceFraction();
        return temp;
    }
    Fraction operator*(double floatNumber, const Fraction &frac1)
    {
        Fraction floatAsFraction(floatNumber);
        Fraction temp = floatAsFraction * frac1;
        temp.reduceFraction();
        return temp;
    }
    Fraction operator/(double floatNumber, const Fraction &frac1)
    {
        if (frac1.numerator == 0)
        {
            throw std::runtime_error("Dividing by zero");
        }

        Fraction floatAsFraction(floatNumber);
        Fraction temp = floatAsFraction / frac1;
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
        double fracAsfloat = static_cast<double>(frac1.numerator) / frac1.denominator;
        // return Fraction(floatfloatNumber) == frac1;
        return floatNumber == fracAsfloat;
    }
    bool operator>=(double floatfloatNumber, const Fraction &frac1)
    {
        return Fraction(floatfloatNumber) >= frac1;
    }
    bool operator<=(double floatfloatNumber, const Fraction &frac1)
    {
        return Fraction(floatfloatNumber) <= frac1;
    }
    bool operator>(double floatfloatNumber, const Fraction &frac1)
    {
        return Fraction(floatfloatNumber) > frac1;
    }
    bool operator<(double floatfloatNumber, const Fraction &frac1)
    {
        return Fraction(floatfloatNumber) < frac1;
    }

    bool operator==(const Fraction &frac1, double floatfloatNumber)
    {
        return frac1 == Fraction(floatfloatNumber);
    }
    bool operator>=(const Fraction &frac1, double floatfloatNumber)
    {
        return frac1 >= Fraction(floatfloatNumber);
    }
    bool operator<=(const Fraction &frac1, double floatfloatNumber)
    {
        return frac1 <= Fraction(floatfloatNumber);
    }
    bool operator>(const Fraction &frac1, double floatfloatNumber)
    {
        return frac1 > Fraction(floatfloatNumber);
    }
    bool operator<(const Fraction &frac1, double floatfloatNumber)
    {
        return frac1 < Fraction(floatfloatNumber);
    }

    std::ostream &operator<<(std::ostream &output, const Fraction &frac) { return (output << frac.getNumerator() << '/' << frac.getDenominator()); }
    std::istream &operator>>(std::istream &input, Fraction& frac)
    {
           
        if (input.peek() == EOF)
        {
            throw std::runtime_error("no input");
        }
        
        input >> frac.numerator;
        if (input.peek() == EOF)
        {
            throw std::runtime_error("only one argument");
        }
        input >> frac.denominator;
        return input;
    }
}

