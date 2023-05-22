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
            if (numerator > 0)
            {
                this->numerator *= -1;
                this->denominator *= -1;
            }
            else // numerator < 0 (ie. -2/-3)
            {
                this->numerator *= -1;
                this->denominator *= -1;
            }
        }

        if (denominator == 0 && numerator != 0)
        {
            throw std::invalid_argument("Dividing by zero");
        }
        reduceFraction();
    }
    Fraction::Fraction(float floatNumber)
    {
        float limitedToThreeDigits = std::round(floatNumber * 1000.0) / 1000.0;
        // convert to numerator and denominator
        this->numerator = limitedToThreeDigits * 1000;
        this->denominator = 1000;

        if (this->denominator < 0)
        {
            this->numerator *= -1;
            this->denominator *= -1;
        }

        // reduce
        reduceFraction();
    }

    int Fraction::getNumerator() const { return this->numerator; }
    int Fraction::getDenominator() const { return this->denominator; }

    bool Fraction::reduceFraction()
    {

        int gcd = findGcd(this->numerator, this->denominator);
        if (gcd != 1)
        {
            if (gcd < 0)
            {
                gcd *= -1;
            }

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
        long long newNumerator, newDenominator = static_cast<long long>(first.denominator);
        if (first.denominator == second.denominator)
        {
            newNumerator = static_cast<long long>(first.numerator) + static_cast<long long>(second.numerator);
        }
        else
        {
            newNumerator = static_cast<long long>(first.numerator) * static_cast<long long>(second.denominator) + static_cast<long long>(second.numerator) * static_cast<long long>(first.denominator);
            newDenominator = static_cast<long long>(first.denominator) * static_cast<long long>(second.denominator);
        }
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }

        return Fraction(static_cast<int>(newNumerator), static_cast<long long>(newDenominator));
    }
    Fraction operator-(const Fraction &first, const Fraction &second)
    {
        Fraction result;
        long long newNumerator, newDenominator = static_cast<long long>(first.denominator);
        if (first.denominator == second.denominator)
        {
            newNumerator = static_cast<long long>(first.numerator) - static_cast<long long>(second.numerator);
        }
        else
        {
            newNumerator = static_cast<long long>(first.numerator) * static_cast<long long>(second.denominator) - static_cast<long long>(second.numerator) * static_cast<long long>(first.denominator);
            newDenominator = static_cast<long long>(first.denominator) * static_cast<long long>(second.denominator);
        }
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }

        return Fraction(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    }
    Fraction operator*(const Fraction &first, const Fraction &second)
    {
        long long newNumerator = static_cast<long long>(first.numerator) * static_cast<long long>(second.numerator);
        long long newDenominator = static_cast<long long>(first.denominator) * static_cast<long long>(second.denominator);
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }

        return Fraction(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    }
    Fraction operator/(const Fraction &first, const Fraction &second)
    {
        if (second.numerator == 0)
        {
            throw std::runtime_error("Dividing by zero");
        }

        // no need to check for dividing by zero in advance because its made in constructors
        long long newNumerator = static_cast<long long>(first.numerator) * static_cast<long long>(second.denominator);
        long long newDenominator = static_cast<long long>(first.denominator) * static_cast<long long>(second.numerator);
        if (Fraction::checkOverflow(newNumerator, newDenominator))
        {
            throw overflow_error("overflow");
        }

        return Fraction(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    }

    //* binary operators *//
    Fraction operator+(const Fraction &fraction, float floatNumber)
    {
        return fraction + Fraction(floatNumber);
    }
    Fraction operator-(const Fraction &fraction, float floatNumber)
    {
        return fraction - Fraction(floatNumber);
    }
    Fraction operator*(const Fraction &fraction, float floatNumber)
    {
        return fraction * Fraction(floatNumber);
    }
    Fraction operator/(const Fraction &fraction, float floatNumber)
    {
        // checking of dividing by zero is made in constructor
        return fraction / Fraction(floatNumber);
    }

    Fraction operator+(float floatNumber, const Fraction &frac1)
    {

        return frac1 + Fraction(floatNumber);
    }
    Fraction operator-(float floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) - frac1;
    }
    Fraction operator*(float floatNumber, const Fraction &frac1)
    {
        return frac1 * Fraction(floatNumber);
    }
    Fraction operator/(float floatNumber, const Fraction &frac1)
    {
        // checking of dividing by zero is made in constructor
        return Fraction(floatNumber) / frac1;
    }

    //* logic operators *//
    bool operator>=(const Fraction &frac1, const Fraction &frac2)
    {
        int firstNewNumerator = frac1.numerator * frac2.denominator;
        int secondNewNumerator = frac2.numerator * frac1.denominator;

        return firstNewNumerator >= secondNewNumerator;
    }
    bool operator<=(const Fraction &frac1, const Fraction &frac2)
    {
        return frac2 >= frac1;
    }
    bool operator==(const Fraction &frac1, const Fraction &frac2)
    {
        return (frac1 >= frac2 && frac2 >= frac1);
    }
    bool operator>(const Fraction &frac1, const Fraction &frac2)
    {
        int firstNewNumerator = frac1.numerator * frac2.denominator;
        int secondNewNumerator = frac2.numerator * frac1.denominator;

        return firstNewNumerator > secondNewNumerator;
    }
    bool operator<(const Fraction &frac1, const Fraction &frac2)
    {
        return frac2 > frac1;
    }
    bool operator>=(const Fraction &frac1, float floatNumber)
    {
        return frac1 >= Fraction(floatNumber);
    }
    bool operator<=(const Fraction &frac1, float floatNumber)
    {
        return frac1 <= Fraction(floatNumber);
    }
    bool operator==(const Fraction &frac1, float floatNumber)
    {
        return (frac1 >= floatNumber && frac1 <= floatNumber);
    }
    bool operator>(const Fraction &frac1, float floatNumber)
    {
        return frac1 > Fraction(floatNumber);
    }
    bool operator<(const Fraction &frac1, float floatNumber)
    {
        return frac1 < Fraction(floatNumber);
    }
    bool operator>=(float floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) >= frac1;
    }
    bool operator<=(float floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) <= frac1;
    }
    bool operator==(float floatNumber, const Fraction &frac1)
    {
        return frac1 == floatNumber;
    }
    bool operator>(float floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) > frac1;
    }
    bool operator<(float floatNumber, const Fraction &frac1)
    {
        return Fraction(floatNumber) < frac1;
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

    std::ostream &operator<<(std::ostream &output, const Fraction &frac)
    {
        output << frac.getNumerator() << '/' << frac.getDenominator();
        return output;
    }
    std::istream &operator>>(std::istream &input, Fraction &frac)
    {

        if (input.peek() == EOF)
        {
            throw std::runtime_error("no input");
        }
        if (!(input >> frac.numerator))
        {
            throw std::runtime_error("Couldn't read numerator");
        }
        if (input.peek() == EOF)
        {
            throw std::runtime_error("only one argument");
        }
        if (!(input >> frac.denominator))
        {
            throw std::runtime_error("Couldn't read denominator");
        }
        if (frac.denominator == 0)
        {
            throw std::runtime_error("Dividing by Zero");
        }

        else if (frac.denominator < 0) // move '-' to numerator
        {
            frac.numerator *= -1;
            frac.denominator *= -1;
        }

        return input;
    }
}
