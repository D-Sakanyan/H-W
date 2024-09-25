#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0);

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(double constant) const;
    double absolute() const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

private:
    double real_;
    double imag_;
};

#endif
