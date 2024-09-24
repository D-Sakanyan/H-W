#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <iostream>

class ComplexNumber {
private:
    double real; 
    double imag; 

public:
    ComplexNumber(double r = 0.0, double i = 0.0);

    ComplexNumber operator+(const ComplexNumber& other) const;
    ComplexNumber operator-(const ComplexNumber& other) const;
    ComplexNumber operator*(double scalar) const;

    double absolute() const; 
    friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& cn);
};

#endif
