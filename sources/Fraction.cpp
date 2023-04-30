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
        if (floatNumber == 0)
        {
            throw invalid_argument("Dividing by zero");
        }
        
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

    Fraction::Fraction(const Fraction &frac) : numerator(frac.numerator), denominator(frac.denominator)
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

    int Fraction::findGcd(int first, int second)
    {
        return __gcd(first, second);
    }

    int Fraction::findLcm(const Fraction &first, const Fraction &second)
    {
        int firstDenominator = first.getDenominator();
        int secondDenominator = second.getDenominator();

        return abs(firstDenominator * secondDenominator) / findGcd(firstDenominator, secondDenominator);
    }

    bool Fraction::checkOverflow(long long first, long long second)
    {
        constexpr long long max_int = std::numeric_limits<int>::max();
        constexpr long long min_int = std::numeric_limits<int>::min();

        if (first > max_int || second > max_int || first < min_int || second < min_int)
        {
            return true;
        }
        return false;
    }

    // overloading +,-,*,/,==,>,<,<=,>=,++,--,<<,>>
    Fraction operator+(const Fraction &first, const Fraction &second)
    {
        Fraction result;
        long long newNumerator, newDenominator = first.denominator;
        if (first.denominator == second.denominator)
        {
            newNumerator = first.numerator + second.numerator;
        }
        else
        {
            newNumerator = ((long long)first.numerator * (long long)second.denominator) + ((long long)second.numerator * (long long)first.denominator);
            newDenominator = (long long)first.denominator * (long long)second.denominator;
        }
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }
        
        return Fraction(newNumerator, newDenominator);
    }
    Fraction operator-(const Fraction &first, const Fraction &second)
    {
        Fraction result;
        long long newNumerator, newDenominator = first.denominator;
        if (first.denominator == second.denominator)
        {
            newNumerator = first.numerator - second.numerator;
        }
        else
        {
            newNumerator = ((long long)first.numerator * (long long)second.denominator) - ((long long)second.numerator * (long long)first.denominator);
            newDenominator = (long long)first.denominator * (long long)second.denominator;
        }
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }
        
        return Fraction(newNumerator, newDenominator);
    }
    Fraction operator*(const Fraction &first, const Fraction &second)
    {
        int newNumerator = first.numerator * second.numerator;
        int newDenominator = first.denominator * second.denominator;
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }
        
        return Fraction(newNumerator, newDenominator);
    }
    Fraction operator/(const Fraction &first, const Fraction &second)
    {
        // no need to check for dividing by zero in advance because its made in constructors
        int newNumerator = first.numerator * second.denominator;
        int newDenominator = first.denominator * second.numerator;
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }
        
        return Fraction(newNumerator, newDenominator);
    }

    Fraction operator+(const Fraction &fraction, double floatNumber)
    {
        return fraction + Fraction(floatNumber);
    }
    Fraction operator-(const Fraction &fraction, double floatNumber)
    {
        return fraction - Fraction(floatNumber);
    }
    Fraction operator*(const Fraction &fraction, double floatNumber)
    {
        return fraction * Fraction(floatNumber);
    }
    Fraction operator/(const Fraction &fraction, double floatNumber)
    {
        return fraction / Fraction(floatNumber);
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
        
        return frac1 + Fraction(floatNumber);
    }
    Fraction operator-(double floatNumber, const Fraction &frac1)
    {
        return  Fraction(floatNumber) - frac1;
    }
    Fraction operator*(double floatNumber, const Fraction &frac1)
    {
        return frac1 * Fraction(floatNumber);
    }
    Fraction operator/(double floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) / frac1;
    }

    bool operator==(const Fraction &frac1, const Fraction &frac2)
    {
        if (frac1.getDenominator() == frac2.getDenominator())
        {
            return frac1.getNumerator() == frac2.getNumerator();
        }

        int lcm = Fraction::findLcm(frac1, frac2);
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

        int lcm = Fraction::findLcm(frac1, frac2);
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

        int lcm = Fraction::findLcm(frac1, frac2);
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

        int lcm = Fraction::findLcm(frac1, frac2);
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

        int lcm = Fraction::findLcm(frac1, frac2);
        int firstFracLcmMultiply = frac1.getNumerator() * lcm / frac1.getDenominator();
        int secondFracLcmMultiply = frac2.getNumerator() * lcm / frac2.getDenominator();

        return (firstFracLcmMultiply < secondFracLcmMultiply);
    }

    bool operator==(double floatNumber, const Fraction &frac1)
    {
        double fracAsfloat = static_cast<double>(frac1.numerator) / frac1.denominator;
        return floatNumber == fracAsfloat;
    }
    bool operator>=(double floatNumber, const Fraction &frac1)
    {
        double fracAsfloat = static_cast<double>(frac1.numerator) / frac1.denominator;
        return floatNumber >= fracAsfloat;
    }
    bool operator<=(double floatNumber, const Fraction &frac1)
    {
        double fracAsfloat = static_cast<double>(frac1.numerator) / frac1.denominator;
        return floatNumber <= fracAsfloat;
    }
    bool operator>(double floatNumber, const Fraction &frac1)
    {
        double fracAsfloat = static_cast<double>(frac1.numerator) / frac1.denominator;
        return floatNumber > fracAsfloat;
    }
    bool operator<(double floatNumber, const Fraction &frac1)
    {
        double fracAsfloat = static_cast<double>(frac1.numerator) / frac1.denominator;
        return floatNumber < fracAsfloat;
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
