/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/Fraction.hpp"

using namespace ariel;

int main()
{
    Fraction a(5, 3), b(14, 21), d(1.5), e(2, 4);
    cout << "a: " << a << " b: " << b << endl;
    cout << "d: " << d << " e: " << e << endl; // should be 3/2 and 1/2
    cout << a + b << endl;
    cout << "a+b " << a + b << endl;
    cout << "a-b " << a - b << endl;
    cout << "a/b " << a / b << endl;
    cout << "a*b " << a * b << endl;
    cout << "2.3*b " << 2.3 * b << endl;
    cout << "a+2.421 " << a + 2.421 << endl;
    Fraction c = a + b - 1;
    cout << c++ << endl;
    cout << --c << endl;

    cout << "d+e " << d + e << endl;
    cout << "d-e " << d - e << endl;
    cout << "d/e " << d / e << endl;
    cout << "d*e " << d * e << endl;
    cout << "2.3*e " << 2.3 * e << endl;
    cout << "d+2.421 " << d + 2.421 << endl;
    cout << "e+2.421 " << e + 2.421 << endl;

    cout << "a+b+d-e " << a + b + d - e << endl;
    cout << "a*b*d/e " << a * b * d / e << endl;

    cout << "c >=b ? : " << (c >= b) << endl;
    if (a > 1.1)
        cout << " a is bigger than 1.1" << endl;
    else
        cout << " a is smaller than 1.1" << endl;

    stringstream input("5 8");
    Fraction frac;
    input >> frac;
    cout << frac << endl;

    stringstream invalid("2");
    try
    {
        invalid >> frac;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Throws exception as required";
    }
    
}